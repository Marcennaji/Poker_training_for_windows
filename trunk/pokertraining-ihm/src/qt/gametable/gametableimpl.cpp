/*****************************************************************************
 * PokerTraining - THNL training software, based on the PokerTH GUI          *
 * Copyright (C) 2013 Marc Ennaji                                            *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/
#include "gametableimpl.h"
#include "session.h"
#include <qt/mymessagedialog/mymessagedialogimpl.h>
#include <qt/settingsdialog/settingsdialogimpl.h>
#include <qt/startwindow/startwindowimpl.h>

#include <qt/gametable/startsplash/startsplash.h>
#include "mycardspixmaplabel.h"
#include "mysetlabel.h"
#include "myactionbutton.h"
#include "mycashlabel.h"
#include "mynamelabel.h"
#include "mychancelabel.h"
#include "mymenubar.h"
#include <qt/gametable/log/guilog.h>

#include <engine/Player.h>
#include <engine/boardinterface.h>
#include <engine/handinterface.h>
#include <engine/game.h>
#include <engine/cardsvalue.h>

#include <configfile.h>
#include <qt/sound/sdlplayer.h>
#include <qt/sound/soundevents.h>
#include <qt/styles/gametablestylereader.h>
#include <qt/styles/carddeckstylereader.h>
#include <gamedata.h>

#include <cmath>

#define FORMATLEFT(X) "<p align='center'>(X)"
#define FORMATRIGHT(X) "(X)</p>"

using namespace std;

gameTableImpl::gameTableImpl(ConfigFile *c, QMainWindow *parent)
	: QMainWindow(parent), myConfig(c), gameSpeed(0), myActionIsBet(0), myActionIsRaise(0),
	pushButtonBetRaiseIsChecked(FALSE), pushButtonBetRaiseHalfPotIsChecked(FALSE), 
	pushButtonBetRaiseTwoThirdPotIsChecked(FALSE), pushButtonBetRaisePotIsChecked(FALSE), pushButtonCallCheckIsChecked(FALSE),
	pushButtonFoldIsChecked(FALSE), pushButtonAllInIsChecked(FALSE), myButtonsAreCheckable(FALSE),
	breakAfterCurrentHand(FALSE), currentGameOver(FALSE), betSliderChangedByInput(FALSE),
	guestMode(FALSE), myLastPreActionBetValue(0)
{
	int i;

	//	this->setStyle(new QPlastiqueStyle);

	//for statistic development
	for(i=0; i<15; i++) {
		statisticArray[i] = 0;
	}
	////////////////////////////

	myAppDataPath = QString::fromUtf8(myConfig->readConfigString("AppDataDir").c_str());

	setupUi(this);

	//Sound
	mySDLPlayer = new SDLPlayer(myConfig);
	mySoundEventHandler = new SoundEvents(myConfig);

	// 	Init game table style
	myGameTableStyle = new GameTableStyleReader(myConfig, this);
	myGameTableStyle->readStyleFile(QString::fromUtf8(myConfig->readConfigString("CurrentGameTableStyle").c_str()));

	// 	Init card deck style
	myCardDeckStyle = new CardDeckStyleReader(myConfig, this);
	myCardDeckStyle->readStyleFile(QString::fromUtf8(myConfig->readConfigString("CurrentCardDeckStyle").c_str()));

	//Player0 pixmapCardsLabel needs Myw
	pixmapLabel_card0b->setW(this);
	pixmapLabel_card0a->setW(this);

	//set myStyle to widgets wich needs it

	label_chance->setStyle(myGameTableStyle);

	//Flipside festlegen;
	if (myConfig->readConfigInt("FlipsideOwn") && myConfig->readConfigString("FlipsideOwnFile") != "") {
		flipside = QPixmap::fromImage(QImage(QString::fromUtf8(myConfig->readConfigString("FlipsideOwnFile").c_str())));
	} else {
		flipside = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+"flipside.png"));
	}

	//Flipside Animation noch nicht erledigt
	flipHolecardsAllInAlreadyDone = FALSE;

	//Toolboxen verstecken?
	if (!myConfig->readConfigInt("ShowRightToolBox")) {
		groupBox_RightToolBox->hide();
	}
	//CardsChanceMonitor show/hide
	if (!myConfig->readConfigInt("ShowCardsChanceMonitor")) {
		tabWidget_Right->removeTab(2);
		tabWidget_Right->setCurrentIndex(0);
	}

	// userWidgetsArray init
	userWidgetsArray[0] = pushButton_BetRaise;
	userWidgetsArray[1] = pushButton_BetRaiseHalfPot;
	userWidgetsArray[2] = pushButton_BetRaiseTwoThirdPot;
	userWidgetsArray[3] = pushButton_BetRaisePot;
	userWidgetsArray[4] = pushButton_CallCheck;
	userWidgetsArray[5] = pushButton_Fold;
	userWidgetsArray[6] = spinBox_betValue;
	userWidgetsArray[7] = horizontalSlider_bet;
	userWidgetsArray[8] = pushButton_AllIn;

	//hide userWidgets
	for(i=0; i < USER_WIDGETS_NUMBER; i++) {
		userWidgetsArray[i]->hide();
	}

	//Timer Objekt erstellen
	dealFlopCards0Timer = new QTimer(this);
	dealFlopCards1Timer = new QTimer(this);
	dealFlopCards2Timer = new QTimer(this);
	dealFlopCards3Timer = new QTimer(this);
	dealFlopCards4Timer = new QTimer(this);
	dealFlopCards5Timer = new QTimer(this);
	dealFlopCards6Timer = new QTimer(this);
	dealTurnCards0Timer = new QTimer(this);
	dealTurnCards1Timer = new QTimer(this);
	dealTurnCards2Timer = new QTimer(this);
	dealRiverCards0Timer = new QTimer(this);
	dealRiverCards1Timer = new QTimer(this);
	dealRiverCards2Timer = new QTimer(this);

	nextPlayerAnimationTimer = new QTimer(this);
	preflopAnimation1Timer = new QTimer(this);
	preflopAnimation2Timer = new QTimer(this);
	flopAnimation1Timer = new QTimer(this);
	flopAnimation2Timer = new QTimer(this);
	turnAnimation1Timer = new QTimer(this);
	turnAnimation2Timer = new QTimer(this);
	riverAnimation1Timer = new QTimer(this);
	riverAnimation2Timer = new QTimer(this);

	postRiverAnimation1Timer = new QTimer(this);
	postRiverRunAnimation1Timer = new QTimer(this);
	postRiverRunAnimation2Timer = new QTimer(this);
	postRiverRunAnimation2_flipHoleCards1Timer = new QTimer(this);
	postRiverRunAnimation2_flipHoleCards2Timer = new QTimer(this);
	postRiverRunAnimation3Timer = new QTimer(this);
	postRiverRunAnimation5Timer = new QTimer(this);
	potDistributeTimer = new QTimer(this);
	postRiverRunAnimation6Timer = new QTimer(this);

	blinkingStartButtonAnimationTimer = new QTimer(this);
//	voteOnKickTimeoutTimer = new QTimer(this);
	enableCallCheckPushButtonTimer = new QTimer(this);

	dealFlopCards0Timer->setSingleShot(TRUE);
	dealFlopCards1Timer->setSingleShot(TRUE);
	dealFlopCards2Timer->setSingleShot(TRUE);
	dealFlopCards3Timer->setSingleShot(TRUE);
	dealFlopCards4Timer->setSingleShot(TRUE);
	dealFlopCards5Timer->setSingleShot(TRUE);
	dealFlopCards6Timer->setSingleShot(TRUE);
	dealTurnCards0Timer->setSingleShot(TRUE);
	dealTurnCards1Timer->setSingleShot(TRUE);
	dealTurnCards2Timer->setSingleShot(TRUE);
	dealRiverCards0Timer->setSingleShot(TRUE);
	dealRiverCards1Timer->setSingleShot(TRUE);
	dealRiverCards2Timer->setSingleShot(TRUE);

	nextPlayerAnimationTimer->setSingleShot(TRUE);
	preflopAnimation1Timer->setSingleShot(TRUE);
	preflopAnimation2Timer->setSingleShot(TRUE);
	flopAnimation1Timer->setSingleShot(TRUE);
	flopAnimation2Timer->setSingleShot(TRUE);
	turnAnimation1Timer->setSingleShot(TRUE);
	turnAnimation2Timer->setSingleShot(TRUE);
	riverAnimation1Timer->setSingleShot(TRUE);
	riverAnimation2Timer->setSingleShot(TRUE);

	postRiverAnimation1Timer->setSingleShot(TRUE);
	postRiverRunAnimation1Timer->setSingleShot(TRUE);
	postRiverRunAnimation2Timer->setSingleShot(TRUE);
	postRiverRunAnimation3Timer->setSingleShot(TRUE);
	postRiverRunAnimation5Timer->setSingleShot(TRUE);
	postRiverRunAnimation6Timer->setSingleShot(TRUE);

	enableCallCheckPushButtonTimer->setSingleShot(TRUE);

	// buttonLabelArray init
	buttonLabelArray[0] = textLabel_Button0;
	buttonLabelArray[1] = textLabel_Button1;
	buttonLabelArray[2] = textLabel_Button2;
	buttonLabelArray[3] = textLabel_Button3;
	buttonLabelArray[4] = textLabel_Button4;
	buttonLabelArray[5] = textLabel_Button5;
	buttonLabelArray[6] = textLabel_Button6;
	buttonLabelArray[7] = textLabel_Button7;
	buttonLabelArray[8] = textLabel_Button8;
	buttonLabelArray[9] = textLabel_Button9;

	// cashLabelArray init
	cashLabelArray[0] = textLabel_Cash0;
	cashLabelArray[1] = textLabel_Cash1;
	cashLabelArray[2] = textLabel_Cash2;
	cashLabelArray[3] = textLabel_Cash3;
	cashLabelArray[4] = textLabel_Cash4;
	cashLabelArray[5] = textLabel_Cash5;
	cashLabelArray[6] = textLabel_Cash6;
	cashLabelArray[7] = textLabel_Cash7;
	cashLabelArray[8] = textLabel_Cash8;
	cashLabelArray[9] = textLabel_Cash9;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		cashLabelArray[i]->setW(this);
	}

	playerTipLabelArray[0] = label_playerTip0;
	playerTipLabelArray[1] = label_playerTip1;
	playerTipLabelArray[2] = label_playerTip2;
	playerTipLabelArray[3] = label_playerTip3;
	playerTipLabelArray[4] = label_playerTip4;
	playerTipLabelArray[5] = label_playerTip5;
	playerTipLabelArray[6] = label_playerTip6;
	playerTipLabelArray[7] = label_playerTip7;
	playerTipLabelArray[8] = label_playerTip8;
	playerTipLabelArray[9] = label_playerTip9;


	// playerNameLabelArray init
	playerNameLabelArray[0] = label_PlayerName0;
	playerNameLabelArray[1] = label_PlayerName1;
	playerNameLabelArray[2] = label_PlayerName2;
	playerNameLabelArray[3] = label_PlayerName3;
	playerNameLabelArray[4] = label_PlayerName4;
	playerNameLabelArray[5] = label_PlayerName5;
	playerNameLabelArray[6] = label_PlayerName6;
	playerNameLabelArray[7] = label_PlayerName7;
	playerNameLabelArray[8] = label_PlayerName8;
	playerNameLabelArray[9] = label_PlayerName9;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		playerNameLabelArray[i]->setW(this);
	}

	// playerAvatarLabelArray init
	playerAvatarLabelArray[0] = label_Avatar0;
	playerAvatarLabelArray[1] = label_Avatar1;
	playerAvatarLabelArray[2] = label_Avatar2;
	playerAvatarLabelArray[3] = label_Avatar3;
	playerAvatarLabelArray[4] = label_Avatar4;
	playerAvatarLabelArray[5] = label_Avatar5;
	playerAvatarLabelArray[6] = label_Avatar6;
	playerAvatarLabelArray[7] = label_Avatar7;
	playerAvatarLabelArray[8] = label_Avatar8;
	playerAvatarLabelArray[9] = label_Avatar9;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		playerAvatarLabelArray[i]->setW(this);
		playerAvatarLabelArray[i]->setId(i);
	}

	// setLabelArray init
	setLabelArray[0] = textLabel_Set0;
	setLabelArray[1] = textLabel_Set1;
	setLabelArray[2] = textLabel_Set2;
	setLabelArray[3] = textLabel_Set3;
	setLabelArray[4] = textLabel_Set4;
	setLabelArray[5] = textLabel_Set5;
	setLabelArray[6] = textLabel_Set6;
	setLabelArray[7] = textLabel_Set7;
	setLabelArray[8] = textLabel_Set8;
	setLabelArray[9] = textLabel_Set9;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		setLabelArray[i]->setW(this);
	}

	// statusLabelArray init
	actionLabelArray[0] = textLabel_Status0;
	actionLabelArray[1] = textLabel_Status1;
	actionLabelArray[2] = textLabel_Status2;
	actionLabelArray[3] = textLabel_Status3;
	actionLabelArray[4] = textLabel_Status4;
	actionLabelArray[5] = textLabel_Status5;
	actionLabelArray[6] = textLabel_Status6;
	actionLabelArray[7] = textLabel_Status7;
	actionLabelArray[8] = textLabel_Status8;
	actionLabelArray[9] = textLabel_Status9;

	textLabel_Status0->setW(this);

	// GroupBoxArray init
	groupBoxArray[0] = groupBox0;
	groupBoxArray[1] = groupBox1;
	groupBoxArray[2] = groupBox2;
	groupBoxArray[3] = groupBox3;
	groupBoxArray[4] = groupBox4;
	groupBoxArray[5] = groupBox5;
	groupBoxArray[6] = groupBox6;
	groupBoxArray[7] = groupBox7;
	groupBoxArray[8] = groupBox8;
	groupBoxArray[9] = groupBox9;

	// boardCardsArray init
	boardCardsArray[0] = pixmapLabel_cardBoard0;
	boardCardsArray[1] = pixmapLabel_cardBoard1;
	boardCardsArray[2] = pixmapLabel_cardBoard2;
	boardCardsArray[3] = pixmapLabel_cardBoard3;
	boardCardsArray[4] = pixmapLabel_cardBoard4;

	// holeCardsArray int
	holeCardsArray[0][0] = pixmapLabel_card0a;
	holeCardsArray[0][1] = pixmapLabel_card0b;
	holeCardsArray[1][0] = pixmapLabel_card1a;
	holeCardsArray[1][1] = pixmapLabel_card1b;
	holeCardsArray[2][0] = pixmapLabel_card2a;
	holeCardsArray[2][1] = pixmapLabel_card2b;
	holeCardsArray[3][0] = pixmapLabel_card3a;
	holeCardsArray[3][1] = pixmapLabel_card3b;
	holeCardsArray[4][0] = pixmapLabel_card4a;
	holeCardsArray[4][1] = pixmapLabel_card4b;
	holeCardsArray[5][0] = pixmapLabel_card5a;
	holeCardsArray[5][1] = pixmapLabel_card5b;
	holeCardsArray[6][0] = pixmapLabel_card6a;
	holeCardsArray[6][1] = pixmapLabel_card6b;
	holeCardsArray[7][0] = pixmapLabel_card7a;
	holeCardsArray[7][1] = pixmapLabel_card7b;
	holeCardsArray[8][0] = pixmapLabel_card8a;
	holeCardsArray[8][1] = pixmapLabel_card8b;
	holeCardsArray[9][0] = pixmapLabel_card9a;
	holeCardsArray[9][1] = pixmapLabel_card9b;

	//style Game Table
	refreshGameTableStyle();

	//raise actionLable above just inserted mypixmaplabel
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		actionLabelArray[i]->raise();
	}

	//raise board cards
	for (i=0; i<5; i++) {
		boardCardsArray[i]->raise();
	}

	//fix for away string bug in righttabwidget on windows
#if (defined _WIN32) || (defined __APPLE__)
	tabWidget_Right->setTabText(0, " "+tabWidget_Right->tabText(0)+" ");
	tabWidget_Right->setTabText(1, " "+tabWidget_Right->tabText(1)+" ");
	tabWidget_Right->setTabText(2, " "+tabWidget_Right->tabText(2)+" ");
#endif

	//resize stop-button depending on translation
	QFontMetrics tempMetrics = this->fontMetrics();
	int width = tempMetrics.width(tr("Stop"));

	//Clear Focus

	pushButton_break->setMinimumSize(width+10,20);
	groupBox_RightToolBox->clearFocus();

	//set Focus to gametable
	this->setFocus();

	//windowicon
	// 	QString windowIconString();
	this->setWindowIcon(QIcon(myAppDataPath+"gfx/gui/misc/windowicon.png"));

	this->installEventFilter(this);

	this->setWindowTitle(QString(tr("PokerTraining %1").arg(POKERTRAINING_BETA_RELEASE_STRING)));

	// create universal messageDialgo
	myUniversalMessageDialog = new myMessageDialogImpl(myConfig, this);
	myUniversalMessageDialog->setParent(this);

	connect(dealFlopCards0Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards1() ));
	connect(dealFlopCards1Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards2() ));
	connect(dealFlopCards2Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards3() ));
	connect(dealFlopCards3Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards4() ));
	connect(dealFlopCards4Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards5() ));
	connect(dealFlopCards5Timer, SIGNAL(timeout()), this, SLOT( dealFlopCards6() ));
	connect(dealFlopCards6Timer, SIGNAL(timeout()), this, SLOT( handSwitchRounds() ));
	connect(dealTurnCards0Timer, SIGNAL(timeout()), this, SLOT( dealTurnCards1() ));
	connect(dealTurnCards1Timer, SIGNAL(timeout()), this, SLOT( dealTurnCards2() ));
	connect(dealTurnCards2Timer, SIGNAL(timeout()), this, SLOT( handSwitchRounds() ));
	connect(dealRiverCards0Timer, SIGNAL(timeout()), this, SLOT( dealRiverCards1() ));
	connect(dealRiverCards1Timer, SIGNAL(timeout()), this, SLOT( dealRiverCards2() ));
	connect(dealRiverCards2Timer, SIGNAL(timeout()), this, SLOT( handSwitchRounds() ));

	connect(nextPlayerAnimationTimer, SIGNAL(timeout()), this, SLOT( handSwitchRounds() ));
	connect(preflopAnimation1Timer, SIGNAL(timeout()), this, SLOT( preflopAnimation1Action() ));
	connect(preflopAnimation2Timer, SIGNAL(timeout()), this, SLOT( preflopAnimation2Action() ));
	connect(flopAnimation1Timer, SIGNAL(timeout()), this, SLOT( flopAnimation1Action() ));
	connect(flopAnimation2Timer, SIGNAL(timeout()), this, SLOT( flopAnimation2Action() ));
	connect(turnAnimation1Timer, SIGNAL(timeout()), this, SLOT( turnAnimation1Action() ));
	connect(turnAnimation2Timer, SIGNAL(timeout()), this, SLOT( turnAnimation2Action() ));
	connect(riverAnimation1Timer, SIGNAL(timeout()), this, SLOT( riverAnimation1Action() ));
	connect(riverAnimation2Timer, SIGNAL(timeout()), this, SLOT( riverAnimation2Action() ));

	connect(postRiverAnimation1Timer, SIGNAL(timeout()), this, SLOT( postRiverAnimation1Action() ));
	connect(postRiverRunAnimation1Timer, SIGNAL(timeout()), this, SLOT( postRiverRunAnimation2() ));
	connect(postRiverRunAnimation2Timer, SIGNAL(timeout()), this, SLOT( postRiverRunAnimation3() ));
	connect(postRiverRunAnimation3Timer, SIGNAL(timeout()), this, SLOT( postRiverRunAnimation4() ));
	connect(potDistributeTimer, SIGNAL(timeout()), this, SLOT(postRiverRunAnimation5()));
	connect(postRiverRunAnimation5Timer, SIGNAL(timeout()), this, SLOT( postRiverRunAnimation6() ));
	connect(postRiverRunAnimation6Timer, SIGNAL(timeout()), this, SLOT( startNewHand() ));

	connect(blinkingStartButtonAnimationTimer, SIGNAL(timeout()), this, SLOT( blinkingStartButtonAnimationAction()));
	//connect(voteOnKickTimeoutTimer, SIGNAL(timeout()), this, SLOT(nextVoteOnKickTimeoutAnimationFrame()));
	connect(enableCallCheckPushButtonTimer, SIGNAL(timeout()), this, SLOT(enableCallCheckPushButton()));


	connect( actionConfigurePokerTraining, SIGNAL( triggered() ), this, SLOT( callSettingsDialog() ) );
	connect( actionClose, SIGNAL( triggered() ), this, SLOT( closeGameTable()) );

	connect( actionFullScreen, SIGNAL( triggered() ), this, SLOT( switchFullscreen() ) );

	connect( actionShowHideLog, SIGNAL( triggered() ), this, SLOT( switchLogWindow() ) );
	connect( actionShowHideAway, SIGNAL( triggered() ), this, SLOT( switchAwayWindow() ) );
	connect( actionShowHideChance, SIGNAL( triggered() ), this, SLOT( switchChanceWindow() ) );

	connect( pushButton_BetRaise, SIGNAL( clicked(bool) ), this, SLOT( pushButtonBetRaiseClicked(bool) ) );
	connect( pushButton_BetRaiseHalfPot, SIGNAL( clicked(bool) ), this, SLOT( pushButtonBetRaiseHalfPotClicked(bool) ) );
	connect( pushButton_BetRaiseTwoThirdPot, SIGNAL( clicked(bool) ), this, SLOT( pushButtonBetRaiseTwoThirdPotClicked(bool) ) );
	connect( pushButton_BetRaisePot, SIGNAL( clicked(bool) ), this, SLOT( pushButtonBetRaisePotClicked(bool) ) );

	connect( pushButton_Fold, SIGNAL( clicked(bool) ), this, SLOT( pushButtonFoldClicked(bool) ) );
	connect( pushButton_CallCheck, SIGNAL( clicked(bool) ), this, SLOT( pushButtonCallCheckClicked(bool) ) );
	connect( pushButton_AllIn, SIGNAL( clicked(bool) ), this, SLOT(pushButtonAllInClicked(bool) ) );
	connect( horizontalSlider_bet, SIGNAL( valueChanged(int)), this, SLOT ( changeSpinBoxBetValue(int) ) );
	connect( spinBox_betValue, SIGNAL( valueChanged(int)), this, SLOT ( spinBoxBetValueChanged(int) ) );

	connect( horizontalSlider_speed, SIGNAL( valueChanged(int)), this, SLOT ( setGameSpeed(int) ) );
	connect( pushButton_break, SIGNAL( clicked()), this, SLOT ( breakButtonClicked() ) ); // auch wieder starten!!!!

	connect( radioButton_manualAction, SIGNAL( clicked() ) , this, SLOT( changePlayingMode() ) );
	connect( radioButton_autoCheckFold, SIGNAL( clicked() ) , this, SLOT( changePlayingMode() ) );
	connect( radioButton_autoCheckCallAny, SIGNAL( clicked() ), this, SLOT( changePlayingMode() ) );

	//Nachrichten Thread-Save
	connect(this, SIGNAL(signalInitGui(int)), this, SLOT(initGui(int)));
	connect(this, SIGNAL(signalRefreshSet()), this, SLOT(refreshSet()));
	connect(this, SIGNAL(signalRefreshCash()), this, SLOT(refreshCash()));
	connect(this, SIGNAL(signalRefreshAction(int, int)), this, SLOT(refreshAction(int, int)));
	connect(this, SIGNAL(signalRefreshChangePlayer()), this, SLOT(refreshChangePlayer()));
	connect(this, SIGNAL(signalRefreshPot()), this, SLOT(refreshPot()));
	connect(this, SIGNAL(signalRefreshGroupbox(int, int)), this, SLOT(refreshGroupbox(int, int)));
	connect(this, SIGNAL(signalRefreshAll()), this, SLOT(refreshAll()));
	connect(this, SIGNAL(signalRefreshPlayerName()), this, SLOT(refreshPlayerName()));
	connect(this, SIGNAL(signalRefreshButton()), this, SLOT(refreshButton()));
	connect(this, SIGNAL(signalRefreshGameLabels(int)), this, SLOT(refreshGameLabels(int)));
	connect(this, SIGNAL(signalSetPlayerAvatar(int, QString)), this, SLOT(setPlayerAvatar(int, QString)));
	connect(this, SIGNAL(signalGuiUpdateDone()), this, SLOT(guiUpdateDone()));
	connect(this, SIGNAL(signalMeInAction()), this, SLOT(meInAction()));
	connect(this, SIGNAL(signalDisableMyButtons()), this, SLOT(disableMyButtons()));
	connect(this, SIGNAL(signalUpdateMyButtonsState()), this, SLOT(updateMyButtonsState()));
	connect(this, SIGNAL(signalDealBettingRoundCards(int)), this, SLOT(dealBettingRoundCards(int)));
	connect(this, SIGNAL(signalDealHoleCards()), this, SLOT(dealHoleCards()));
	connect(this, SIGNAL(signalDealFlopCards0()), this, SLOT(dealFlopCards0()));
	connect(this, SIGNAL(signalDealTurnCards0()), this, SLOT(dealTurnCards0()));
	connect(this, SIGNAL(signalDealRiverCards0()), this, SLOT(dealRiverCards0()));
	connect(this, SIGNAL(signalNextPlayerAnimation()), this, SLOT(nextPlayerAnimation()));
	connect(this, SIGNAL(signalBettingRoundAnimation2(int)), this, SLOT(beRoAnimation2(int)));
	connect(this, SIGNAL(signalPreflopAnimation1()), this, SLOT(preflopAnimation1()));
	connect(this, SIGNAL(signalPreflopAnimation2()), this, SLOT(preflopAnimation2()));
	connect(this, SIGNAL(signalFlopAnimation1()), this, SLOT(flopAnimation1()));
	connect(this, SIGNAL(signalFlopAnimation2()), this, SLOT(flopAnimation2()));
	connect(this, SIGNAL(signalTurnAnimation1()), this, SLOT(turnAnimation1()));
	connect(this, SIGNAL(signalTurnAnimation2()), this, SLOT(turnAnimation2()));
	connect(this, SIGNAL(signalRiverAnimation1()), this, SLOT(riverAnimation1()));
	connect(this, SIGNAL(signalRiverAnimation2()), this, SLOT(riverAnimation2()));
	connect(this, SIGNAL(signalPostRiverAnimation1()), this, SLOT(postRiverAnimation1()));
	connect(this, SIGNAL(signalPostRiverRunAnimation1()), this, SLOT(postRiverRunAnimation1()));
	connect(this, SIGNAL(signalPostRiverShowCards(unsigned)), this, SLOT(showHoleCards(unsigned)));
	connect(this, SIGNAL(signalFlipHolecardsAllIn()), this, SLOT(flipHolecardsAllIn()));
	connect(this, SIGNAL(signalNextRoundCleanGui()), this, SLOT(nextRoundCleanGui()));
}

gameTableImpl::~gameTableImpl()
{


}

void gameTableImpl::callSettingsDialog()
{
	bool iamInGame = true;
	myStartWindow->callSettingsDialog(iamInGame);
}

void gameTableImpl::applySettings(settingsDialogImpl* mySettingsDialog)
{

	//apply card deck style
	myCardDeckStyle->readStyleFile(QString::fromUtf8(myConfig->readConfigString("CurrentCardDeckStyle").c_str()));
	//apply game table style
	myGameTableStyle->readStyleFile(QString::fromUtf8(myConfig->readConfigString("CurrentGameTableStyle").c_str()));

	if (myConfig->readConfigInt("ShowRightToolBox")) {
		groupBox_RightToolBox->show();
	} else {
		groupBox_RightToolBox->hide();
	}

	//cardschancemonitor show/hide
	if (!myConfig->readConfigInt("ShowCardsChanceMonitor")) {
		tabWidget_Right->removeTab(2);
		tabWidget_Right->setCurrentIndex(0);
	} else {
		if(tabWidget_Right->widget(2) != tab_Chance)
			tabWidget_Right->insertTab(2, tab_Chance, QString(tr("Chance")));
	}
	//refresh board cards if game is running
	if(myStartWindow->getSession()->getCurrentGame()) {

		int tempBoardCardsArray[5];
		myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
		GameState currentState = myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->getBettingRoundID();
		if(currentState >= GAME_STATE_FLOP && currentState <= GAME_STATE_POST_RIVER)
			for(int i=0; i<3; i++) {
				QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[i], 10)+".png"));
				boardCardsArray[i]->setPixmap(card, FALSE);
			}
		if(currentState >= GAME_STATE_TURN && currentState <= GAME_STATE_POST_RIVER) {
			QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[3], 10)+".png"));
			boardCardsArray[3]->setPixmap(card, FALSE);
		}
		if(currentState == GAME_STATE_RIVER || currentState == GAME_STATE_POST_RIVER) {
			QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[4], 10)+".png"));
			boardCardsArray[4]->setPixmap(card, FALSE);
		}
	}

	//Flipside refresh
	if (myConfig->readConfigInt("FlipsideOwn") && myConfig->readConfigString("FlipsideOwnFile") != "") {
		flipside = QPixmap::fromImage(QImage(QString::fromUtf8(myConfig->readConfigString("FlipsideOwnFile").c_str())));
	} else {
		flipside = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+"flipside.png"));
	}
	int j,k;
	for (j=1; j<MAX_NUMBER_OF_PLAYERS; j++ ) {
		for ( k=0; k<=1; k++ ) {
			if (holeCardsArray[j][k]->getIsFlipside()) {
				holeCardsArray[j][k]->setPixmap(flipside, TRUE);
			}
		}
	}

	//Check for anti-peek mode
	if(myStartWindow->getSession()->getCurrentGame()) {
		// 		check if human player is already active
		boost::shared_ptr<Player> humanPlayer = myStartWindow->getSession()->getCurrentGame()->getSeatsList()->front();
		if(humanPlayer->getActiveStatus()) {

			QPixmap tempCardsPixmapArray[2];
			int tempCardsIntArray[2];

			humanPlayer->getCards(tempCardsIntArray);
			if(myConfig->readConfigInt("AntiPeekMode")) {
				holeCardsArray[0][0]->setPixmap(flipside, TRUE);
				tempCardsPixmapArray[0] = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[0], 10)+".png"));
				holeCardsArray[0][0]->setHiddenFrontPixmap(tempCardsPixmapArray[0]);
				holeCardsArray[0][1]->setPixmap(flipside, TRUE);
				tempCardsPixmapArray[1]= QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[1], 10)+".png"));
				holeCardsArray[0][1]->setHiddenFrontPixmap(tempCardsPixmapArray[1]);
			} else {
				tempCardsPixmapArray[0]= QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[0], 10)+".png"));
				holeCardsArray[0][0]->setPixmap(tempCardsPixmapArray[0],FALSE);
				tempCardsPixmapArray[1]= QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[1], 10)+".png"));
				holeCardsArray[0][1]->setPixmap(tempCardsPixmapArray[1],FALSE);
			}
		}
	}

	refreshGameTableStyle();
	//    qDebug() << "table: " << myGameTableStyle->getStyleDescription() << myGameTableStyle->getState();
	if(this->isVisible() && myGameTableStyle->getState() != GT_STYLE_OK) myGameTableStyle->showErrorMessage();

	//blind buttons refresh
	if(myStartWindow->getSession()->getCurrentGame()) {
		refreshButton();
		refreshGroupbox();
		provideMyActions();
	}

	// Re-init audio.
	mySDLPlayer->audioDone();
	mySDLPlayer->initAudio();
}

void gameTableImpl::initGui(int speed)
{
	//kill running Singleshots!!!
	stopTimer();

	label_Pot->setText(PotString);

	label_handNumber->setText(HandString+":");
	label_gameNumber->setText(GameString+":");

    label_Total->setText(TotalString+":");
    label_Sets->setText(BetsString+":");
	groupBox_RightToolBox->setDisabled(FALSE);

	//show human player buttons
	for(int i=0; i < USER_WIDGETS_NUMBER; i++) {
		userWidgetsArray[i]->show();
	}


	horizontalSlider_speed->setMinimum(7);

}

boost::shared_ptr<Session> gameTableImpl::getSession()
{
	assert(myStartWindow->getSession().get());
	return myStartWindow->getSession();
}

//refresh-Funktionen
void gameTableImpl::refreshSet()
{

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		if( (*it_c)->getSet() == 0 )
			setLabelArray[(*it_c)->getID()]->setText("");
		else
			setLabelArray[(*it_c)->getID()]->setText("$"+QString("%L1").arg((*it_c)->getSet()));
	}
}

void gameTableImpl::refreshButton()
{

	QPixmap dealerButton = QPixmap::fromImage(QImage(myGameTableStyle->getDealerPuck()));
	QPixmap smallblindButton = QPixmap::fromImage(QImage(myGameTableStyle->getSmallBlindPuck()));
	QPixmap bigblindButton = QPixmap::fromImage(QImage(myGameTableStyle->getBigBlindPuck()));
	QPixmap onePix = QPixmap::fromImage(QImage(myAppDataPath +"gfx/gui/misc/1px.png"));

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	PlayerList activePlayerList = currentGame->getActivePlayerList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		if( (*it_c)->getActiveStatus() ) {
			if( activePlayerList->size() > 2 ) {
				switch ( (*it_c)->getButton() ) {

				case 1 :
					buttonLabelArray[(*it_c)->getID()]->setPixmap(dealerButton);
					break;
				case 2 : {
					if(myConfig->readConfigInt("ShowBlindButtons"))
						buttonLabelArray[(*it_c)->getID()]->setPixmap(smallblindButton);
					else
						buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);
				}
				break;
				case 3 : {
					if(myConfig->readConfigInt("ShowBlindButtons"))
						buttonLabelArray[(*it_c)->getID()]->setPixmap(bigblindButton);
					else
						buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);
				}
				break;
				default:
					buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);

				}
			} else {
				switch ((*it_c)->getButton()) {

				case 2 :
					buttonLabelArray[(*it_c)->getID()]->setPixmap(dealerButton);
					break;
				case 3 : {
					if(myConfig->readConfigInt("ShowBlindButtons"))
						buttonLabelArray[(*it_c)->getID()]->setPixmap(bigblindButton);
					else
						buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);
				}
				break;
				default:
					buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);

				}
			}
		} else {
			buttonLabelArray[(*it_c)->getID()]->setPixmap(onePix);
		}
	}
}


void gameTableImpl::refreshPlayerName()
{

	if(myStartWindow->getSession()->getCurrentGame()) {

		boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
		PlayerListConstIterator it_c;
		PlayerList seatsList = currentGame->getSeatsList();
		for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {

			//collect needed infos
			// bool guest = myStartWindow->getSession()->getClientPlayerInfo((*it_c)->getUniqueID()).isGuest;
			bool guest = false;

			bool computerPlayer = false;
			if((*it_c)->getType() == PLAYER_TYPE_COMPUTER) {
				computerPlayer = true;
			}
			QString nick = QString::fromUtf8((*it_c)->getName().c_str());

			//check SeatStates and refresh
			switch(getCurrentSeatState((*it_c))) {

			case SEAT_ACTIVE: {
				playerNameLabelArray[(*it_c)->getID()]->setText(nick, FALSE, guest, computerPlayer );
			}
			break;
			case SEAT_AUTOFOLD: {
				playerNameLabelArray[(*it_c)->getID()]->setText(nick, TRUE, guest, computerPlayer );
			}
			break;
			case SEAT_STAYONTABLE: {
				playerNameLabelArray[(*it_c)->getID()]->setText(nick, TRUE, guest, computerPlayer );
			}
			break;
			case SEAT_CLEAR: {
				playerNameLabelArray[(*it_c)->getID()]->setText("");
			}
			break;
			default: {
				playerNameLabelArray[(*it_c)->getID()]->setText("");
			}
			}
		}
	}
}

void gameTableImpl::refreshPlayerAvatar()
{

	if(myStartWindow->getSession()->getCurrentGame()) {

		QPixmap onePix = QPixmap::fromImage(QImage(myAppDataPath +"gfx/gui/misc/1px.png"));

		boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
		int seatPlace;
		PlayerListConstIterator it_c;
		PlayerList seatsList = currentGame->getSeatsList();
		for (it_c=seatsList->begin(), seatPlace=0; it_c!=seatsList->end(); ++it_c, seatPlace++) {

			//get CountryString
			//QString countryString(QString(myStartWindow->getSession()->getClientPlayerInfo((*it_c)->getUniqueID()).countryCode.c_str()).toLower());
//			countryString = QString(":/cflags/cflags/%1.png").arg(countryString);

			//get AvatarPic
			QFile myAvatarFile(QString::fromUtf8((*it_c)->getAvatar().c_str()));
			QPixmap avatarPic;
			if((*it_c)->getAvatar() == "" || !myAvatarFile.exists()) {
				avatarPic = QPixmap::fromImage(QImage(myGameTableStyle->getDefaultAvatar()));
			} else {
				avatarPic = QPixmap::fromImage(QImage(QString::fromUtf8((*it_c)->getAvatar().c_str())));
			}

			//check SeatStates and refresh
			switch(getCurrentSeatState((*it_c))) {

			case SEAT_ACTIVE: {
//				qDebug() << seatPlace << "AVATAR ACTIVE";
				playerAvatarLabelArray[(*it_c)->getID()]->setPixmapAndCountry(avatarPic, "", seatPlace);
			}
			break;
			case SEAT_AUTOFOLD: {
//				qDebug() << seatPlace << "AVATAR AUTOFOLD";
				playerAvatarLabelArray[(*it_c)->getID()]->setPixmapAndCountry(avatarPic, "", seatPlace, TRUE);
			}
			break;
			case SEAT_STAYONTABLE: {
//				qDebug() << seatPlace << "AVATAR STAYONTABLE";
				playerAvatarLabelArray[(*it_c)->getID()]->setPixmapAndCountry(avatarPic, "", seatPlace, TRUE);
			}
			break;
			case SEAT_CLEAR: {
				playerAvatarLabelArray[(*it_c)->getID()]->setPixmap(onePix);
			}
			break;
			default: {
				playerAvatarLabelArray[(*it_c)->getID()]->setPixmap(onePix);
			}
			}
		}
	}
}

void gameTableImpl::setPlayerAvatar(int myID, QString myAvatar)
{

	if(myStartWindow->getSession()->getCurrentGame()) {

		boost::shared_ptr<Player> tmpPlayer = myStartWindow->getSession()->getCurrentGame()->getPlayerByUniqueId(myID);
		if (tmpPlayer.get()) {

			QFile myAvatarFile(myAvatar);
			if(myAvatarFile.exists()) {
				playerAvatarLabelArray[tmpPlayer->getID()]->setPixmap(myAvatar);
				tmpPlayer->setAvatar(myAvatar.toUtf8().constData());
			} else {
				playerAvatarLabelArray[tmpPlayer->getID()]->setPixmap(QPixmap::fromImage(QImage(myGameTableStyle->getDefaultAvatar())));
				tmpPlayer->setAvatar("");
			}
		}
	}
}

void gameTableImpl::refreshAction(int playerID, int playerAction)
{

	QPixmap onePix = QPixmap::fromImage(QImage(myAppDataPath +"gfx/gui/misc/1px.png"));
	QPixmap action;

	QStringList actionArray;
	actionArray << "" << "fold" << "check" << "call" << "bet" << "raise" << "allin";

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	if(playerID == -1 || playerAction == -1) {

		PlayerListConstIterator it_c;
		PlayerList seatsList = currentGame->getSeatsList();
		for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {

			//if no action --> clear Pixmap
			if( (*it_c)->getAction() == 0) {
				actionLabelArray[(*it_c)->getID()]->setPixmap(onePix);
			} else {
				//paint action pixmap
				actionLabelArray[(*it_c)->getID()]->setPixmap(QPixmap::fromImage(QImage(myGameTableStyle->getActionPic((*it_c)->getAction()))));
			}

			if ((*it_c)->getAction()==1) {

				if((*it_c)->getID() != 0) {
					holeCardsArray[(*it_c)->getID()][0]->setPixmap(onePix, FALSE);
					holeCardsArray[(*it_c)->getID()][1]->setPixmap(onePix, FALSE);
				}
			}
		}
	} else {
		//if no action --> clear Pixmap
		if(playerAction == 0) {
			actionLabelArray[playerID]->setPixmap(onePix);
		} else {

			// 		paint action pixmap and raise
			actionLabelArray[playerID]->setPixmap(QPixmap::fromImage(QImage(myGameTableStyle->getActionPic(playerAction))));

			//play sounds if exist
			if(myConfig->readConfigInt("PlayGameActions"))
				mySDLPlayer->playSound(actionArray[playerAction].toStdString(), playerID);
		}

		if (playerAction == 1) { // FOLD

			if (playerID == 0) {
				holeCardsArray[0][0]->startFadeOut(10);
				holeCardsArray[0][1]->startFadeOut(10);
			} else {
				holeCardsArray[playerID][0]->setPixmap(onePix, FALSE);
				holeCardsArray[playerID][1]->setPixmap(onePix, FALSE);
			}
		}
	}
}
void gameTableImpl::refreshPlayerStatistics()
{
	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
	const int nbPlayers = currentGame->getCurrentHand()->getActivePlayerList()->size();

	const string style = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu';  font-size:8pt; font-weight:400;\">"; // color:#ff0000;\">";

	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {

		if (! myConfig->readConfigInt("ShowPlayersStatistics")){
			playerTipLabelArray[(*it_c)->getID()]->setText("");
			continue;
		}

		const PlayerStatistics & stats = (*it_c)->getStatistics(nbPlayers);
		const PreflopStatistics & preflop = stats.getPreflopStatistics();
		const FlopStatistics & flop = stats.getFlopStatistics();
		const TurnStatistics & turn = stats.getTurnStatistics();
		const RiverStatistics & river = stats.getRiverStatistics();
		
		stringstream display;
		display.precision(0);

		display << fixed 
				<< style	<< "Hands:" << (int)preflop.m_hands << "</span></p>"
				<< style	<< "VP$IP:" << (int)preflop.getVoluntaryPutMoneyInPot() 
							<< " PFR:" << (int)preflop.getPreflopRaise() << "</span></p>"
				<< style	<< "Flop AFq:" << flop.getAgressionFrequency() 
							<< " CB:" << flop.getContinuationBetFrequency() << "</span></p>"
				<< style	<< "Turn AFq:" << turn.getAgressionFrequency() << "</span></p>"
				<< style	<< "River AFq:" << river.getAgressionFrequency() << "</span></p>"
							;

		playerTipLabelArray[(*it_c)->getID()]->setText(display.str().c_str());
	}
}

void gameTableImpl::refreshCash()
{

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	bool transparent = true;
	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {

		//check SeatStates and refresh
		switch(getCurrentSeatState((*it_c))) {

		case SEAT_ACTIVE: {
//			qDebug() << (*it_c)->getID() << "CASH ACTIVE";
			cashLabelArray[(*it_c)->getID()]->setText("$"+QString("%L1").arg((*it_c)->getCash()));
		}
		break;
		case SEAT_AUTOFOLD: {
//			qDebug() << (*it_c)->getID() << "CASH AUTOFOLD"; //TODO transparent
			cashLabelArray[(*it_c)->getID()]->setText("$"+QString("%L1").arg((*it_c)->getCash()), transparent);
		}
		break;
		case SEAT_STAYONTABLE: {
			cashLabelArray[(*it_c)->getID()]->setText("");
		}
		break;
		case SEAT_CLEAR: {
			cashLabelArray[(*it_c)->getID()]->setText("");
		}
		break;
		default: {
			cashLabelArray[(*it_c)->getID()]->setText("");
		}
		}
	}
}

void gameTableImpl::refreshGroupbox(int playerID, int status)
{

	int j;

	if(playerID == -1 || status == -1) {

		boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
		PlayerListConstIterator it_c;
		PlayerList seatsList = currentGame->getSeatsList();
		for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {

			if((*it_c)->getTurn()) {
				//Groupbox glow wenn der Spiele dran ist.
				myGameTableStyle->setPlayerSeatActiveStyle(groupBoxArray[(*it_c)->getID()]);
			} else {
				//Groupbox auf Hintergrundfarbe setzen wenn der Spiele nicht dran aber aktiv ist.
				if((*it_c)->getActiveStatus()) {
					if((*it_c)->getID()==0) {
						//show buttons
						for(j=0; j < USER_WIDGETS_NUMBER; j++) {
							userWidgetsArray[j]->show();
						}
					}
					myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[(*it_c)->getID()]);

				}
				//Groupbox verdunkeln wenn der Spiele inactive ist.
				else {
					if((*it_c)->getID()==0) {
						//hide buttons
						for(j=0; j < USER_WIDGETS_NUMBER; j++) {
							userWidgetsArray[j]->hide();
						}
						//disable anti-peek front after player is out
						holeCardsArray[0][0]->signalFastFlipCards(FALSE);
						holeCardsArray[0][1]->signalFastFlipCards(FALSE);
					}
					myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[(*it_c)->getID()]);
				}
			}
		}
	} else {
		switch(status) {

			//inactive
		case 0: {
			if (!playerID) {
				//hide buttons
				for(j=0; j < USER_WIDGETS_NUMBER; j++) {
					userWidgetsArray[j]->hide();
				}
				//disable anti-peek front after player is out
				holeCardsArray[0][0]->signalFastFlipCards(FALSE);
				holeCardsArray[0][1]->signalFastFlipCards(FALSE);
			}
			myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[playerID]);
		}
		break;
		//active but fold
		case 1: {
			if (!playerID) {
				//show buttons
				for(j=0; j < USER_WIDGETS_NUMBER; j++) {
					userWidgetsArray[j]->show();
				}
			}
			myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[playerID]);
		}
		break;
		//active in action
		case 2:  {
			myGameTableStyle->setPlayerSeatActiveStyle(groupBoxArray[playerID]);
		}
		break;
		//active not in action
		case 3:  {
			myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[playerID]);
		}
		break;
		default:
		{}
		}
	}
}

void gameTableImpl::refreshGameLabels(int gameState)
{

	switch(gameState) {
	case 0: {
		textLabel_handLabel->setText(PreflopString);
	}
	break;
	case 1: {
		textLabel_handLabel->setText(FlopString);
	}
	break;
	case 2: {
		textLabel_handLabel->setText(TurnString);
	}
	break;
	case 3: {
		textLabel_handLabel->setText(RiverString);
	}
	break;
	case 4: {
		textLabel_handLabel->setText("");
	}
	break;
	default: {
		textLabel_handLabel->setText("!!! ERROR !!!");
	}
	}

	label_handNumberValue->setText(QString::number(myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getID(),10));
	label_gameNumberValue->setText(QString::number(myStartWindow->getSession()->getCurrentGame()->getGameID(),10));
}

void gameTableImpl::refreshAll()
{

	refreshSet();
	refreshButton();

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		refreshAction( (*it_c)->getID(), (*it_c)->getAction());
	}

	refreshCash();
	refreshGroupbox();
	refreshPlayerName();
	refreshPlayerAvatar();
	refreshPlayerStatistics();
}

void gameTableImpl::refreshChangePlayer()
{

	refreshSet();

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();
	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		refreshAction( (*it_c)->getID(), (*it_c)->getAction());
	}

	refreshCash();
}

void gameTableImpl::refreshPot()
{
	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	textLabel_Sets->setText("$"+QString("%L1").arg(currentHand->getBoard()->getSets()));
	textLabel_Pot->setText("$"+QString("%L1").arg(currentHand->getBoard()->getPot()));
}

void gameTableImpl::guiUpdateDone()
{
	guiUpdateSemaphore.release();
}

void gameTableImpl::waitForGuiUpdateDone()
{
	guiUpdateSemaphore.acquire();
}

void gameTableImpl::dealHoleCards()
{

	int i,k;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++ ) {
		for ( k=0; k<=1; k++ ) {
			holeCardsArray[i][k]->setFadeOutAction(FALSE);
			holeCardsArray[i][k]->stopFlipCardsAnimation();
		}
	}

	QPixmap onePix = QPixmap::fromImage(QImage(myAppDataPath +"gfx/gui/misc/1px.png"));

	//TempArrays
	QPixmap tempCardsPixmapArray[2];
	int tempCardsIntArray[2];

	// Karten der Gegner und eigene Karten austeilen
	int j;
	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	PlayerListConstIterator it_c;
	PlayerList seatsList = currentGame->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		(*it_c)->getCards(tempCardsIntArray);
		for(j=0; j<2; j++) {
			if((*it_c)->getActiveStatus()) {
				if (( (*it_c)->getID() == 0)/* || DEBUG_MODE*/) {
					tempCardsPixmapArray[j].load(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[j], 10)+".png");
					if(myConfig->readConfigInt("AntiPeekMode")) {
						holeCardsArray[(*it_c)->getID()][j]->setPixmap(flipside, TRUE);
						holeCardsArray[(*it_c)->getID()][j]->setFront(flipside);
						holeCardsArray[(*it_c)->getID()][j]->setHiddenFrontPixmap(tempCardsPixmapArray[j]);
					} else {
						holeCardsArray[(*it_c)->getID()][j]->setPixmap(tempCardsPixmapArray[j],FALSE);
						holeCardsArray[(*it_c)->getID()][j]->setFront(tempCardsPixmapArray[j]);
					}
				} else {
					holeCardsArray[(*it_c)->getID()][j]->setPixmap(flipside, TRUE);
					holeCardsArray[(*it_c)->getID()][j]->setFlipsidePix(flipside);
				}
			} else {

				holeCardsArray[(*it_c)->getID()][j]->setPixmap(onePix, FALSE);
			}
		}
	}

	//fix press mouse button during bankrupt with anti-peek-mode
	this->mouseOverFlipCards(FALSE);

	//refresh CardsChanceMonitor Tool
	//refreshCardsChance(GAME_STATE_PREFLOP);
}

void gameTableImpl::dealBettingRoundCards(int myBettingRoundID)
{

	uncheckMyButtons();
	myButtonsCheckable(FALSE);
	resetButtonsCheckStateMemory();
	clearMyButtons();

	horizontalSlider_bet->setDisabled(TRUE);
	spinBox_betValue->setDisabled(TRUE);

	switch(myBettingRoundID) {

	case 1: {
		dealFlopCards0();
	}
	break;
	case 2: {
		dealTurnCards0();
	}
	break;
	case 3: {
		dealRiverCards0();
	}
	break;
	default: {
		cout << "dealBettingRoundCards() Error" << endl;
	}
	}
}


void gameTableImpl::dealFlopCards0()
{
	dealFlopCards0Timer->start(preDealCardsSpeed);
}

void gameTableImpl::dealFlopCards1()
{

	boardCardsArray[0]->setPixmap(flipside, TRUE);
	dealFlopCards1Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealFlopCards2()
{

	boardCardsArray[1]->setPixmap(flipside, TRUE);
	dealFlopCards2Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealFlopCards3()
{

	boardCardsArray[2]->setPixmap(flipside, TRUE);
	dealFlopCards3Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealFlopCards4()
{

	int tempBoardCardsArray[5];

	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
	QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[0], 10)+".png"));

	//Config? mit oder ohne Eye-Candy?
	if(myConfig->readConfigInt("ShowFlipCardsAnimation")) {
		//with Eye-Candy
		boardCardsArray[0]->startFlipCards(guiGameSpeed, card, flipside);
	} else {
		//without Eye-Candy
		boardCardsArray[0]->setFront(card);
		boardCardsArray[0]->setPixmap(card, FALSE);
	}
	dealFlopCards4Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealFlopCards5()
{

	int tempBoardCardsArray[5];
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
	QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[1], 10)+".png"));

	//Config? mit oder ohne Eye-Candy?
	if(myConfig->readConfigInt("ShowFlipCardsAnimation")) {
		//with Eye-Candy
		boardCardsArray[1]->startFlipCards(guiGameSpeed, card, flipside);
	} else {
		//without Eye-Candy
		boardCardsArray[1]->setFront(card);
		boardCardsArray[1]->setPixmap(card, FALSE);
	}
	dealFlopCards5Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealFlopCards6()
{

	int tempBoardCardsArray[5];
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
	QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[2], 10)+".png"));

	//Config? mit oder ohne Eye-Candy?
	if(myConfig->readConfigInt("ShowFlipCardsAnimation")) {
		//with Eye-Candy
		boardCardsArray[2]->startFlipCards(guiGameSpeed, card, flipside);
	} else {
		//without Eye-Candy
		boardCardsArray[2]->setFront(card);
		boardCardsArray[2]->setPixmap(card, FALSE);
	}

	// stable
	// wenn alle All In
	if(myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getAllInCondition()) {
		dealFlopCards6Timer->start(AllInDealCardsSpeed);
	}
	// sonst normale Variante
	else {
		updateMyButtonsState(0);  //mode 0 == called from dealBettingRoundcards
		dealFlopCards6Timer->start(postDealCardsSpeed);
	}

	//refresh CardsChanceMonitor Tool
	//refreshCardsChance(GAME_STATE_FLOP);
}

void gameTableImpl::dealTurnCards0()
{
	dealTurnCards0Timer->start(preDealCardsSpeed);
}

void gameTableImpl::dealTurnCards1()
{

	boardCardsArray[3]->setPixmap(flipside, TRUE);
	dealTurnCards1Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealTurnCards2()
{

	int tempBoardCardsArray[5];
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
	QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[3], 10)+".png"));

	//Config? mit oder ohne Eye-Candy?
	if(myConfig->readConfigInt("ShowFlipCardsAnimation")) {
		//with Eye-Candy
		boardCardsArray[3]->startFlipCards(guiGameSpeed, card, flipside);
	} else {
		//without Eye-Candy
		boardCardsArray[3]->setFront(card);
		boardCardsArray[3]->setPixmap(card, FALSE);
	}

	// stable
	// wenn alle All In
	if(myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getAllInCondition()) {
		dealTurnCards2Timer->start(AllInDealCardsSpeed);
	}
	// sonst normale Variante
	else {
		updateMyButtonsState(0);  //mode 0 == called from dealBettingRoundcards
		dealTurnCards2Timer->start(postDealCardsSpeed);
	}
	//refresh CardsChanceMonitor Tool
	//refreshCardsChance(GAME_STATE_TURN);
}

void gameTableImpl::dealRiverCards0()
{
	dealRiverCards0Timer->start(preDealCardsSpeed);
}

void gameTableImpl::dealRiverCards1()
{

	boardCardsArray[4]->setPixmap(flipside, TRUE);

	// 	QTimer::singleShot(dealCardsSpeed, this, SLOT( dealRiverCards2() ));
	dealRiverCards1Timer->start(dealCardsSpeed);
}

void gameTableImpl::dealRiverCards2()
{

	int tempBoardCardsArray[5];
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(tempBoardCardsArray);
	QPixmap card = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempBoardCardsArray[4], 10)+".png"));

	//Config? mit oder ohne Eye-Candy?
	if(myConfig->readConfigInt("ShowFlipCardsAnimation")) {
		//with Eye-Candy
		boardCardsArray[4]->startFlipCards(guiGameSpeed, card, flipside);
	} else {
		//without Eye-Candy
		boardCardsArray[4]->setFront(card);
		boardCardsArray[4]->setPixmap(card, FALSE);
	}

	// stable
	// wenn alle All In
	if(myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getAllInCondition()) {
		dealRiverCards2Timer->start(AllInDealCardsSpeed);
	}
	// sonst normale Variante
	else {
		updateMyButtonsState(0);  //mode 0 == called from dealBettingRoundcards
		dealRiverCards2Timer->start(postDealCardsSpeed);
	}
	//refresh CardsChanceMonitor Tool
	//refreshCardsChance(GAME_STATE_RIVER);
}

void gameTableImpl::provideMyActions(int mode)
{

	QString pushButtonFoldString;
	QString pushButtonBetRaiseString;
	QString pushButtonHalfPotBetRaiseString;
	QString pushButtonTwoThirdPotBetRaiseString;
	QString pushButtonPotBetRaiseString;
	QString lastPushButtonBetRaiseString = pushButton_BetRaise->text();
	QString pushButtonCallCheckString;
	QString pushButtonAllInString;
	QString lastPushButtonCallCheckString = pushButton_CallCheck->text();

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();
	PlayerList activePlayerList = currentHand->getActivePlayerList();

	//really disabled buttons if human player is fold/all-in or server-autofold... and not called from dealBettingRoundcards
	if((mode != 0 && (humanPlayer->getAction() == PLAYER_ACTION_ALLIN || 
		humanPlayer->getAction() == PLAYER_ACTION_FOLD || 
		(humanPlayer->getSet() == currentHand->getCurrentBettingRound()->getHighestSet() && (humanPlayer->getAction() != PLAYER_ACTION_NONE)))) 
|| !humanPlayer->isSessionActive() /*server-autofold*/) {

		pushButton_BetRaise->setText("");
		pushButton_BetRaiseHalfPot->setText("50% pot");
		pushButton_BetRaiseTwoThirdPot->setText("75% pot");
		pushButton_BetRaisePot->setText("100% pot");
		pushButton_CallCheck->setText("");
		pushButton_Fold->setText("");
		pushButton_AllIn->setText("");

		horizontalSlider_bet->setDisabled(TRUE);
		spinBox_betValue->setDisabled(TRUE);

		myButtonsCheckable(FALSE);

		refreshActionButtonFKeyIndicator(1);
	} else {
		horizontalSlider_bet->setEnabled(TRUE);
		spinBox_betValue->setEnabled(TRUE);

		//show available actions on buttons
		if(currentHand->getCurrentRound() == 0) { // preflop

			if (humanPlayer->getCash()+humanPlayer->getSet() > currentHand->getCurrentBettingRound()->getHighestSet() && !currentHand->getCurrentBettingRound()->getFullBetRule()) {
				pushButtonBetRaiseString = RaiseString+"\n$"+QString("%L1").arg(getBetAmount());
			}

			if (humanPlayer->getSet()== currentHand->getCurrentBettingRound()->getHighestSet() &&  humanPlayer->getButton() == 3) {
				pushButtonCallCheckString = CheckString;
			} else {
				pushButtonCallCheckString = CallString+"\n$"+QString("%L1").arg(getCallAmount());
			}

			pushButtonFoldString = FoldString;
			if(!currentHand->getCurrentBettingRound()->getFullBetRule()) {
				pushButtonAllInString = AllInString;
			}
		} else { // flop,turn,river

			if (currentHand->getCurrentBettingRound()->getHighestSet() == 0 && pushButton_Fold->isCheckable() ) {
				pushButtonFoldString = CheckString+" /\n"+FoldString;
			} else {
				pushButtonFoldString = FoldString;
			}
			if (currentHand->getCurrentBettingRound()->getHighestSet() == 0) {

				pushButtonCallCheckString = CheckString;
				pushButtonBetRaiseString = BetString+"\n$"+QString("%L1").arg(getBetAmount());
			}
			if (currentHand->getCurrentBettingRound()->getHighestSet() > 0 && currentHand->getCurrentBettingRound()->getHighestSet() > humanPlayer->getSet()) {
				pushButtonCallCheckString = CallString+"\n$"+QString("%L1").arg(getCallAmount());
				if (humanPlayer->getCash()+humanPlayer->getSet() > currentHand->getCurrentBettingRound()->getHighestSet() && !currentHand->getCurrentBettingRound()->getFullBetRule()) {
					pushButtonBetRaiseString = RaiseString+"\n$"+QString("%L1").arg(getBetAmount());
				}
			}
			if(!currentHand->getCurrentBettingRound()->getFullBetRule()) {
				pushButtonAllInString = AllInString;
			}
		}

		if(mode == 0) {
			if( humanPlayer->getAction() != PLAYER_ACTION_FOLD ) {
				pushButtonBetRaiseString = BetString+"\n$"+QString("%L1").arg(getBetAmount());
				pushButtonCallCheckString = CheckString;
				if( (activePlayerList->size() > 2 && humanPlayer->getButton() == BUTTON_SMALL_BLIND ) || ( activePlayerList->size() <= 2 && humanPlayer->getButton() == BUTTON_BIG_BLIND)) {
					pushButtonFoldString = FoldString;
				} else {
					pushButtonFoldString = CheckString+" /\n"+FoldString;
				}

				pushButtonAllInString = AllInString;
			} else {
				pushButtonBetRaiseString = "";
				pushButtonCallCheckString = "";
				pushButtonFoldString = "";
				pushButtonAllInString = "";
				horizontalSlider_bet->setDisabled(TRUE);
				spinBox_betValue->setDisabled(TRUE);

				myButtonsCheckable(FALSE);

			}
		}

		//if text changed on checked button --> do something to prevent unwanted actions
		if(pushButtonCallCheckString != lastPushButtonCallCheckString) {

			if(pushButton_CallCheck->isChecked()) {
				//uncheck a previous checked button to prevent unwanted action
				uncheckMyButtons();
				resetButtonsCheckStateMemory();
			}
			//disable button to prevent unwanted clicks (e.g. call allin)
			if(myConfig->readConfigInt("AccidentallyCallBlocker")) {
				pushButton_CallCheck->setEatMyEvents(true);
				enableCallCheckPushButtonTimer->start(1000);
			}

		}

		if(pushButtonBetRaiseString == "") {

			horizontalSlider_bet->setDisabled(TRUE);
			spinBox_betValue->setDisabled(TRUE);
		}

		pushButton_Fold->setText(pushButtonFoldString);
		pushButton_BetRaise->setText(pushButtonBetRaiseString);
		pushButton_BetRaiseHalfPot->setText("50% pot");
		pushButton_BetRaiseTwoThirdPot->setText("75% pot");
		pushButton_BetRaisePot->setText("100% pot");
		pushButton_CallCheck->setText(pushButtonCallCheckString);
		pushButton_AllIn->setText(pushButtonAllInString);

		refreshActionButtonFKeyIndicator();
		// 		myBetRaise();

		if(pushButton_BetRaise->text().startsWith(RaiseString)) {

			horizontalSlider_bet->setMinimum(currentHand->getCurrentBettingRound()->getHighestSet() - humanPlayer->getSet() + currentHand->getCurrentBettingRound()->getMinimumRaise());
			horizontalSlider_bet->setMaximum(humanPlayer->getCash());
			horizontalSlider_bet->setSingleStep(10);
			spinBox_betValue->setMinimum(currentHand->getCurrentBettingRound()->getHighestSet() - humanPlayer->getSet() + currentHand->getCurrentBettingRound()->getMinimumRaise());
			spinBox_betValue->setMaximum(humanPlayer->getCash());
			changeSpinBoxBetValue(horizontalSlider_bet->value());

			myActionIsRaise = 1;
		} else if(pushButton_BetRaise->text().startsWith(BetString)) {

			horizontalSlider_bet->setMinimum(currentHand->getSmallBlind()*2);
			horizontalSlider_bet->setMaximum(humanPlayer->getCash());
			horizontalSlider_bet->setSingleStep(10);
			spinBox_betValue->setMinimum(currentHand->getSmallBlind()*2);
			spinBox_betValue->setMaximum(humanPlayer->getCash());
			changeSpinBoxBetValue(horizontalSlider_bet->value());

			myActionIsBet = 1;
		} 


		//if value changed on bet/raise button --> uncheck to prevent unwanted actions
		int lastBetValue = lastPushButtonBetRaiseString.simplified().remove(QRegExp("[^0-9]")).toInt();

		if((lastBetValue < horizontalSlider_bet->minimum() && pushButton_BetRaise->isChecked())) {

			uncheckMyButtons();
			resetButtonsCheckStateMemory();
		}

		spinBox_betValue->setFocus();
		spinBox_betValue->selectAll();
	}
}

void gameTableImpl::meInAction()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getGuiInterface()->showCards(0);

	myButtonsCheckable(FALSE);

	horizontalSlider_bet->setEnabled(TRUE);
	spinBox_betValue->setEnabled(TRUE);

	myActionIsRaise = 0;
	myActionIsBet = 0;

	if(myConfig->readConfigInt("ShowStatusbarMessages")) {
		if ( myConfig->readConfigInt("AlternateFKeysUserActionMode") == 0 ) {
			// // 			statusBar()->showMessage(tr("F1 - Fold | F2 - Check/Call | F3 - Bet/Raise | F4 - All-In"), 15000);
		} else {
			// 			statusBar()->showMessage(tr("F1 - All-In | F2 - Bet/Raise | F3 - Check/Call | F4 - Fold"), 15000);
		}
	}

	QString lastPushButtonFoldString = pushButton_Fold->text();

	//paint actions on buttons
	provideMyActions();

	//do remembered action
	if( pushButtonBetRaiseIsChecked ) {
		pushButton_BetRaise->click();
		pushButtonBetRaiseIsChecked = FALSE;
	}
	if( pushButtonCallCheckIsChecked )  {
		pushButton_CallCheck->click();
		pushButtonCallCheckIsChecked = FALSE;
	}
	if( pushButtonFoldIsChecked ) {
		if(lastPushButtonFoldString == CheckString+" /\n"+FoldString && pushButton_CallCheck->text() == CheckString) {
			pushButton_CallCheck->click();
		} else {
			pushButton_Fold->click();
		}
		pushButtonFoldIsChecked = FALSE;
	}
	if( pushButtonAllInIsChecked ) {
		pushButton_AllIn->click();
		pushButtonAllInIsChecked = FALSE;
	}

	// automatic mode
	switch (playingMode) {
	case 0: // Manual mode
		break;
	case 1: // Auto check / call all
		myCallCheck();
		break;
	case 2: // Auto check / fold all
		if (pushButton_CallCheck->text() == CheckString) {
			myCheck();
		} else {
			myFold();
		}
		break;
	}
}


void gameTableImpl::disableMyButtons()
{

	boost::shared_ptr<Player> humanPlayer = myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getSeatsList()->front();

	clearMyButtons();

	//clear userWidgets
	horizontalSlider_bet->setDisabled(TRUE);
	spinBox_betValue->setDisabled(TRUE);
	horizontalSlider_bet->setMinimum(0);
	horizontalSlider_bet->setMaximum(humanPlayer->getCash());
	spinBox_betValue->setMinimum(0);
	spinBox_betValue->setMaximum(humanPlayer->getCash());
	spinBox_betValue->clear();
	horizontalSlider_bet->setValue(0);

#ifdef _WIN32
	QString humanPlayerButtonFontSize = "10";
#else
	QString humanPlayerButtonFontSize = "12";
#endif
}

void gameTableImpl::myCallCheck()
{

	if(pushButton_CallCheck->text().startsWith(CallString)) {
		myCall();
	}
	if(pushButton_CallCheck->text() == CheckString) {
		myCheck();
	}
}

void gameTableImpl::myFold()
{

	if(pushButton_Fold->text() == FoldString) {

		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();
		humanPlayer->setAction(PLAYER_ACTION_FOLD);
		humanPlayer->setTurn(0);

		//set that i was the last active player. need this for unhighlighting groupbox
		currentHand->setPreviousPlayerID(0);

		// 		statusBar()->clearMessage();

		//Spiel läuft weiter
		myActionDone();
	}
}

void gameTableImpl::myCheck()
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();
	humanPlayer->setTurn(0);
	humanPlayer->setAction(PLAYER_ACTION_CHECK);

	//set that i was the last active player. need this for unhighlighting groupbox
	currentHand->setPreviousPlayerID(0);

	// 	statusBar()->clearMessage();

	//Spiel läuft weiter
	myActionDone();
}

int gameTableImpl::getCallAmount()
{

	int tempHighestSet = 0;

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();
	tempHighestSet = currentHand->getCurrentBettingRound()->getHighestSet();

	if (humanPlayer->getCash() + humanPlayer->getSet() <= tempHighestSet) {

		return humanPlayer->getCash();
	} else {
		return tempHighestSet - humanPlayer->getSet();
	}
}

int gameTableImpl::getBetRaisePushButtonValue()
{

	int betValue = pushButton_BetRaise->text().simplified().remove(QRegExp("[^0-9]")).toInt();
	return betValue;
}

int gameTableImpl::getBetAmount()
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();

	int betValue = getBetRaisePushButtonValue();
	int minimum;

	minimum = currentHand->getCurrentBettingRound()->getHighestSet() - humanPlayer->getSet() + currentHand->getCurrentBettingRound()->getMinimumRaise();

	if(betValue < minimum) {
		return min(minimum,humanPlayer->getCash());
	} else {
		return betValue;
	}
}

void gameTableImpl::myCall()
{

	int tempHighestSet = 0;
	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();

	tempHighestSet = currentHand->getCurrentBettingRound()->getHighestSet();

	if (humanPlayer->getCash() + humanPlayer->getSet() <= tempHighestSet) {

		humanPlayer->setSet(humanPlayer->getCash());
		humanPlayer->setCash(0);
		humanPlayer->setAction(PLAYER_ACTION_ALLIN);
	} else {
		humanPlayer->setSet(tempHighestSet - humanPlayer->getSet());
		humanPlayer->setAction(PLAYER_ACTION_CALL);
	}
	humanPlayer->setTurn(0);

	currentHand->getBoard()->collectSets();
	refreshPot();

	//set that i was the last active player. need this for unhighlighting groupbox
	currentHand->setPreviousPlayerID(0);

	// 	statusBar()->clearMessage();

	//Spiel läuft weiter
	myActionDone();
}

void gameTableImpl::mySet()
{
	GameState currentState = myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->getBettingRoundID();

	if(pushButton_BetRaise->text() != "") {

		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();

		int tempCash = humanPlayer->getCash();

		// 		cout << "Set-Value " << getBetRaisePushButtonValue() << endl;
		humanPlayer->setSet(getBetRaisePushButtonValue());

		if (getBetRaisePushButtonValue() >= tempCash ) {

			humanPlayer->setSet(humanPlayer->getCash());
			humanPlayer->setCash(0);
			humanPlayer->setAction(PLAYER_ACTION_ALLIN);

			// full bet rule
			if(currentHand->getCurrentBettingRound()->getHighestSet() + currentHand->getCurrentBettingRound()->getMinimumRaise() > humanPlayer->getSet()) {
				currentHand->getCurrentBettingRound()->setFullBetRule(true);
			}
		}

		if(myActionIsRaise) {
			//do not if allIn
			if(humanPlayer->getAction() != 6) {
				humanPlayer->setAction(PLAYER_ACTION_RAISE);
			}
			myActionIsRaise = 0;

			currentHand->getCurrentBettingRound()->setMinimumRaise(humanPlayer->getSet() - currentHand->getCurrentBettingRound()->getHighestSet());
		}

		if(myActionIsBet) {
			//do not if allIn
			if(humanPlayer->getAction() != 6) {
				humanPlayer->setAction(PLAYER_ACTION_BET);
			}
			myActionIsBet = 0;

			currentHand->getCurrentBettingRound()->setMinimumRaise(humanPlayer->getSet());
		}

		currentHand->getCurrentBettingRound()->setHighestSet(humanPlayer->getSet());

		humanPlayer->setTurn(0);

		currentHand->getBoard()->collectSets();
		refreshPot();

		// 		statusBar()->clearMessage();

		//set that i was the last active player. need this for unhighlighting groupbox
		currentHand->setPreviousPlayerID(0);

		// lastPlayerAction für Karten umblättern reihenfolge setzrn
		currentHand->setLastActionPlayerID(humanPlayer->getUniqueID());

		//Spiel läuft weiter
		myActionDone();
	}
}

void gameTableImpl::myAllIn()
{

	if(pushButton_AllIn->text() == AllInString) {

		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		boost::shared_ptr<Player> humanPlayer = currentHand->getSeatsList()->front();

		humanPlayer->setSet(humanPlayer->getCash());
		humanPlayer->setCash(0);
		humanPlayer->setAction(PLAYER_ACTION_ALLIN);

		// full bet rule
		if(currentHand->getCurrentBettingRound()->getHighestSet() + currentHand->getCurrentBettingRound()->getMinimumRaise() > humanPlayer->getSet()) {
			currentHand->getCurrentBettingRound()->setFullBetRule(true);
		}

		if(humanPlayer->getSet() > currentHand->getCurrentBettingRound()->getHighestSet()) {
			currentHand->getCurrentBettingRound()->setMinimumRaise(humanPlayer->getSet() - currentHand->getCurrentBettingRound()->getHighestSet());

			currentHand->getCurrentBettingRound()->setHighestSet(humanPlayer->getSet());

			// lastPlayerAction für Karten umblättern reihenfolge setzrn
			currentHand->setLastActionPlayerID(humanPlayer->getUniqueID());

		}

		humanPlayer->setTurn(0);

		currentHand->getBoard()->collectSets();
		refreshPot();

		//set that i was the last active player. need this for unhighlighting groupbox
		currentHand->setPreviousPlayerID(0);

		//Spiel läuft weiter
		myActionDone();
	}
}


void gameTableImpl::pushButtonBetRaiseClicked(bool checked)
{

	if (pushButton_BetRaise->isCheckable()) {
		if(checked) {
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_Fold->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonCallCheckIsChecked = FALSE;
			pushButtonFoldIsChecked = FALSE;
			pushButtonAllInIsChecked = FALSE;

			pushButtonBetRaiseIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();

		} else {
			pushButtonBetRaiseIsChecked = FALSE;
			myLastPreActionBetValue = 0;
		}
	} else {
		mySet();
	}
}
void gameTableImpl::pushButtonBetRaiseHalfPotClicked(bool checked)
{

	if (pushButton_BetRaiseHalfPot->isCheckable()) {
		if(checked) {
			pushButton_BetRaiseTwoThirdPot->setChecked(FALSE);
			pushButton_BetRaisePot->setChecked(FALSE);
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_Fold->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonCallCheckIsChecked = FALSE;
			pushButtonFoldIsChecked = FALSE;
			pushButtonAllInIsChecked = FALSE;

			pushButtonBetRaiseHalfPotIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();

		} else {
			pushButtonBetRaiseHalfPotIsChecked = FALSE;
			myLastPreActionBetValue = 0;
		}
	} else {

		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		int amount = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();

		amount = amount / 2;

		pushButton_BetRaise->setText("");
	    QString betRaise = currentHand->getCurrentBettingRound()->getHighestSet() == 0 ? BetString : RaiseString;
        pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(amount));
		mySet();
	}
}
void gameTableImpl::pushButtonBetRaiseTwoThirdPotClicked(bool checked)
{

	if (pushButton_BetRaiseTwoThirdPot->isCheckable()) {
		if(checked) {
			pushButton_BetRaiseHalfPot->setChecked(FALSE);
			pushButton_BetRaisePot->setChecked(FALSE);
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_Fold->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonCallCheckIsChecked = FALSE;
			pushButtonFoldIsChecked = FALSE;
			pushButtonAllInIsChecked = FALSE;

			pushButtonBetRaiseTwoThirdPotIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();

		} else {
			pushButtonBetRaiseTwoThirdPotIsChecked = FALSE;
			myLastPreActionBetValue = 0;
		}
	} else {
		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		int amount = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();

		amount = amount * 0.75;

		pushButton_BetRaise->setText("");
	    QString betRaise = currentHand->getCurrentBettingRound()->getHighestSet() == 0 ? BetString : RaiseString;
        pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(amount));
		mySet();
	}
}
void gameTableImpl::pushButtonBetRaisePotClicked(bool checked)
{

	if (pushButton_BetRaisePot->isCheckable()) {
		if(checked) {
			pushButton_BetRaiseHalfPot->setChecked(FALSE);
			pushButton_BetRaiseTwoThirdPot->setChecked(FALSE);
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_Fold->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonCallCheckIsChecked = FALSE;
			pushButtonFoldIsChecked = FALSE;
			pushButtonAllInIsChecked = FALSE;

			pushButtonBetRaisePotIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();

		} else {
			pushButtonBetRaisePotIsChecked = FALSE;
			myLastPreActionBetValue = 0;
		}
	} else {

		boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
		int amount = currentHand->getBoard()->getPot()+ currentHand->getBoard()->getSets();

		pushButton_BetRaise->setText("");
	    QString betRaise = currentHand->getCurrentBettingRound()->getHighestSet() == 0 ? BetString : RaiseString;
        pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(amount));
		mySet();
	}
}
void gameTableImpl::pushButtonCallCheckClicked(bool checked)
{

	if (pushButton_CallCheck->isCheckable()) {
		if(checked) {
			pushButton_Fold->setChecked(FALSE);
			pushButton_BetRaise->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonAllInIsChecked = FALSE;
			pushButtonFoldIsChecked = FALSE;
			pushButtonBetRaiseIsChecked = FALSE;

			pushButtonCallCheckIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();
		} else {
			pushButtonCallCheckIsChecked = FALSE;
		}
	} else {
		myCallCheck();
	}
}

void gameTableImpl::pushButtonFoldClicked(bool checked)
{

	if (pushButton_Fold->isCheckable()) {
		if(checked) {
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_BetRaise->setChecked(FALSE);
			pushButton_AllIn->setChecked(FALSE);

			pushButtonAllInIsChecked = FALSE;
			pushButtonCallCheckIsChecked = FALSE;
			pushButtonBetRaiseIsChecked = FALSE;

			pushButtonFoldIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();
		} else {
			pushButtonFoldIsChecked = FALSE;
		}
	} else {
		myFold();
	}
}

void gameTableImpl::pushButtonAllInClicked(bool checked)
{

	if (pushButton_AllIn->isCheckable()) {
		if(checked) {
			pushButton_CallCheck->setChecked(FALSE);
			pushButton_BetRaise->setChecked(FALSE);
			pushButton_Fold->setChecked(FALSE);

			pushButtonFoldIsChecked = FALSE;
			pushButtonCallCheckIsChecked = FALSE;
			pushButtonBetRaiseIsChecked = FALSE;

			pushButtonAllInIsChecked = TRUE;

			if(!radioButton_manualAction->isChecked())
				radioButton_manualAction->click();
		} else {
			pushButtonAllInIsChecked = FALSE;
		}
	} else {
		myAllIn();
	}
}

void gameTableImpl::myActionDone()
{
	boost::shared_ptr<Player> humanPlayer = myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getSeatsList()->front();
	GameState currentState = myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->getBettingRoundID();
	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	if (currentState == GAME_STATE_PREFLOP){
		humanPlayer->getCurrentHandActions().getPreflopActions().push_back(humanPlayer->getAction());
		humanPlayer->updatePreflopStatistics();
		if (humanPlayer->getAction() == PLAYER_ACTION_RAISE || humanPlayer->getAction() == PLAYER_ACTION_ALLIN)
			currentHand->setPreflopLastRaiserID(humanPlayer->getUniqueID());
	}
	else
	if (currentState == GAME_STATE_FLOP){
		humanPlayer->getCurrentHandActions().getFlopActions().push_back(humanPlayer->getAction());
		humanPlayer->updateFlopStatistics();
	}
	else
	if (currentState == GAME_STATE_TURN){
		humanPlayer->getCurrentHandActions().getTurnActions().push_back(humanPlayer->getAction());
		humanPlayer->updateTurnStatistics();
	}
	else
	if (currentState == GAME_STATE_RIVER){
		humanPlayer->getCurrentHandActions().getRiverActions().push_back(humanPlayer->getAction());
		humanPlayer->updateRiverStatistics();
	}


	disableMyButtons();

	nextPlayerAnimation();

	//prevent escape button working while allIn
	myActionIsRaise = 0;
	myActionIsBet = 0;

#ifdef LOG_POKER_EXEC

	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	PlayerAction myAction = humanPlayer->getAction();

	cout << endl << "\t" << humanPlayer->getPositionLabel(humanPlayer->getPosition()) 
		<< "\t" << humanPlayer->getName() 
		<< "\t" << humanPlayer->getCardsValueString()   
		<< "\t" <<  "stack = " << humanPlayer->getCash() 
		<< ", pot = " << currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets()
		<< "\tPFR : " << humanPlayer->getStatistics(nbPlayers).getPreflopStatistics().getPreflopRaise() << endl;

	if (myAction == PLAYER_ACTION_FOLD)
		cout << "FOLD";
	else
	if (myAction == PLAYER_ACTION_BET)
		cout << "BET ";
	else
	if (myAction == PLAYER_ACTION_RAISE)
		cout << "RAISE ";
	else
	if (myAction == PLAYER_ACTION_CALL)
		cout << "CALL ";
	else
	if (myAction == PLAYER_ACTION_CHECK)
		cout << "CHECK";
	else
	if (myAction == PLAYER_ACTION_ALLIN)
		cout << "ALLIN ";
	else
	if (myAction == PLAYER_ACTION_NONE)
		cout << "NONE";
	else
		cout << "undefined ?";

	cout << endl << endl << "---------------------------------------------------------------------------------" << endl << endl;
#endif
}

void gameTableImpl::nextPlayerAnimation()
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	//refresh Change Player
	refreshSet();

	PlayerListConstIterator it_c;
	PlayerList seatsList = currentHand->getSeatsList();
	for (it_c=seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		if((*it_c)->getID() == currentHand->getPreviousPlayerID()) break;
	}

	if(currentHand->getPreviousPlayerID() != -1) {
		refreshAction(currentHand->getPreviousPlayerID(), (*it_c)->getAction());
	}
	refreshCash();

	//refresh actions for human player
	updateMyButtonsState();

	nextPlayerAnimationTimer->start(nextPlayerSpeed1);
}

void gameTableImpl::beRoAnimation2(int myBettingRoundID)
{

	switch(myBettingRoundID) {

	case 0: {
		preflopAnimation2();
	}
	break;
	case 1: {
		flopAnimation2();
	}
	break;
	case 2: {
		turnAnimation2();
	}
	break;
	case 3: {
		riverAnimation2();
	}
	break;
	default: {
		cout << "beRoAnimation2() Error" << endl;
	}
	}
}


void gameTableImpl::preflopAnimation1()
{
	preflopAnimation1Timer->start(nextPlayerSpeed2);
}
void gameTableImpl::preflopAnimation1Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->run();
}

void gameTableImpl::preflopAnimation2()
{
	preflopAnimation2Timer->start(preflopNextPlayerSpeed);
}
void gameTableImpl::preflopAnimation2Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->nextPlayer();
}


void gameTableImpl::flopAnimation1()
{
	flopAnimation1Timer->start(nextPlayerSpeed2);
}
void gameTableImpl::flopAnimation1Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->run();
}

void gameTableImpl::flopAnimation2()
{
	flopAnimation2Timer->start(nextPlayerSpeed3);
}
void gameTableImpl::flopAnimation2Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->nextPlayer();
}

void gameTableImpl::turnAnimation1()
{
	turnAnimation1Timer->start(nextPlayerSpeed2);
}
void gameTableImpl::turnAnimation1Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->run();
}

void gameTableImpl::turnAnimation2()
{
	turnAnimation2Timer->start(nextPlayerSpeed3);
}
void gameTableImpl::turnAnimation2Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->nextPlayer();
}

void gameTableImpl::riverAnimation1()
{
	riverAnimation1Timer->start(nextPlayerSpeed2);
}
void gameTableImpl::riverAnimation1Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->run();
}

void gameTableImpl::riverAnimation2()
{
	riverAnimation2Timer->start(nextPlayerSpeed3);
}
void gameTableImpl::riverAnimation2Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->nextPlayer();
}

void gameTableImpl::postRiverAnimation1()
{
	postRiverAnimation1Timer->start(nextPlayerSpeed2);
}
void gameTableImpl::postRiverAnimation1Action()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getCurrentBettingRound()->postRiverRun();
}

void gameTableImpl::postRiverRunAnimation1()
{
	postRiverRunAnimation1Timer->start(postRiverRunAnimationSpeed);
}

void gameTableImpl::postRiverRunAnimation2()
{

	uncheckMyButtons();
	myButtonsCheckable(FALSE);
	clearMyButtons();
	resetButtonsCheckStateMemory();

	horizontalSlider_bet->setDisabled(TRUE);
	spinBox_betValue->setDisabled(TRUE);

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	int nonfoldPlayersCounter = 0;
	PlayerListConstIterator it_c;
	PlayerList activePlayerList = currentGame->getActivePlayerList();
	for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if ((*it_c)->getAction() != PLAYER_ACTION_FOLD)
			nonfoldPlayersCounter++;
	}

	if(nonfoldPlayersCounter!=1) {

		if(!flipHolecardsAllInAlreadyDone) {

			for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
				if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->checkIfINeedToShowCards()) {

					showHoleCards((*it_c)->getUniqueID());
				}
			}
			//Wenn einmal umgedreht dann fertig!!
			flipHolecardsAllInAlreadyDone = TRUE;
		} else {
			for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
				if((*it_c)->getAction() != PLAYER_ACTION_FOLD) {
					//set Player value (logging) for all in already shown cards
					(*it_c)->setCardsFlip(1,3);
				}
			}
		}
		postRiverRunAnimation2Timer->start(postRiverRunAnimationSpeed);
	} else {

		postRiverRunAnimation3();
	}

}

void gameTableImpl::postRiverRunAnimation3()
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	int nonfoldPlayerCounter = 0;
	PlayerListConstIterator it_c;

	PlayerList activePlayerList = currentHand->getActivePlayerList();
	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getAction() != PLAYER_ACTION_FOLD) {
			nonfoldPlayerCounter++;
		}
	}

	list<unsigned> winners = currentHand->getBoard()->getWinners();

	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() == currentHand->getCurrentBettingRound()->getHighestCardsValue() ) {

			//Show "Winner" label
			actionLabelArray[(*it_c)->getID()]->setPixmap(QPixmap::fromImage(QImage(myGameTableStyle->getActionPic(7))));

			//show winnercards if more than one player is active TODO
			if ( nonfoldPlayerCounter != 1 && myConfig->readConfigInt("ShowFadeOutCardsAnimation")) {

				int j;
				int bestHandPos[5];
				(*it_c)->getBestHandPosition(bestHandPos);

				bool index0 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 0 ) {
						index0 = FALSE;
					}
				}
				if (index0) {
					holeCardsArray[(*it_c)->getID()][0]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index0" << endl;*/
				}
				//index 1 testen
				bool index1 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 1 ) {
						index1 = FALSE;
					}
				}
				if (index1) {
					holeCardsArray[(*it_c)->getID()][1]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index1" << endl;*/
				}
				//index 2 testen
				bool index2 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 2 ) {
						index2 = FALSE;
					}
				}
				if (index2) {
					boardCardsArray[0]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index2" << endl;*/
				}
				//index 3 testen
				bool index3 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 3 ) {
						index3 = FALSE;
					}
				}
				if (index3) {
					boardCardsArray[1]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index3" << endl;*/
				}
				//index 4 testen
				bool index4 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 4 ) {
						index4 = FALSE;
					}
				}
				if (index4) {
					boardCardsArray[2]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index4" << endl;*/
				}
				//index 5 testen
				bool index5 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 5 ) {
						index5 = FALSE;
					}
				}
				if (index5) {
					boardCardsArray[3]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index5" << endl;*/
				}
				//index 6 testen
				bool index6 = TRUE;
				for(j=0; j<5; j++) {
					if (bestHandPos[j] == 6 ) {
						index6 = FALSE;
					}
				}
				if (index6) {
					boardCardsArray[4]->startFadeOut(guiGameSpeed); /*cout << "Fade Out index6" << endl;*/
				}
			}
			//Pot-Verteilung Loggen
			//Wenn River dann auch das Blatt loggen!
			// 			if (textLabel_handLabel->text() == "River") {

			//set Player value (logging)
			myGuiLog->logPlayerWinsMsg(QString::fromUtf8((*it_c)->getName().c_str()),(*it_c)->getLastMoneyWon(),true);

			// 			}
			// 			else {
			// 				myLog->logPlayerWinsMsg(i, pot);
			// 			}
		} else {

			if( activePlayerList->size() != 1 && (*it_c)->getAction() != PLAYER_ACTION_FOLD && myConfig->readConfigInt("ShowFadeOutCardsAnimation")
			  ) {

				//aufgedeckte Gegner auch ausblenden
				holeCardsArray[(*it_c)->getID()][0]->startFadeOut(guiGameSpeed);
				holeCardsArray[(*it_c)->getID()][1]->startFadeOut(guiGameSpeed);
			}
		}
	}

	// log side pot winners -> TODO
	list<unsigned>::iterator it_int;
	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() != currentHand->getCurrentBettingRound()->getHighestCardsValue() ) {

			for(it_int = winners.begin(); it_int != winners.end(); ++it_int) {
				if((*it_int) == (*it_c)->getUniqueID()) {
					myGuiLog->logPlayerWinsMsg(QString::fromUtf8((*it_c)->getName().c_str()), (*it_c)->getLastMoneyWon(), false);
				}
			}

		}
	}

	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getCash() == 0) {
//			currentHand->getGuiInterface()->logPlayerSitsOut((*it_c)->getName());
		}
	}

//	textBrowser_Log->append("");

	postRiverRunAnimation3Timer->start(postRiverRunAnimationSpeed/2);
}

void gameTableImpl::postRiverRunAnimation4()
{

	distributePotAnimCounter=0;
	potDistributeTimer->start(winnerBlinkSpeed);
}

void gameTableImpl::postRiverRunAnimation5()
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	PlayerList activePlayerList = currentHand->getActivePlayerList();
	PlayerListConstIterator it_c;

	if (distributePotAnimCounter<10) {

		if (distributePotAnimCounter==0 || distributePotAnimCounter==2 || distributePotAnimCounter==4 || distributePotAnimCounter==6 || distributePotAnimCounter==8) {

#ifndef GUI_800x480
			label_Pot->setText("");
#endif

			for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

				if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() == currentHand->getCurrentBettingRound()->getHighestCardsValue() ) {

					playerNameLabelArray[(*it_c)->getID()]->hide();
				}
			}
		} else {
#ifndef GUI_800x480
			label_Pot->setText(PotString);
#endif

			for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

				if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() == currentHand->getCurrentBettingRound()->getHighestCardsValue() ) {

					playerNameLabelArray[(*it_c)->getID()]->show();
				}
			}
		}

		distributePotAnimCounter++;
	} else {
		potDistributeTimer->stop();
		postRiverRunAnimation5Timer->start(gameSpeed);
	}
}

void gameTableImpl::postRiverRunAnimation6()
{
	int i;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		playerNameLabelArray[i]->show();
	}

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	refreshCash();
	refreshPot();

	// if 1 active playerleft, open "new game" dialog
	int playersPositiveCashCounter = 0;

	PlayerListConstIterator it_c;
	PlayerList activePlayerList = currentHand->getActivePlayerList();
	for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

		if ((*it_c)->getCash() > 0) playersPositiveCashCounter++;
	}

	if (playersPositiveCashCounter==1) {

		for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

			if ((*it_c)->getCash() > 0) {
				currentHand->getGuiInterface()->logPlayerWinGame((*it_c)->getName(),  
					myStartWindow->getSession()->getCurrentGame()->getGameID());
			}
		}

		currentGameOver = TRUE;

		pushButton_break->setDisabled(FALSE);
		QFontMetrics tempMetrics = this->fontMetrics();
		int width = tempMetrics.width(tr("Start"));

		pushButton_break->setMinimumSize(width+10,20);
		pushButton_break->setText(tr("Start"));
		blinkingStartButtonAnimationTimer->start(500);

		return;
	}

	postRiverRunAnimation6Timer->start(newRoundSpeed);

}

void gameTableImpl::showHoleCards(unsigned playerId, bool allIn)
{
	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();
	//TempArrays
	QPixmap tempCardsPixmapArray[2];
	int tempCardsIntArray[2];
	int showFlipcardAnimation = myConfig->readConfigInt("ShowFlipCardsAnimation");
	int j;
	PlayerListConstIterator it_c;
	PlayerList activePlayerList = currentHand->getActivePlayerList();
	for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

		if((*it_c)->getUniqueID() == playerId) {

			(*it_c)->getCards(tempCardsIntArray);
			for(j=0; j<2; j++) {

				if(showFlipcardAnimation) { // with Eye-Candy
					holeCardsArray[(*it_c)->getID()][j]->startFlipCards(guiGameSpeed, QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[j], 10)+".png")), flipside);
				} else { //without Eye-Candy
					tempCardsPixmapArray[j] = QPixmap::fromImage(QImage(myCardDeckStyle->getCurrentDir()+QString::number(tempCardsIntArray[j], 10)+".png"));
					holeCardsArray[(*it_c)->getID()][j]->setPixmap(tempCardsPixmapArray[j], FALSE);
				}
			}
			//set Player value (logging)
			if(currentHand->getCurrentRound() < GAME_STATE_RIVER || allIn) {
				(*it_c)->setCardsFlip(1,2); //for BettingRound before postriver or allin just log the hole cards
			} else {
				(*it_c)->setCardsFlip(1,1); //for postriver log the value
			}
		}
	}
}

void gameTableImpl::flipHolecardsAllIn()
{

	boost::shared_ptr<Game> currentGame = myStartWindow->getSession()->getCurrentGame();

	if(!flipHolecardsAllInAlreadyDone && currentGame->getCurrentHand()->getCurrentRound() < GAME_STATE_RIVER) {
		//Aktive Spieler zählen --> wenn nur noch einer nicht-folded dann keine Karten umdrehen
		int nonfoldPlayersCounter = 0;
		PlayerListConstIterator it_c;
		PlayerList activePlayerList = currentGame->getActivePlayerList();
		for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
			if ((*it_c)->getAction() != PLAYER_ACTION_FOLD) nonfoldPlayersCounter++;
		}

		if(nonfoldPlayersCounter!=1) {
			for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
				if((*it_c)->getAction() != PLAYER_ACTION_FOLD) {

					showHoleCards((*it_c)->getUniqueID());
				}
			}
		}

		//Wenn einmal umgedreht dann fertig!!
		flipHolecardsAllInAlreadyDone = TRUE;
	}
}


void gameTableImpl::startNewHand()
{

	if( !breakAfterCurrentHand) {
		myStartWindow->getSession()->getCurrentGame()->initHand();
		myStartWindow->getSession()->getCurrentGame()->startHand();
	} else {

		pushButton_break->setDisabled(FALSE);

		QFontMetrics tempMetrics = this->fontMetrics();
		int width = tempMetrics.width(tr("Start"));
		pushButton_break->setMinimumSize(width+10,20);
		pushButton_break->setText(tr("Start"));
		breakAfterCurrentHand=FALSE;
		blinkingStartButtonAnimationTimer->start(500);
	}
}

void gameTableImpl::handSwitchRounds()
{
	myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->switchRounds();
}

void gameTableImpl::nextRoundCleanGui()
{

	int i,j;

	// GUI bereinigen - Bilder löschen, Animationen unterbrechen
	QPixmap onePix = QPixmap::fromImage(QImage(myAppDataPath +"gfx/gui/misc/1px.png"));
	for (i=0; i<5; i++ ) {
		boardCardsArray[i]->setPixmap(onePix, FALSE);
		boardCardsArray[i]->setFadeOutAction(FALSE);
		boardCardsArray[i]->stopFlipCardsAnimation();

	}
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++ ) {
		for ( j=0; j<=1; j++ ) {
			holeCardsArray[i][j]->setFadeOutAction(FALSE);
			holeCardsArray[i][j]->stopFlipCardsAnimation();
		}
	}

	// for startNewGame during human player is active
	if(myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getSeatsList()->front()->getActiveStatus() == 1) {
		disableMyButtons();
	}

	textLabel_handLabel->setText("");

	refreshAll();

	flipHolecardsAllInAlreadyDone = FALSE;

	//Wenn Pause zwischen den Hands in der Konfiguration steht den Stop Button drücken!
	if (myConfig->readConfigInt("PauseBetweenHands") ) {

		pushButton_break->click();

	} else {
		//FIX STRG+N Bug

		pushButton_break->setEnabled(TRUE);
		breakAfterCurrentHand=FALSE;
	}

	//Clean breakbutton
	blinkingStartButtonAnimationTimer->stop();
	myGameTableStyle->setBreakButtonStyle(pushButton_break,0);

	blinkingStartButtonAnimationTimer->stop();
	QFontMetrics tempMetrics = this->fontMetrics();
	int width = tempMetrics.width(tr("Stop"));
	pushButton_break->setMinimumSize(width+10,20);
	pushButton_break->setText(tr("Stop"));

	//Clear Statusbarmessage
	// 	statusBar()->clearMessage();

	//fix press mouse button during bankrupt with anti-peek-mode
	this->mouseOverFlipCards(FALSE);

	horizontalSlider_bet->setDisabled(TRUE);
	spinBox_betValue->setDisabled(TRUE);

	uncheckMyButtons();
	myButtonsCheckable(FALSE);
	resetButtonsCheckStateMemory();
	clearMyButtons();
}

void gameTableImpl::stopTimer()
{

	dealFlopCards0Timer->stop();
	dealFlopCards1Timer->stop();
	dealFlopCards2Timer->stop();
	dealFlopCards3Timer->stop();
	dealFlopCards4Timer->stop();
	dealFlopCards5Timer->stop();
	dealFlopCards6Timer->stop();
	dealTurnCards0Timer->stop();
	dealTurnCards1Timer->stop();
	dealTurnCards2Timer->stop();
	dealRiverCards0Timer->stop();
	dealRiverCards1Timer->stop();
	dealRiverCards2Timer->stop();

	nextPlayerAnimationTimer->stop();
	preflopAnimation1Timer->stop();
	preflopAnimation2Timer->stop();
	flopAnimation1Timer->stop();
	flopAnimation2Timer->stop();
	turnAnimation1Timer->stop();
	turnAnimation2Timer->stop();
	riverAnimation1Timer->stop();
	riverAnimation2Timer->stop();

	postRiverAnimation1Timer->stop();
	postRiverRunAnimation1Timer->stop();
	postRiverRunAnimation2Timer->stop();
	postRiverRunAnimation3Timer->stop();
	postRiverRunAnimation5Timer->stop();
	postRiverRunAnimation6Timer->stop();
	potDistributeTimer->stop();
}

void gameTableImpl::setSpeeds()
{

	gameSpeed = (11-guiGameSpeed)*10;
	dealCardsSpeed = (gameSpeed/2)*10; //milliseconds
	preDealCardsSpeed = dealCardsSpeed*2; //Zeit for Karten aufdecken auf dem Board (Flop, Turn, River)
	postDealCardsSpeed = dealCardsSpeed*3; //Zeit nach Karten aufdecken auf dem Board (Flop, Turn, River)
	AllInDealCardsSpeed = dealCardsSpeed*4; //Zeit nach Karten aufdecken auf dem Board (Flop, Turn, River) bei AllIn
	postRiverRunAnimationSpeed = gameSpeed*18;
	winnerBlinkSpeed = gameSpeed*3; //milliseconds
	newRoundSpeed = gameSpeed*35;
	nextPlayerSpeed1 = gameSpeed*10; // Zeit zwischen dem Setzen des Spielers und dem Verdunkeln
	nextPlayerSpeed2 = gameSpeed*4; // Zeit zwischen Verdunkeln des einen und aufhellen des anderen Spielers
	nextPlayerSpeed3 = gameSpeed*7; // Zeit bis zwischen Aufhellen und Aktion
	preflopNextPlayerSpeed = gameSpeed*10; // Zeit bis zwischen Aufhellen und Aktion im Preflop (etwas langsamer da nicht gerechnet wird. )
}

void gameTableImpl::breakButtonClicked()
{

	if (pushButton_break->text() == tr("Stop")) {
		pushButton_break->setDisabled(TRUE);
		breakAfterCurrentHand=TRUE;
	} else if (pushButton_break->text() == tr("Lobby")) {
//		leaveCurrentNetworkGame();
	} else if (pushButton_break->text() == tr("Start")) {

		blinkingStartButtonAnimationTimer->stop();
		//Set default Color
		myGameTableStyle->setBreakButtonStyle(pushButton_break,0);
		QFontMetrics tempMetrics = this->fontMetrics();
		int width = tempMetrics.width(tr("Stop"));
		pushButton_break->setMinimumSize(width+10,20);

		pushButton_break->setText(tr("Stop"));

		if(currentGameOver) {
			//let the SoundEventHandler know that there is a new game
			mySoundEventHandler->newGameStarts();

			currentGameOver = FALSE;
			myStartWindow->callNewGameDialog();
			//Bei Cancel nichts machen!!!
		} else {
			startNewHand();
		}
	}
}

void gameTableImpl::keyPressEvent ( QKeyEvent * event )
{

	// 	cout << event->key() << endl;

	//bool ctrlPressed = FALSE;

	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return ) { /*ENTER*/
		if(spinBox_betValue->hasFocus()) {
			pushButton_BetRaise->click();
		}
	}
	if (event->key() == Qt::Key_F1) {
		if (myConfig->readConfigInt("AlternateFKeysUserActionMode") == 0) {
			pushButton_Fold->click();
		} else {
			pushButton_AllIn->click();
		}
	}
	if (event->key() == Qt::Key_F2) {
		if (myConfig->readConfigInt("AlternateFKeysUserActionMode") == 0) {
			pushButton_CallCheck->click();
		} else {
			pushButton_BetRaise->click();
		}

	}
	if (event->key() == Qt::Key_F3 ) {
		if (myConfig->readConfigInt("AlternateFKeysUserActionMode") == 0) {
			pushButton_BetRaise->click();
		} else {
			pushButton_CallCheck->click();
		}
	}
	if (event->key() == Qt::Key_F6) {
		radioButton_manualAction->click();
	}
	if (event->key() == Qt::Key_F7) {
//		radioButton_autoCheckFold->click();
	}
	if (event->key() == Qt::Key_F8) {
	//	radioButton_autoCheckCallAny->click();
	}
	if (event->key() == Qt::Key_Shift) {
		pushButton_break->click();
			//ctrlPressed = TRUE;
	}
}

void gameTableImpl::changePlayingMode()
{

	int mode = -1;

	if(radioButton_manualAction->isChecked()) {
		mode=0;
	}
	if(radioButton_autoCheckFold->isChecked()) {
		mode=2;
	}
	if(radioButton_autoCheckCallAny->isChecked()) {
		mode=1;
	}

	playingMode = mode;
}

bool gameTableImpl::eventFilter(QObject *obj, QEvent *event)
{
	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

	if (/*obj == lineEdit_ChatInput && lineEdit_ChatInput->text() != "" && */event->type() == QEvent::KeyPress && keyEvent->key() == Qt::Key_Tab) {
		//myChat->nickAutoCompletition();
		return true;
//    CURRENTLY not possible in Android :(  -->     } else if (event->type() == QEvent::KeyPress && keyEvent->key() == Qt::Key_Back) {
//            event->ignore();
//            closeGameTable();
//            return true;
        } else if (event->type() == QEvent::Close) {
		event->ignore();
		closeGameTable();
		return true;
	} else {
		// pass the event on to the parent class
		return QMainWindow::eventFilter(obj, event);
	}
}

void gameTableImpl::switchLogWindow()
{

	int tab = 0;
#ifdef GUI_800x480
	if (tabs.groupBox_RightToolBox->isHidden()) {
		tabs.tabWidget_Right->setCurrentIndex(tab);
		tabs.groupBox_RightToolBox->show();
	}	else {
		if (tabs.tabWidget_Right->currentIndex() == tab) {
			tabs.groupBox_RightToolBox->hide();
		} else {
			tabs.tabWidget_Right->setCurrentIndex(tab);
		}
	}
#else
	if (groupBox_RightToolBox->isHidden()) {
		tabWidget_Right->setCurrentIndex(tab);
		groupBox_RightToolBox->show();
	}	else {
		if (tabWidget_Right->currentIndex() == tab) {
			groupBox_RightToolBox->hide();
		} else {
			tabWidget_Right->setCurrentIndex(tab);
		}
	}
#endif
}

void gameTableImpl::switchAwayWindow()
{

	int tab = 1;
#ifdef GUI_800x480
	if (tabs.groupBox_RightToolBox->isHidden()) {
		tabs.tabWidget_Right->setCurrentIndex(tab);
		tabs.groupBox_RightToolBox->show();
	}	else {
		if (tabs.tabWidget_Right->currentIndex() == tab) {
			tabs.groupBox_RightToolBox->hide();
		} else {
			tabs.tabWidget_Right->setCurrentIndex(tab);
		}
	}
#else
	if (groupBox_RightToolBox->isHidden()) {
		tabWidget_Right->setCurrentIndex(tab);
		groupBox_RightToolBox->show();
	}	else {
		if (tabWidget_Right->currentIndex() == tab) {
			groupBox_RightToolBox->hide();
		} else {
			tabWidget_Right->setCurrentIndex(tab);
		}
	}
#endif
}

void gameTableImpl::switchChanceWindow()
{

	int tab = 2;
#ifdef GUI_800x480
	if (tabs.groupBox_RightToolBox->isHidden()) {
		tabs.tabWidget_Right->setCurrentIndex(tab);
		tabs.groupBox_RightToolBox->show();
	}	else {
		if (tabs.tabWidget_Right->currentIndex() == tab) {
			tabs.groupBox_RightToolBox->hide();
		} else {
			tabs.tabWidget_Right->setCurrentIndex(tab);
		}
	}
#else
	if (groupBox_RightToolBox->isHidden()) {
		tabWidget_Right->setCurrentIndex(tab);
		groupBox_RightToolBox->show();
	}	else {
		if (tabWidget_Right->currentIndex() == tab) {
			groupBox_RightToolBox->hide();
		} else {
			tabWidget_Right->setCurrentIndex(tab);
		}
	}
#endif
}

void gameTableImpl::switchFullscreen()
{

	if (this->isFullScreen()) {
		this->showNormal();
	} else {
		this->showFullScreen();
	}
}

void gameTableImpl::blinkingStartButtonAnimationAction()
{

#ifdef GUI_800x480
	QString style = tabs.pushButton_break->styleSheet();
#else
	QString style = pushButton_break->styleSheet();
#endif

	if(style.contains("QPushButton:enabled { background-color: #"+myGameTableStyle->getBreakLobbyButtonBgColor())) {
#ifdef GUI_800x480
		myGameTableStyle->setBreakButtonStyle(tabs.pushButton_break,1);
#else
		myGameTableStyle->setBreakButtonStyle(pushButton_break,1);
#endif
	} else {
#ifdef GUI_800x480
		myGameTableStyle->setBreakButtonStyle(tabs.pushButton_break,0);
#else
		myGameTableStyle->setBreakButtonStyle(pushButton_break,0);
#endif
	}
}

//void gameTableImpl::sendChatMessage()
//{
//	myChat->sendMessage();
//}
//void gameTableImpl::checkChatInputLength(QString string)
//{
//	myChat->checkInputLength(string);
//}


void gameTableImpl::tabSwitchAction()
{

//#ifdef GUI_800x480
//	switch(tabs.tabWidget_Left->currentIndex()) {
//
//	case 1: {
//		tabs.lineEdit_ChatInput->setFocus();
//	}
//	break;
//	default: {
//		tabs.lineEdit_ChatInput->clearFocus();
//	}
//
//	}
//#else
//	switch(tabWidget_Left->currentIndex()) {
//
//	case 1: {
//		lineEdit_ChatInput->setFocus();
//	}
//	break;
//	default: {
//		lineEdit_ChatInput->clearFocus();
//	}
//
//	}
//#endif
//
}


void gameTableImpl::GameModification()
{

	int i;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++ ) {
		playerAvatarLabelArray[i]->setEnabledContextMenu(FALSE);
	}

#ifdef GUI_800x480
	tabs.pushButton_break->show();
#else
	pushButton_break->show();
#endif
	QFontMetrics tempMetrics = this->fontMetrics();
	int width = tempMetrics.width(tr("Stop"));
#ifdef GUI_800x480
	tabs.pushButton_break->setText(tr("Stop"));
	tabs.pushButton_break->setMinimumSize(width+10,20);
#else
	pushButton_break->setText(tr("Stop"));
	pushButton_break->setMinimumSize(width+10,20);
#endif

	//Set the playing mode to "manual"
#ifdef GUI_800x480
	tabs.radioButton_manualAction->click();
#else
	radioButton_manualAction->click();
#endif

	//restore saved windows geometry
	restoreGameTableGeometry();

	if(myGameTableStyle->getState() != GT_STYLE_OK) myGameTableStyle->showErrorMessage();

	//let the SoundEventHandler know that there is a new game
	mySoundEventHandler->newGameStarts();
}

void gameTableImpl::mouseOverFlipCards(bool front)
{

	if(myStartWindow->getSession()->getCurrentGame()) {
		if(myConfig->readConfigInt("AntiPeekMode") && myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getSeatsList()->front()->getActiveStatus()/* && myStartWindow->getSession()->getCurrentGame()->getSeatsList()->front()->getAction() != PLAYER_ACTION_FOLD*/) {
			holeCardsArray[0][0]->signalFastFlipCards(front);
			holeCardsArray[0][1]->signalFastFlipCards(front);
		}
	}
}

void gameTableImpl::updateMyButtonsState(int mode)
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	if(currentHand->getPreviousPlayerID() == 0) {
		myButtonsCheckable(FALSE);
		clearMyButtons();
	} else {
		if(currentHand->getSeatsList()->front()->getAction() != PLAYER_ACTION_ALLIN) { // dont show pre-actions after flip cards when allin
			myButtonsCheckable(TRUE);
			provideMyActions(mode);
		}
	}
}

void gameTableImpl::uncheckMyButtons()
{

	pushButton_BetRaise->setChecked(FALSE);
	pushButton_CallCheck->setChecked(FALSE);
	pushButton_Fold->setChecked(FALSE);
	pushButton_AllIn->setChecked(FALSE);

}

void gameTableImpl::resetButtonsCheckStateMemory()
{

	pushButtonCallCheckIsChecked = FALSE;
	pushButtonFoldIsChecked = FALSE;
	pushButtonAllInIsChecked = FALSE;
	pushButtonBetRaiseIsChecked = FALSE;
}

void gameTableImpl::clearMyButtons()
{

	refreshActionButtonFKeyIndicator(1);

	pushButton_BetRaise->setText("");
	pushButton_CallCheck->setText("");
	pushButton_Fold->setText("");
	pushButton_AllIn->setText("");
}

void gameTableImpl::myButtonsCheckable(bool state)
{

	boost::shared_ptr<HandInterface> currentHand = myStartWindow->getSession()->getCurrentGame()->getCurrentHand();

	if(state) {
		//checkable

		// exception: full bet rule
		if(!currentHand->getCurrentBettingRound()->getFullBetRule()) {
			pushButton_BetRaise->setCheckable(TRUE);
			pushButton_BetRaiseHalfPot->setCheckable(TRUE);
			pushButton_BetRaiseTwoThirdPot->setCheckable(TRUE);
			pushButton_BetRaisePot->setCheckable(TRUE);
		}
		pushButton_CallCheck->setCheckable(TRUE);
		pushButton_Fold->setCheckable(TRUE);
		pushButton_AllIn->setCheckable(TRUE);

		//design
		myGameTableStyle->setButtonsStyle(pushButton_BetRaise,pushButton_BetRaiseHalfPot, pushButton_BetRaiseTwoThirdPot, pushButton_BetRaisePot, 
			pushButton_CallCheck, pushButton_Fold, pushButton_AllIn, 2);

		myButtonsAreCheckable = TRUE;
	} else {
		//not checkable

		pushButton_BetRaise->setCheckable(FALSE);
		pushButton_BetRaiseHalfPot->setCheckable(FALSE);
		pushButton_BetRaiseTwoThirdPot->setCheckable(FALSE);
		pushButton_BetRaisePot->setCheckable(FALSE);
		pushButton_CallCheck->setCheckable(FALSE);
		pushButton_Fold->setCheckable(FALSE);
		pushButton_AllIn->setCheckable(FALSE);

		QString hover;
		if(pushButton_AllIn->text()==AllInString) {
			myGameTableStyle->setButtonsStyle(pushButton_BetRaise,pushButton_BetRaiseHalfPot, pushButton_BetRaiseTwoThirdPot, pushButton_BetRaisePot, 
					pushButton_CallCheck, pushButton_Fold, pushButton_AllIn, 0);
		} else {
			myGameTableStyle->setButtonsStyle(pushButton_BetRaise,pushButton_BetRaiseHalfPot, pushButton_BetRaiseTwoThirdPot, pushButton_BetRaisePot, 
					pushButton_CallCheck, pushButton_Fold, pushButton_AllIn, 1);
		}

		myButtonsAreCheckable = FALSE;
	}
}

void gameTableImpl::showMaximized ()
{
	this->showFullScreen ();
}

void gameTableImpl::closeGameTable()
{

	bool close = true;

	if(close) {
		//now really close the table
//		myStartWindow->getSession()->terminateNetworkClient();
		stopTimer();
		saveGameTableGeometry();
		myStartWindow->show();
		this->hide();
	}

}

void gameTableImpl::changeSpinBoxBetValue(int value)
{
        if(betSliderChangedByInput) {
                //prevent interval cutting of spinBox_betValue input from code below
                betSliderChangedByInput = FALSE;
        }
        else {

            if(horizontalSlider_bet->value() == horizontalSlider_bet->maximum()) {

                spinBox_betValue->setValue(horizontalSlider_bet->value());
            }
            else {

                int temp;
                if(horizontalSlider_bet->maximum() <= 1000 ) {
                        temp = (int)((value/10)*10);
                } else if(horizontalSlider_bet->maximum() > 1000 && horizontalSlider_bet->maximum() <= 10000) {
                        temp = (int)((value/50)*50);
                } else if(horizontalSlider_bet->maximum() > 10000 && horizontalSlider_bet->maximum() <= 100000) {
                        temp = (int)((value/500)*500);
                } else {
                        temp = (int)((value/5000)*5000);
                }

                if(temp < horizontalSlider_bet->minimum())
                        spinBox_betValue->setValue(horizontalSlider_bet->minimum());
                else
                        spinBox_betValue->setValue(temp);
            }
        }
}

void gameTableImpl::spinBoxBetValueChanged(int value)
{

    if(horizontalSlider_bet->isEnabled()) {

        QString betRaise = pushButton_BetRaise->text().section("\n",0 ,0);

        if(value >= horizontalSlider_bet->minimum()) {

            if(value > horizontalSlider_bet->maximum()) { // print the maximum
                pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(horizontalSlider_bet->maximum()));
                betSliderChangedByInput = TRUE;
                horizontalSlider_bet->setValue(horizontalSlider_bet->maximum());
            } else { // really print the value
                pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(value));
                betSliderChangedByInput = TRUE;
                horizontalSlider_bet->setValue(value);
            }
        } else { // print the minimum
            pushButton_BetRaise->setText(betRaise + "\n$" + QString("%L1").arg(horizontalSlider_bet->minimum()));
            betSliderChangedByInput = TRUE;
            horizontalSlider_bet->setValue(horizontalSlider_bet->minimum());
        }
    }
}


//void gameTableImpl::refreshCardsChance(GameState BettingRound)
//{
//	if(myConfig->readConfigInt("ShowCardsChanceMonitor")) {
//
//		boost::shared_ptr<Player> humanPlayer = myStartWindow->getSession()->getCurrentGame()->getSeatsList()->front();
//		if(humanPlayer->getActiveStatus()) {
//			int boardCards[5];
//			int holeCards[2];
//
//			humanPlayer->getCards(holeCards);
//			myStartWindow->getSession()->getCurrentGame()->getCurrentHand()->getBoard()->getCards(boardCards);
//
//			if(humanPlayer->getAction() == PLAYER_ACTION_FOLD) {
//#ifdef GUI_800x480
//				tabs.label_chance->refreshChance(CardsValue::calcCardsChance(BettingRound, holeCards, boardCards), true);
//#else
//				label_chance->refreshChance(CardsValue::calcCardsChance(BettingRound, holeCards, boardCards), true);
//#endif
//			} else {
//#ifdef GUI_800x480
//				tabs.label_chance->refreshChance(CardsValue::calcCardsChance(BettingRound, holeCards, boardCards), false);
//#else
//				label_chance->refreshChance(CardsValue::calcCardsChance(BettingRound, holeCards, boardCards), false);
//#endif
//			}
//		} else {
//#ifdef GUI_800x480
//			tabs.label_chance->resetChance();
//#else
//			label_chance->resetChance();
//#endif
//		}
//	}
//}

void gameTableImpl::refreshActionButtonFKeyIndicator(bool clear)
{
	if(clear) {
		pushButton_AllIn->setFKeyText("");
		pushButton_BetRaise->setFKeyText("");
		pushButton_BetRaiseHalfPot->setFKeyText("");
		pushButton_BetRaiseTwoThirdPot->setFKeyText("");
		pushButton_BetRaisePot->setFKeyText("");
		pushButton_CallCheck->setFKeyText("");
		pushButton_Fold->setFKeyText("");
	} else {
		if(myConfig->readConfigInt("AlternateFKeysUserActionMode") == 0 ) {
			if(!pushButton_AllIn->text().isEmpty()) pushButton_AllIn->setFKeyText("");
			if(!pushButton_BetRaise->text().isEmpty()) pushButton_BetRaise->setFKeyText("F3");
			if(!pushButton_BetRaiseHalfPot->text().isEmpty()) pushButton_BetRaiseHalfPot->setFKeyText("");
			if(!pushButton_BetRaiseTwoThirdPot->text().isEmpty()) pushButton_BetRaiseTwoThirdPot->setFKeyText("");
			if(!pushButton_BetRaisePot->text().isEmpty()) pushButton_BetRaisePot->setFKeyText("");
			if(!pushButton_CallCheck->text().isEmpty()) pushButton_CallCheck->setFKeyText("F2");
			if(!pushButton_Fold->text().isEmpty()) pushButton_Fold->setFKeyText("F1");
		} else {
			if(!pushButton_AllIn->text().isEmpty()) pushButton_AllIn->setFKeyText("F1");
			if(!pushButton_BetRaise->text().isEmpty()) pushButton_BetRaise->setFKeyText("F2");
			if(!pushButton_BetRaiseHalfPot->text().isEmpty()) pushButton_BetRaiseHalfPot->setFKeyText("");
			if(!pushButton_BetRaiseTwoThirdPot->text().isEmpty()) pushButton_BetRaiseTwoThirdPot->setFKeyText("");
			if(!pushButton_BetRaisePot->text().isEmpty()) pushButton_BetRaisePot->setFKeyText("");
			if(!pushButton_CallCheck->text().isEmpty()) pushButton_CallCheck->setFKeyText("F3");
			if(!pushButton_Fold->text().isEmpty()) pushButton_Fold->setFKeyText("");
		}
	}
}

void gameTableImpl::refreshGameTableStyle()
{
	myGameTableStyle->setWindowsGeometry(this);
#ifdef GUI_800x480
#ifdef ANDROID
        myGameTableStyle->setChatLogStyle(tabs.textBrowser_Log);
#endif
	myGameTableStyle->setChatLogStyle(tabs.textBrowser_Chat);
//	myGameTableStyle->setChatLogStyle(tabs.textEdit_tipInput);
//	myGameTableStyle->setChatInputStyle(tabs.lineEdit_ChatInput);
#else
	myGameTableStyle->setChatLogStyle(textBrowser_Log);
#endif

	int i;
	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {

		myGameTableStyle->setCashLabelStyle(cashLabelArray[i]);
		myGameTableStyle->setSetLabelStyle(setLabelArray[i]);
		myGameTableStyle->setPlayerNameLabelStyle(playerNameLabelArray[i]);
	}

    myGameTableStyle->setSmallFontBoardStyle(label_Sets);
    myGameTableStyle->setSmallFontBoardStyle(label_Total);
	myGameTableStyle->setSmallFontBoardStyle(textLabel_Sets);
	myGameTableStyle->setSmallFontBoardStyle(textLabel_Pot);
	myGameTableStyle->setSmallFontBoardStyle(label_handNumber);
	myGameTableStyle->setSmallFontBoardStyle(label_gameNumber);
	myGameTableStyle->setSmallFontBoardStyle(label_handNumberValue);
	myGameTableStyle->setSmallFontBoardStyle(label_gameNumberValue);
	myGameTableStyle->setBigFontBoardStyle(textLabel_handLabel);
	myGameTableStyle->setBigFontBoardStyle(label_Pot);
	myGameTableStyle->setCardHolderStyle(label_CardHolder0,0);
	myGameTableStyle->setCardHolderStyle(label_CardHolder1,0);
	myGameTableStyle->setCardHolderStyle(label_CardHolder2,0);
	myGameTableStyle->setCardHolderStyle(label_CardHolder3,1);
	myGameTableStyle->setCardHolderStyle(label_CardHolder4,2);
	myGameTableStyle->setTableBackground(this);
	myGameTableStyle->setMenuBarStyle(menubar);
	myGameTableStyle->setBreakButtonStyle(pushButton_break,0);
	myGameTableStyle->setSpeedStringStyle(label_speedString);
	myGameTableStyle->setSpeedStringStyle(label_speedValue);

	for (i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {

		myGameTableStyle->setPlayerSeatInactiveStyle(groupBoxArray[i]);
	}
	//Human player button
	myGameTableStyle->setButtonsStyle(pushButton_BetRaise,pushButton_BetRaiseHalfPot, pushButton_BetRaiseTwoThirdPot, pushButton_BetRaisePot, 
			pushButton_CallCheck, pushButton_Fold, pushButton_AllIn, 0);

	myGameTableStyle->setBetValueInputStyle(spinBox_betValue);
	myGameTableStyle->setSliderStyle(horizontalSlider_bet);
	myGameTableStyle->setSliderStyle(horizontalSlider_speed);

	// 	away radiobuttons
	myGameTableStyle->setAwayRadioButtonsStyle(radioButton_manualAction);
	myGameTableStyle->setAwayRadioButtonsStyle(radioButton_autoCheckFold);
	myGameTableStyle->setAwayRadioButtonsStyle(radioButton_autoCheckCallAny);

	myGameTableStyle->setToolBoxBackground(groupBox_RightToolBox);

	myGameTableStyle->setTabWidgetStyle(tabWidget_Right, tabWidget_Right->getTabBar());

	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionCallI18NString() == "NULL") {
		CallString = "Call";
	} else {
		CallString = myGameTableStyle->getActionCallI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionCheckI18NString() == "NULL") {
		CheckString = "Check";
	} else {
		CheckString = myGameTableStyle->getActionCheckI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionBetI18NString() == "NULL") {
		BetString = "Bet";
	} else {
		BetString = myGameTableStyle->getActionBetI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionRaiseI18NString() == "NULL") {
		RaiseString = "Raise";
	} else {
		RaiseString = myGameTableStyle->getActionRaiseI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionFoldI18NString() == "NULL") {
		FoldString = "Fold";
	} else {
		FoldString = myGameTableStyle->getActionFoldI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getActionAllInI18NString() == "NULL") {
		AllInString = "All-In";
	} else {
		AllInString = myGameTableStyle->getActionAllInI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getPotI18NString() == "NULL") {
		PotString = "Pot";
	} else {
		PotString = myGameTableStyle->getPotI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getTotalI18NString() == "NULL") {
		TotalString = "Total";
	} else {
		TotalString = myGameTableStyle->getTotalI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getBetsI18NString() == "NULL") {
		BetsString = "Bets";
	} else {
		BetsString = myGameTableStyle->getBetsI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getGameI18NString() == "NULL") {
		GameString = "Game";
	} else {
		GameString = myGameTableStyle->getGameI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getHandI18NString() == "NULL") {
		HandString = "Hand";
	} else {
		HandString = myGameTableStyle->getHandI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getPreflopI18NString() == "NULL") {
		PreflopString = "Preflop";
	} else {
		PreflopString = myGameTableStyle->getPreflopI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getFlopI18NString() == "NULL") {
		FlopString = "Flop";
	} else {
		FlopString = myGameTableStyle->getFlopI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getTurnI18NString() == "NULL") {
		TurnString = "Turn";
	} else {
		TurnString = myGameTableStyle->getTurnI18NString();
	}
	if(myConfig->readConfigInt("DontTranslateInternationalPokerStringsFromStyle") || myGameTableStyle->getRiverI18NString() == "NULL") {
		RiverString = "River";
	} else {
		RiverString = myGameTableStyle->getRiverI18NString();
	}

#ifndef GUI_800x480
	label_Pot->setText(PotString);
#endif
	label_Total->setText(TotalString+":");
	label_Sets->setText(BetsString+":");
	label_handNumber->setText(HandString+":");
	label_gameNumber->setText(GameString+":");

}

void gameTableImpl::saveGameTableGeometry()
{
	if(this->isFullScreen()) {
		myConfig->writeConfigInt("GameTableFullScreenSave", 1);
	} else {
		myConfig->writeConfigInt("GameTableFullScreenSave", 0);
		myConfig->writeConfigInt("GameTableHeightSave", this->height());
		myConfig->writeConfigInt("GameTableWidthSave", this->width());
	}
	myConfig->writeBuffer();
}

void gameTableImpl::restoreGameTableGeometry()
{
#ifdef ANDROID
    this->showFullScreen();
#else
	if(myConfig->readConfigInt("GameTableFullScreenSave")) {
    #ifndef GUI_800x480
		if(actionFullScreen->isEnabled()) this->showFullScreen();
    #endif
	} else {
		//resize only if style size allow this and if NOT fixed windows size
		if(!myGameTableStyle->getIfFixedWindowSize().toInt() && myConfig->readConfigInt("GameTableHeightSave") <= myGameTableStyle->getMaximumWindowHeight().toInt() && myConfig->readConfigInt("GameTableHeightSave") >= myGameTableStyle->getMinimumWindowHeight().toInt() && myConfig->readConfigInt("GameTableWidthSave") <= myGameTableStyle->getMaximumWindowWidth().toInt() && myConfig->readConfigInt("GameTableWidthSave") >= myGameTableStyle->getMinimumWindowWidth().toInt()) {

			this->resize(myConfig->readConfigInt("GameTableWidthSave"), myConfig->readConfigInt("GameTableHeightSave"));
		}
	}
#endif
}

void gameTableImpl::registeredUserMode()
{
#ifdef GUI_800x480
	tabs.lineEdit_ChatInput->clear();
	tabs.lineEdit_ChatInput->setEnabled(true);
#else
	//lineEdit_ChatInput->clear();
	//lineEdit_ChatInput->setEnabled(true);
#endif
	guestMode = false;
}


void gameTableImpl::guestUserMode()
{
#ifdef GUI_800x480
	//tabs.lineEdit_ChatInput->setText(tr("Chat is only available to registered players."));
	//tabs.lineEdit_ChatInput->setDisabled(true);
#else
	//lineEdit_ChatInput->setText(tr("Chat is only available to registered players."));
	//lineEdit_ChatInput->setDisabled(true);
#endif
	guestMode = true;
}

//void gameTableImpl::showShowMyCardsButton()
//{
//	pushButton_showMyCards->show();
//	pushButton_showMyCards->raise();
//}

//void gameTableImpl::sendShowMyCardsSignal()
//{
//	if(pushButton_showMyCards->isVisible()) {
//
//		myStartWindow->getSession()->showMyCards();
//
//		pushButton_showMyCards->hide();
//	}
//}

void gameTableImpl::closeMessageBoxes()
{

	myUniversalMessageDialog->close();
}

void gameTableImpl::hide()
{
	//clear log
#ifdef GUI_800x480
	tabs.textBrowser_Log->clear();
    tabsDiag->hide();
#else
	textBrowser_Log->clear();
#endif
	QWidget::hide();
}

SeatState gameTableImpl::getCurrentSeatState(boost::shared_ptr<Player> player)
{

	if(player->getActiveStatus()) {
		if(player->isSessionActive()) {
			return SEAT_ACTIVE;
		} else {
			return SEAT_AUTOFOLD;
		}
	} else {
		return SEAT_CLEAR;
	}
	return SEAT_UNDEFINED;
}

void gameTableImpl::soundEvent_blindsWereSet(int sbSet)
{
	mySoundEventHandler->blindsWereSet(sbSet);
}

void gameTableImpl::enableCallCheckPushButton()
{
	pushButton_CallCheck->setEatMyEvents(false);
}

void gameTableImpl::setGameSpeed(const int theValue) {
	guiGameSpeed = theValue;   
	setSpeeds();
}
SDLPlayer* gameTableImpl::getSDLPlayer() const {
	return mySDLPlayer;
}
SoundEvents* gameTableImpl::getSoundEventHandler() const {
	return mySoundEventHandler;
}
ConfigFile* gameTableImpl::getConfig() const {
	return myConfig;
}
GameTableStyleReader* gameTableImpl::getGameTableStyle() const {
	return myGameTableStyle;
}
bool gameTableImpl::getGuestMode() const {
	return guestMode;
}

void gameTableImpl::setStartWindow(startWindowImpl* s) {
	myStartWindow = s;
}
void gameTableImpl::setGuiLog(guiLog* l) {
	myGuiLog = l;
}

