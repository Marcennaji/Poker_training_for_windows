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

#include <engine/player.h>
#include <engine/handinterface.h>
#include "tools.h"
#include "cardsvalue.h"
#include <configfile.h>
#include <loghelper.h>
#include <sqlite3.h>
#include <dirent.h>
#include <boost/lexical_cast.hpp>
#include <engine/ranges.h>

#include <engine/psim/t_nbitsandstr.c>
#include <engine/psim/simulate.hpp>

#include <fstream>
#include <sstream>

using namespace std;

void CurrentHandActions::reset(){

	m_preflopActions.clear();
	m_flopActions.clear();
	m_turnActions.clear();
	m_riverActions.clear();
}

std::vector<PlayerAction> & CurrentHandActions::getPreflopActions(){
	return m_preflopActions;
}

std::vector<PlayerAction> & CurrentHandActions::getFlopActions() {
	return m_flopActions;
}

std::vector<PlayerAction> & CurrentHandActions::getTurnActions() {
	return m_turnActions;
}

std::vector<PlayerAction> & CurrentHandActions::getRiverActions() {
	return m_riverActions;
}

const char * TightAgressivePlayerName[] = { "Tintin","Tonio","Tetuan","Tim","Thierry","Tania",
										"Taslima","Théo","Tom","Tatiana" }; 

const char * LargeAgressivePlayerName[] = { "Louis","Louane","Ludovic","Lucas","Laure","Leila",
										"Lino","Laurent","Lucie","Ludivine" }; 

const char * ManiacPlayerName[] = { "Maurice","Milou","Michou","Maelle","Mokhtar","Mireille",
										"Marianne","Momo","Maurane","Maya" }; 

const char * HumanPlayerName[] = {" "};

// values are odd %, according to the outs number. Array index is the number of outs
int outsOddsOneCard[] = { 0, 2, 4,  6,  8,  11,	 /* 0 to 5 outs */
							13, 15, 17, 19, 21,  /* 6 to 10 outs */
							24, 26, 28, 30, 32,	 /* 11 to 15 outs */
							34, 36, 39, 41, 43   /* 16 to 20 outs */
						  };

int outsOddsTwoCard[] = { 0, 4, 8,  13, 17, 20,	 /* 0 to 5 outs */
							24, 28, 32, 35, 38,  /* 6 to 10 outs */
							42, 45, 48, 51, 54,	 /* 11 to 15 outs */
							57, 60, 62, 65, 68   /* 16 to 20 outs */
						  };

Player::Player(ConfigFile *c, int id, unsigned uniqueId, PlayerType type, std::string name, 
						std::string avatar, int sC, bool aS, bool sotS, int mB)
	: 
	myConfig(c), currentHand(0), myID(id), myUniqueID(uniqueId), myType(type), myName(name), myAvatar(avatar),
	  myCardsValueInt(0), logHoleCardsDone(false), myCash(sC), mySet(0), myLastRelativeSet(0), myAction(PLAYER_ACTION_NONE),
	  myButton(mB), myActiveStatus(aS), myStayOnTableStatus(sotS), myTurn(0), myCardsFlip(0), myRoundStartCash(0), lastMoneyWon(0),
	  m_isSessionActive(false)
{
	loadStatistics();

	int i;
	for(i=0; i<2; i++) {
		myCards[i] = -1;
	}

	for(i=0; i<5; i++) {
		myBestHandPosition[i] = -1;
	}
}


Player::~Player()
{
}


void Player::setHand(HandInterface* br)
{
	currentHand = br;
}


void Player::action()
{
	//test
	//currentHand->getGuiInterface()->showCards(myUniqueID);
	
	myRaiseAmount = 0;
	myBetAmount = 0;

	switch(currentHand->getCurrentRound()) {

	case GAME_STATE_PREFLOP: 
		doPreflopAction();
		break;

	case GAME_STATE_FLOP: 
		doFlopAction();		
		break;

	case GAME_STATE_TURN: 
		doTurnAction();
		break;

	case GAME_STATE_RIVER: 
		doRiverAction();
		break;

	default:
		break;
	}

	evaluateBetAmount(); // original bet amount may be modified
	currentHand->getBoard()->collectSets();
	currentHand->getGuiInterface()->refreshPot();

	myTurn = 0;

#ifdef LOG_POKER_EXEC
	cout << endl;
	if (myAction == PLAYER_ACTION_FOLD)
		cout << "FOLD";
	else
	if (myAction == PLAYER_ACTION_BET)
		cout << "BET " << myBetAmount;
	else
	if (myAction == PLAYER_ACTION_RAISE)
		cout << "RAISE "  << myRaiseAmount;
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

	cout << endl << "---------------------------------------------------------------------------------" << endl << endl;
#endif

	//set that i was the last active player. need this for unhighlighting groupbox
	currentHand->setPreviousPlayerID(myID);

	currentHand->getGuiInterface()->logPlayerActionMsg(myName, myAction, mySet);
	currentHand->getGuiInterface()->nextPlayerAnimation();
}

void Player::doPreflopAction(){

	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

#ifdef LOG_POKER_EXEC
	cout << endl << "\t" << getPositionLabel(myPosition) << "\t" << myName << "\t" << getCardsValueString()   
		<< "\t" <<  "stack = " << myCash << ", pot = " << currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets()
		<< "\tPFR : " << getStatistics(nbPlayers).getPreflopStatistics().getPreflopRaise()<< endl;
#endif

	myShouldBet  = false;
	myShouldCall =  preflopShouldCall();
	myShouldRaise = preflopShouldRaise(); 

	if (myShouldRaise)
		myShouldCall = false;

	// if last to speak, and nobody has raised : I can check
	if (currentHand->getPreflopRaisesNumber() == 0 && ! myShouldRaise && myPosition == BB) 
		myAction = PLAYER_ACTION_CHECK;
	else{
		if (myShouldBet)
			myAction = PLAYER_ACTION_BET;
		else
		if (myShouldCall)
			myAction = PLAYER_ACTION_CALL;
		else
		if (myShouldRaise)
			myAction = PLAYER_ACTION_RAISE;
		else
			myAction = PLAYER_ACTION_FOLD;
	}
	
	if (myAction != PLAYER_ACTION_RAISE)
		myRaiseAmount = 0;
	else
		currentHand->setPreflopLastRaiserID(myID);

	myCurrentHandActions.m_preflopActions.push_back(myAction);
		
	updatePreflopStatistics();

	//cout << endl << myName << " action : " << myAction << endl;

}
void Player::doFlopAction(){

	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

#ifdef LOG_POKER_EXEC
	cout << endl << "\t" << getPositionLabel(myPosition) << "\t" << myName << "\t" << getCardsValueString()   
		<< "\t" <<  "stack = " << myCash << ", pot = " << currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets()
		<< "\tPFR : " << getStatistics(nbPlayers).getPreflopStatistics().getPreflopRaise()<< endl;
#endif

	myFlopState = getPostFlopState();
	DisplayHandState(&myFlopState);

	myFlopHandSimulation = getHandSimulation();

	myShouldBet  = flopShouldBet();
	myShouldCall = myShouldBet ? false : flopShouldCall();
	myShouldRaise = myShouldBet ? false : flopShouldRaise(); 

	if (myShouldRaise)
		myShouldCall = false;

	if (currentHand->getFlopBetsOrRaisesNumber() == 0 && ! myShouldRaise && ! myShouldBet) 
		myAction = PLAYER_ACTION_CHECK;
	else{
		if (myShouldBet)
			myAction = PLAYER_ACTION_BET;
		else
		if (myShouldCall)
			myAction = PLAYER_ACTION_CALL;
		else
		if (myShouldRaise)
			myAction = PLAYER_ACTION_RAISE;
		else
			myAction = PLAYER_ACTION_FOLD;
	}
	
	if (myAction != PLAYER_ACTION_RAISE)
		myRaiseAmount = 0;

	if (myAction != PLAYER_ACTION_BET)
		myBetAmount = 0;

	myCurrentHandActions.m_flopActions.push_back(myAction);

	updateFlopStatistics();

	//cout << endl << myName << " action : " << myAction << endl;

}
void Player::doTurnAction(){

	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

#ifdef LOG_POKER_EXEC
	cout << endl << "\t" << getPositionLabel(myPosition) << "\t" << myName << "\t" << getCardsValueString()   
		<< "\t" <<  "stack = " << myCash << ", pot = " << currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets()
		<< "\tPFR : " << getStatistics(nbPlayers).getPreflopStatistics().getPreflopRaise()<< endl;
#endif

	myTurnState		= getPostFlopState();
	DisplayHandState(&myTurnState);

	myTurnHandSimulation = getHandSimulation();

	myShouldBet  = turnShouldBet();
	myShouldCall = myShouldBet ? false : turnShouldCall();
	myShouldRaise = myShouldBet ? false : turnShouldRaise(); 

	if (myShouldRaise)
		myShouldCall = false;

	if (currentHand->getTurnBetsOrRaisesNumber() == 0 && ! myShouldRaise && ! myShouldBet) 
		myAction = PLAYER_ACTION_CHECK;
	else{
		if (myShouldBet)
			myAction = PLAYER_ACTION_BET;
		else
		if (myShouldCall)
			myAction = PLAYER_ACTION_CALL;
		else
		if (myShouldRaise)
			myAction = PLAYER_ACTION_RAISE;
		else
			myAction = PLAYER_ACTION_FOLD;
	}
	
	if (myAction != PLAYER_ACTION_RAISE)
		myRaiseAmount = 0;

	if (myAction != PLAYER_ACTION_BET)
		myBetAmount = 0;

	myCurrentHandActions.m_turnActions.push_back(myAction);

	updateTurnStatistics();

}
void Player::doRiverAction(){

	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

#ifdef LOG_POKER_EXEC
	cout << endl << "\t" << getPositionLabel(myPosition) << "\t" << myName << "\t" << getCardsValueString()   
		<< "\t" <<  "stack = " << myCash << ", pot = " << currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets() 
		<< "\tPFR : " << getStatistics(nbPlayers).getPreflopStatistics().getPreflopRaise()<< endl;
#endif

	myRiverState	= getPostFlopState();
	DisplayHandState(&myRiverState);
	myRiverHandSimulation = getHandSimulation();

	myShouldBet  = riverShouldBet();
	myShouldCall = myShouldBet ? false : riverShouldCall();
	myShouldRaise = myShouldBet ? false : riverShouldRaise(); 

	if (myShouldRaise)
		myShouldCall = false;

	if (currentHand->getRiverBetsOrRaisesNumber() == 0 && ! myShouldRaise && ! myShouldBet) 
		myAction = PLAYER_ACTION_CHECK;
	else{
		if (myShouldBet)
			myAction = PLAYER_ACTION_BET;
		else
		if (myShouldCall)
			myAction = PLAYER_ACTION_CALL;
		else
		if (myShouldRaise)
			myAction = PLAYER_ACTION_RAISE;
		else
			myAction = PLAYER_ACTION_FOLD;
	}
	
	if (myAction != PLAYER_ACTION_RAISE)
		myRaiseAmount = 0;

	if (myAction != PLAYER_ACTION_BET)
		myBetAmount = 0;
	
	myCurrentHandActions.m_riverActions.push_back(myAction);
	
	updateRiverStatistics();
	
	//cout << endl << myName << " action : " << myAction << endl;

}
void Player::evaluateBetAmount()
{

	int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();

	if (myAction == PLAYER_ACTION_CALL) {

		// all in
		if(highestSet >= myCash + mySet) {
			mySet += myCash;
			myCash = 0;
			myAction = PLAYER_ACTION_ALLIN;
		}
		else {
			myCash = myCash - highestSet + mySet;
			mySet = highestSet;
		}
	}

	if (myAction == PLAYER_ACTION_BET) {

		// short stack, just go allin
		if (myBetAmount * 2.5 > myCash)
			myBetAmount = myCash;

		if(myBetAmount >= myCash) {
			if(myCash < 2*currentHand->getSmallBlind()) {
				// -> full bet rule
				currentHand->getCurrentBettingRound()->setFullBetRule(true);
			}
			currentHand->getCurrentBettingRound()->setMinimumRaise(myCash);
			mySet = myCash;
			myCash = 0;
			myAction = PLAYER_ACTION_ALLIN;
			highestSet = mySet;
		}
		else {
			currentHand->getCurrentBettingRound()->setMinimumRaise(myBetAmount);
			myCash = myCash - myBetAmount;
			mySet = myBetAmount;
			highestSet = mySet;

		}
		currentHand->setLastActionPlayerID(myUniqueID);
			
	}
		
	if (myAction == PLAYER_ACTION_RAISE){

		// short stack, just go allin
		if (myRaiseAmount * 2.5 > myCash)
			myRaiseAmount = myCash;

		if(currentHand->getCurrentBettingRound()->getFullBetRule()) { // full bet rule -> only call possible
			// all in
			if(highestSet >= myCash + mySet) {
				mySet += myCash;
				myCash = 0;
				myAction = PLAYER_ACTION_ALLIN;
			}
			else {
				myCash = myCash - highestSet + mySet;
				mySet = highestSet;
				myAction = PLAYER_ACTION_CALL;
			}
		} else {
			if(myRaiseAmount < currentHand->getCurrentBettingRound()->getMinimumRaise()) {
				myRaiseAmount = currentHand->getCurrentBettingRound()->getMinimumRaise();
			}
			// all in
			if(highestSet + myRaiseAmount >= myCash + mySet) {
				if(highestSet + currentHand->getCurrentBettingRound()->getMinimumRaise() > myCash + mySet) {
					// perhaps full bet rule
					if(highestSet >= myCash + mySet) {
						// only call all-in
						mySet += myCash;
						myCash = 0;
						myAction = PLAYER_ACTION_ALLIN;
					} else {
						// raise, but not enough --> full bet rule
						currentHand->getCurrentBettingRound()->setFullBetRule(true);
						// lastPlayerAction für Karten umblättern reihenfolge setzrn
						currentHand->setLastActionPlayerID(myUniqueID);

						mySet += myCash;
						currentHand->getCurrentBettingRound()->setMinimumRaise(mySet-highestSet);
						myCash = 0;
						myAction = PLAYER_ACTION_ALLIN;
						highestSet = mySet;
					}
				} else {
					currentHand->setLastActionPlayerID(myUniqueID);

					mySet += myCash;
					currentHand->getCurrentBettingRound()->setMinimumRaise(mySet-highestSet);
					myCash = 0;
					myAction = PLAYER_ACTION_ALLIN;
					highestSet = mySet;
				}
			}
			else {
				currentHand->getCurrentBettingRound()->setMinimumRaise(myRaiseAmount);
				myCash = myCash + mySet - highestSet - myRaiseAmount;
				mySet = highestSet + myRaiseAmount;
				highestSet = mySet;
				currentHand->setLastActionPlayerID(myUniqueID);
			}
		}			
	}

	currentHand->getCurrentBettingRound()->setHighestSet(highestSet);

}




void Player::setIsSessionActive(bool active)
{
	m_isSessionActive = active;
}

bool Player::isSessionActive() const
{
	return m_isSessionActive;
}

PlayerPosition Player::getPosition(){
	return myPosition;
}

void Player::setPosition(){

	myPosition = UNKNOWN;

	const int dealerPosition = currentHand->getDealerPosition();
	const int nbPlayers =	currentHand->getActivePlayerList()->size();

	// first dimension is my relative position, after the dealer. 
	// Second dimension is the corrresponding position, depending on the number of players (from 0 to 10)
	const PlayerPosition onDealerPositionPlus[MAX_NUMBER_OF_PLAYERS][MAX_NUMBER_OF_PLAYERS+1] = 
	{ 
//0 player	1 player	2 players	3 players	4 players		5 players		6 players		7 players		8 players		9 players		10 players		
{UNKNOWN,	UNKNOWN,	BUTTON,		BUTTON,		BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON},	// my position = dealer
{UNKNOWN,	UNKNOWN,	BB,			SB,			SB,				SB,				SB,				SB,				SB,				SB,				SB},		// my position = dealer + 1
{UNKNOWN,	UNKNOWN,	UNKNOWN,	BB,			BB,				BB,				BB,				BB,				BB,				BB,				BB},		// my position = dealer + 2 
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	CUTOFF,			UTG,			UTG,			UTG,			UTG,			UTG,			UTG},		// my position = dealer + 3
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		CUTOFF,			MIDDLE,			MIDDLE,			UTG_PLUS_ONE,	UTG_PLUS_ONE,	UTG_PLUS_ONE}, // my position = dealer + 4
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		CUTOFF,			LATE,			MIDDLE,			UTG_PLUS_TWO,	UTG_PLUS_TWO}, // my position = dealer + 5 
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		CUTOFF,			LATE,			MIDDLE,			MIDDLE},	// my position = dealer + 6
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		CUTOFF,			LATE,			MIDDLE_PLUS_ONE}, // my position = dealer + 7
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		CUTOFF,			LATE},		// my position = dealer + 8
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		CUTOFF}		// my position = dealer + 9
	};

	// first dimension is my relative position, BEHIND the dealer. 
	// Second are the corrresponding positions, depending on the number of players 
	const PlayerPosition onDealerPositionMinus[10][11] = 
	{	
//0 player	1 player	2 players	3 players	4 players		5 players		6 players		7 players		8 players		9 players		10 players		
{UNKNOWN,	UNKNOWN,	BUTTON,		BUTTON,		BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON,			BUTTON},	// my position = dealer
{UNKNOWN,	UNKNOWN,	BB,			BB,			CUTOFF,			CUTOFF,			CUTOFF,			CUTOFF,			CUTOFF,			CUTOFF,			CUTOFF},		// my position = dealer - 1
{UNKNOWN,	UNKNOWN,	UNKNOWN,	SB,			BB,				UTG,			MIDDLE,			LATE,			LATE,			LATE,			LATE},		// my position = dealer - 2 
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	SB	,			BB,				UTG,			MIDDLE,			MIDDLE,			MIDDLE_PLUS_ONE,MIDDLE_PLUS_ONE},	// my position = dealer - 3
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		SB,				BB,				UTG,			UTG_PLUS_ONE,	UTG_PLUS_TWO,	MIDDLE}, // my position = dealer - 4
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		SB,				BB,				UTG,			UTG_PLUS_ONE,	UTG_PLUS_TWO}, // my position = dealer - 5 
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		SB,				BB,				UTG,			UTG_PLUS_ONE},	// my position = dealer - 6
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		SB,				BB,				UTG}, // my position = dealer - 7
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		SB,				BB},	// my position = dealer - 8
{UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,	UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		UNKNOWN,		SB}		// my position = dealer - 9

	};

	if (myID ==  dealerPosition)
		myPosition = BUTTON;
	else{
	
		// get my relative position from the dealer
		PlayerListIterator it_c;
		PlayerList players = currentHand->getActivePlayerList();

		int pos = 0;

		if (myID >  dealerPosition){

			bool dealerFound = false;
			for(it_c=players->begin(); it_c!=players->end(); ++it_c) {
				if((*it_c)->getID() == dealerPosition)
					dealerFound = true;
				else
					if (dealerFound)
						pos++;
				if ((*it_c)->getID() == myID)
					break;
			}
			myPosition = onDealerPositionPlus[pos][nbPlayers];	

		}else{
			// myId < dealerPosition
			bool myPositionFound = false;
			for(it_c=players->begin(); it_c!=players->end(); ++it_c) {

				if((*it_c)->getID() == myID)
					myPositionFound = true;
				else
					if (myPositionFound)
						pos++;
				if((*it_c)->getID() == dealerPosition)
					break;
			}
			myPosition = onDealerPositionMinus[pos][nbPlayers];	
		}
	}

	assert(myPosition != UNKNOWN);

}
std::string Player::getPositionLabel(PlayerPosition p){

	switch (p){

		case UTG : return "UTG"; break;
		case UTG_PLUS_ONE : return "UTG_PLUS_ONE"; break;
		case UTG_PLUS_TWO : return "UTG_PLUS_TWO"; break;
		case MIDDLE : return "MIDDLE"; break;
		case MIDDLE_PLUS_ONE : return "MIDDLE_PLUS_ONE"; break;			
		case LATE : return "LATE"; break;
		case CUTOFF : return "CUTOFF"; break;
		case BUTTON : return "BUTTON"; break;
		case SB : return "SB"; break;
		case BB : return "BB"; break;
		default : return "unknown"; break;
	}
					
}

int Player::getID() const {
	return myID;
}
CurrentHandActions & Player::getCurrentHandActions(){
	return myCurrentHandActions;
}

unsigned Player::getUniqueID() const {
	return myUniqueID;
}
void Player::setUniqueID(unsigned newId) {
	myUniqueID = newId;
}

void Player::setGuid(const std::string &theValue) {
	myGuid = theValue;
}

std::string Player::getGuid() const {
	return myGuid;
}

PlayerType Player::getType() const {
	return myType;
}

void Player::setName(const std::string& theValue) {
	myName = theValue;
}
std::string Player::getName() const {
	return myName;
}

void Player::setAvatar(const std::string& theValue) {
	myAvatar = theValue;
}
std::string Player::getAvatar() const {
	return myAvatar;
}

void Player::setCash(int theValue) {
	myCash = theValue;
}
int Player::getCash() const {
	return myCash;
}

void Player::setSet(int theValue) {
	myLastRelativeSet = theValue;
	mySet += theValue;
	myCash -= theValue;
}
void Player::setSetAbsolute(int theValue) {
	mySet = theValue;
}
void Player::setSetNull() {
	mySet = 0;
	myLastRelativeSet = 0;
}
int Player::getSet() const {
	return mySet;
}
int Player::getLastRelativeSet() const {
	return myLastRelativeSet;
}

void Player::setAction(PlayerAction theValue, bool blind) {
	myAction = theValue;
	// logging for human player
	if(myAction && !blind) currentHand->getGuiInterface()->logPlayerActionMsg(myName, myAction, mySet);
}
PlayerAction Player::getAction() const	{
	return myAction;
}

void Player::setButton(int theValue) {
	myButton = theValue;
}
int Player::getButton() const	{
	return myButton;
}

void Player::setActiveStatus(bool theValue) {
	myActiveStatus = theValue;
}
bool Player::getActiveStatus() const {
	return myActiveStatus;
}

void Player::setStayOnTableStatus(bool theValue) {
	myStayOnTableStatus = theValue;
}
bool Player::getStayOnTableStatus() const {
	return myStayOnTableStatus;
}

void Player::setCards(int* theValue) {

	for(int i=0; i<2; i++) 
		myCards[i] = theValue[i];

	// will contain human-readable string, i.e "Qc" or "Ts"
	myCard1 = CardsValue::CardStringValue[myCards[0]];
	myCard2 = CardsValue::CardStringValue[myCards[1]];

}
void Player::getCards(int* theValue) const {
	int i;
	for(i=0; i<2; i++) theValue[i] = myCards[i];
}

void Player::setTurn(bool theValue) {
	myTurn = theValue;
}
bool Player::getTurn() const {
	return myTurn;
}

void Player::setCardsFlip(bool theValue, int state) {
	myCardsFlip = theValue;
	// log flipping cards
	if(myCardsFlip) {
		switch(state) {
		case 1:
			currentHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1], myCardsValueInt);
			break;
		case 2:
			currentHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1]);
			break;
		case 3:
			currentHand->getGuiInterface()->logFlipHoleCardsMsg(myName, myCards[0], myCards[1], myCardsValueInt, "has");
			break;
		default:
			;
		}
	}
}
bool Player::getCardsFlip() const {
	return myCardsFlip;
}

void Player::setCardsValueInt(int theValue) {
	myCardsValueInt = theValue;
}
int Player::getCardsValueInt() const {
	return myCardsValueInt;
}

void Player::setLogHoleCardsDone(bool theValue) {
	logHoleCardsDone = theValue;
}

bool Player::getLogHoleCardsDone() const {
	return logHoleCardsDone;
}

void Player::setBestHandPosition(int* theValue) {
	for (int i = 0; i < 5; i++)
		myBestHandPosition[i] = theValue[i];
}
void Player::getBestHandPosition(int* theValue) const {
	for (int i = 0; i < 5; i++)
		theValue[i] = myBestHandPosition[i];
}

void Player::setRoundStartCash(int theValue) {
	myRoundStartCash = theValue;
}
int Player::getRoundStartCash() const {
	return myRoundStartCash;
}

void Player::setLastMoneyWon ( int theValue ) {
	lastMoneyWon = theValue;
}
int Player::getLastMoneyWon() const {
	return lastMoneyWon;
}

std::string Player::getCardsValueString(){
	std::string s = myCard1 + " " + myCard2;
	return s;
}


const PlayerStatistics & Player::getStatistics(const int nbPlayers) const {
	return myStatistics[nbPlayers];
}
void Player::resetPlayerStatistics(){

	for (int i=0; i <= MAX_NUMBER_OF_PLAYERS; i++)
		myStatistics[i].reset();		
}

void Player::updatePreflopStatistics(){

	const int nbPlayers = currentHand->getActivePlayerList()->size();
	myStatistics[nbPlayers].m_toTalHands++;
	myStatistics[nbPlayers].m_preflopStatistics.m_hands++;

	switch (myAction){
		case PLAYER_ACTION_ALLIN :  myStatistics[nbPlayers].m_preflopStatistics.m_raises++; break;
		case PLAYER_ACTION_RAISE :  myStatistics[nbPlayers].m_preflopStatistics.m_raises++; break;
		case PLAYER_ACTION_FOLD :	myStatistics[nbPlayers].m_preflopStatistics.m_folds++; break;
		case PLAYER_ACTION_CHECK :  myStatistics[nbPlayers].m_preflopStatistics.m_checks++; break;
		case PLAYER_ACTION_CALL :	myStatistics[nbPlayers].m_preflopStatistics.m_calls++; break;
	}
	if (myAction == PLAYER_ACTION_CALL && currentHand->getRaisersPositions().size() == 0)//
		myStatistics[nbPlayers].m_preflopStatistics.m_limps++;

	if (myAction == PLAYER_ACTION_RAISE && currentHand->getRaisersPositions().size() > 0)
		myStatistics[nbPlayers].m_preflopStatistics.m_threeBets++; 

}
void Player::updateFlopStatistics(){

	const int nbPlayers = currentHand->getActivePlayerList()->size();
	myStatistics[nbPlayers].m_flopStatistics.m_hands++;

	switch (myAction){
		case PLAYER_ACTION_ALLIN :  myStatistics[nbPlayers].m_flopStatistics.m_raises++; break;
		case PLAYER_ACTION_RAISE :  myStatistics[nbPlayers].m_flopStatistics.m_raises++; break;
		case PLAYER_ACTION_FOLD :	myStatistics[nbPlayers].m_flopStatistics.m_folds++; break;
		case PLAYER_ACTION_CHECK :  myStatistics[nbPlayers].m_flopStatistics.m_checks++; break;
		case PLAYER_ACTION_CALL :	myStatistics[nbPlayers].m_flopStatistics.m_calls++; break;
		case PLAYER_ACTION_BET :	myStatistics[nbPlayers].m_flopStatistics.m_bets++; break;
	}
	if (myAction == PLAYER_ACTION_RAISE && currentHand->getRaisersPositions().size() > 0)
		myStatistics[nbPlayers].m_flopStatistics.m_threeBets++; 

	// continuation bets
	if (currentHand->getPreflopLastRaiserID() == myID){
		myStatistics[nbPlayers].m_flopStatistics.m_continuationBetsOpportunities++;
		if (myAction == PLAYER_ACTION_BET)
			myStatistics[nbPlayers].m_flopStatistics.m_continuationBets++;
	}


}
void Player::updateTurnStatistics(){

	const int nbPlayers = currentHand->getActivePlayerList()->size();
	myStatistics[nbPlayers].m_turnStatistics.m_hands++;

	switch (myAction){
		case PLAYER_ACTION_ALLIN :  myStatistics[nbPlayers].m_turnStatistics.m_raises++; break;
		case PLAYER_ACTION_RAISE :  myStatistics[nbPlayers].m_turnStatistics.m_raises++; break;
		case PLAYER_ACTION_FOLD :	myStatistics[nbPlayers].m_turnStatistics.m_folds++; break;
		case PLAYER_ACTION_CHECK :  myStatistics[nbPlayers].m_turnStatistics.m_checks++; break;
		case PLAYER_ACTION_CALL :	myStatistics[nbPlayers].m_turnStatistics.m_calls++; break;
		case PLAYER_ACTION_BET :	myStatistics[nbPlayers].m_turnStatistics.m_bets++; break;
	}
	if (myAction == PLAYER_ACTION_RAISE && currentHand->getRaisersPositions().size() > 0)
		myStatistics[nbPlayers].m_turnStatistics.m_threeBets++; 

}
void Player::updateRiverStatistics(){

	const int nbPlayers = currentHand->getActivePlayerList()->size();
	myStatistics[nbPlayers].m_riverStatistics.m_hands++;

	switch (myAction){
		case PLAYER_ACTION_ALLIN :  myStatistics[nbPlayers].m_riverStatistics.m_raises++; break;
		case PLAYER_ACTION_RAISE :  myStatistics[nbPlayers].m_riverStatistics.m_raises++; break;
		case PLAYER_ACTION_FOLD :	myStatistics[nbPlayers].m_riverStatistics.m_folds++; break;
		case PLAYER_ACTION_CHECK :  myStatistics[nbPlayers].m_riverStatistics.m_checks++; break;
		case PLAYER_ACTION_CALL :	myStatistics[nbPlayers].m_riverStatistics.m_calls++; break;
		case PLAYER_ACTION_BET :	myStatistics[nbPlayers].m_riverStatistics.m_bets++; break;
	}
	if (myAction == PLAYER_ACTION_RAISE && currentHand->getRaisersPositions().size() > 0)
		myStatistics[nbPlayers].m_riverStatistics.m_threeBets++; 

}

void Player::loadStatistics(){

	resetPlayerStatistics();// reset stats to 0

	sqlite3 *db;
	boost::filesystem::path sqliteLogFileName;

	DIR *logDir;
	logDir = opendir((myConfig->readConfigString("LogDir")).c_str());
	bool dirExists = logDir != NULL;
	closedir(logDir);

	// check if logging path exist
	if(myConfig->readConfigString("LogDir") != "" && dirExists) {

		sqliteLogFileName.clear();
		sqliteLogFileName /= myConfig->readConfigString("LogDir");
		sqliteLogFileName /= string("pokerTraining-log.pdb");

		// open sqlite-db
		int rc = sqlite3_open(sqliteLogFileName.string().c_str(), &db);

		if( rc ) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}

		char *errmsg = 0;

		string sql_select = "SELECT * FROM PlayersStatistics WHERE player_name = '" + myName + "';";
    
		sqlite3_stmt *stmt;
		
		rc = sqlite3_prepare_v2(db, sql_select.c_str(), -1, &stmt, 0);

		if (rc == SQLITE_OK) {

			int nCols = sqlite3_column_count(stmt);

			if (nCols)	{

				while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){

					int nbPlayers = 0;

					for (int nCol = 0; nCol < nCols; nCol++){

						const char *colName = sqlite3_column_name(stmt, nCol);

						if (strcmp(colName, "nb_players") == 0)
							nbPlayers = sqlite3_column_int(stmt, nCol);
						else

						// preflop
						if (strcmp(colName, "pf_hands") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_hands = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_folds") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_folds = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_checks") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_checks = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_calls") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_calls = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_raises") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_raises = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_limps") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_limps = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_threeBets") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_threeBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "pf_fourBets") == 0)
							myStatistics[nbPlayers].m_preflopStatistics.m_fourBets = sqlite3_column_int(stmt, nCol);
						else

						// flop
						if (strcmp(colName, "f_hands") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_hands = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_folds") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_folds = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_checks") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_checks = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_calls") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_calls = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_raises") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_raises = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_bets") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_bets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_threeBets") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_threeBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_fourBets") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_fourBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_continuationBets") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_continuationBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "f_continuationBetsOpportunities") == 0)
							myStatistics[nbPlayers].m_flopStatistics.m_continuationBetsOpportunities = sqlite3_column_int(stmt, nCol);
						else

						// turn
						if (strcmp(colName, "t_hands") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_hands = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_folds") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_folds = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_checks") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_checks = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_calls") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_calls = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_raises") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_raises = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_bets") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_bets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_threeBets") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_threeBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_fourBets") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_fourBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_hands") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_hands = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "t_folds") == 0)
							myStatistics[nbPlayers].m_turnStatistics.m_folds = sqlite3_column_int(stmt, nCol);
						else

						// river
						if (strcmp(colName, "r_checks") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_checks = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "r_calls") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_calls = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "r_raises") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_raises = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "r_bets") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_bets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "r_threeBets") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_threeBets = sqlite3_column_int(stmt, nCol);
						else
						if (strcmp(colName, "r_fourBets") == 0)
							myStatistics[nbPlayers].m_riverStatistics.m_fourBets = sqlite3_column_int(stmt, nCol);
					}
				}
			}
			sqlite3_finalize(stmt);
		}
		sqlite3_close(db);
	}
}

const PostFlopState Player::getPostFlopState(){

	std::string stringHand = getCardsValueString();
	std::string stringBoard = getStringBoard();

	PostFlopState r;

	GetHandState((stringHand + stringBoard).c_str(), &r);

	return r;
}
bool Player::checkIfINeedToShowCards()
{
	std::list<unsigned> playerNeedToShowCardsList = currentHand->getBoard()->getPlayerNeedToShowCards();
	for(std::list<unsigned>::iterator it = playerNeedToShowCardsList.begin(); it != playerNeedToShowCardsList.end(); ++it) {
		if(*it == myUniqueID) return true;
	}

	return false;
}
std::string Player::getStringBoard(){

	int cardsOnBoard;

	if (currentHand->getCurrentRound() == GAME_STATE_FLOP)
		cardsOnBoard = 3;
	else
	if (currentHand->getCurrentRound() == GAME_STATE_TURN)
		cardsOnBoard = 4;
	else
	if (currentHand->getCurrentRound() == GAME_STATE_RIVER)
		cardsOnBoard = 5;
	else
		cardsOnBoard = 0;

	std::string stringBoard;
	int board[5];
	currentHand->getBoard()->getCards(board);

	for(int i = 0; i < cardsOnBoard; i++){
		stringBoard += " ";
		stringBoard += CardsValue::CardStringValue[board[i]];
	}

	return stringBoard;
}
int Player::getBoardCardsHigherThan(std::string card){

	string stringBoard = getStringBoard();

	std::istringstream oss(stringBoard);
	std::string boardCard;
	
	int n = 0;

	while(getline(oss, boardCard, ' ')) {
		
		if (CardsValue::CardStringOrdering[boardCard] > CardsValue::CardStringOrdering[card])
			n++;
	}
	return n;
}

bool Player::getHavePosition(PlayerPosition myPos, PlayerList & runningPlayers){
	// return true if myPos is last to play, false if not

	bool havePosition = true;

	PlayerListConstIterator it_c;

	for (it_c=runningPlayers->begin(); it_c!=runningPlayers->end(); ++it_c) {

		if ((*it_c)->getPosition () > myPos) 
			havePosition = false;
	}

	return havePosition;
}

boost::shared_ptr<Player> Player::getPlayerByUniqueId(unsigned id)
{
	boost::shared_ptr<Player> tmpPlayer;
	PlayerListIterator i = currentHand->getSeatsList()->begin();
	PlayerListIterator end = currentHand->getSeatsList()->end();
	while (i != end) {
		if ((*i)->getUniqueID() == id) {
			tmpPlayer = *i;
			break;
		}
		++i;
	}
	return tmpPlayer;
}

bool  Player::isCardsInRange(string card1, string card2, string ranges){

	// process individual ranges, from a string looking like "33,56s+,99+,ATs+,KJs+,QJs,JTs,AQo+"
	
	//card1 = "7h";
	//card2 = "6h";
	//ranges = "74s+";
	//ranges = CUTOFF_STARTING_RANGE[10];

	// first card must be the highest
	if (CardsValue::CardStringOrdering[card1] < CardsValue::CardStringOrdering[card2]){
		string tmp = card1;
		card1 = card2;
		card2 = tmp;
	}

	const char * c1 = card1.c_str();
	const char * c2 = card2.c_str();

	std::istringstream oss(ranges);
	std::string token;

	while(getline(oss, token, ',')) {
		
		if (token.size() == 0)
			continue;

		if (token.size() == 1 || token.size() > 4){
			cout << "invalid range : " << token << endl;
			return false;
		}
		const char * range = token.c_str();

		if (token.size() == 2){ // an exact pair, like 55 or AA

			if (c1[0] == range[0] && c2[0] == range[1]){
				return true;
			}
		}
		if (token.size() == 3){

			if (range[0] != range[1] && range[2] == 's'){ // range is an exact suited hand, like QJs
				if (c1[0] == range[0] && c2[0] == range[1] && (c1[1] == c2[1])){
					return true;
				}
			}

			if (range[0] != range[1] && range[2] == 'o'){ // range is an exact offsuited cards, like KTo
				if (c1[0] == range[0] && c2[0] == range[1] && (c1[1] != c2[1])){
					return true;
				}
			}
			if (range[0] == range[1] && range[2] == '+'){ // range is a pair and above, like 99+
				if (CardsValue::CardStringOrdering[card1] == CardsValue::CardStringOrdering[card2]){
					// we have a pair. Is it above the minimum value ?
					if (CardsValue::CardStringOrdering[card1] >= CardsValue::CardStringOrdering[getFakeCard(range[0])])
						return true;
				}
			}
		}
		if (token.size() == 4){

			if (range[0] != range[1] && range[2] == 'o' && range[3] == '+'){ 
				// range is offsuited and above, like AQo+
				if (CardsValue::CardStringOrdering[card1] == CardsValue::CardStringOrdering[getFakeCard(range[0])] &&
					CardsValue::CardStringOrdering[card2] >= CardsValue::CardStringOrdering[getFakeCard(range[1])] &&
					c1[1] != c2[1])
					return true;
			}
			if (range[0] != range[1] && range[2] == 's' && range[3] == '+'){ 
				// range is suited and above, like AJs+
				if (CardsValue::CardStringOrdering[card1] == CardsValue::CardStringOrdering[getFakeCard(range[0])] &&
					CardsValue::CardStringOrdering[card2] >= CardsValue::CardStringOrdering[getFakeCard(range[1])] &&
					c1[1] == c2[1])
					return true;
			}
		}
	}

	// cout << "NOT in range" << endl;
	return false;
}

// convert a range into a  list of real cards
std::vector<std::string> Player::getRangeAtomicValues(std::string ranges){

	vector<std::string> result;

	std::istringstream oss(ranges);
	std::string token;

	while(getline(oss, token, ',')) {
		
		if (token.size() == 0)
			continue;

		if (token.size() == 1 || token.size() > 4){
			std::cout << "invalid range : " << token << endl;
			return result;
		}

		const char * range = token.c_str();

		if (token.size() == 2){ // an exact pair, like 55 or AA
			result.push_back(range);
			continue;
		}

		if (token.size() == 3){

			if (range[0] != range[1] && range[2] == 's'){ // range is an exact suited hand, like QJs

				string s1;
				s1 = range[0];
				string s2;
				s2 = range[1];

				result.push_back(s1 + 's' + s2 + 's');
				result.push_back(s1 + 'd' + s2 + 'd');
				result.push_back(s1 + 'h' + s2 + 'h');
				result.push_back(s1 + 'c' + s2 + 'c');

				continue;
			}

			if (range[0] != range[1] && range[2] == 'o'){ // range is an exact offsuited cards, like KTo

				string s1;
				s1 = range[0];
				string s2;
				s2 = range[1];

				result.push_back(s1 + 's' + s2 + 'd');
				result.push_back(s1 + 's' + s2 + 'c');
				result.push_back(s1 + 's' + s2 + 'h');

				result.push_back(s1 + 'd' + s2 + 's');
				result.push_back(s1 + 'd' + s2 + 'c');
				result.push_back(s1 + 'd' + s2 + 'h');

				result.push_back(s1 + 'h' + s2 + 'd');
				result.push_back(s1 + 'h' + s2 + 'c');
				result.push_back(s1 + 'h' + s2 + 's');

				result.push_back(s1 + 'c' + s2 + 'd');
				result.push_back(s1 + 'c' + s2 + 's');
				result.push_back(s1 + 'c' + s2 + 'h');

				continue;
			}

			if (range[0] == range[1] && range[2] == '+'){ // range is a pair and above, like 99+
				char c = range[0];

				while(c != 'X'){

					string s;
					s = c;
					result.push_back(s + 's' + s + 'd');
					result.push_back(s + 's' + s + 'c');
					result.push_back(s + 's' + s + 'h');

					result.push_back(s + 'd' + s + 's');
					result.push_back(s + 'd' + s + 'c');
					result.push_back(s + 'd' + s + 'h');

					result.push_back(s + 'h' + s + 'd');
					result.push_back(s + 'h' + s + 'c');
					result.push_back(s + 'h' + s + 's');

					result.push_back(s + 'c' + s + 'd');
					result.push_back(s + 'c' + s + 's');
					result.push_back(s + 'c' + s + 'h');

					// next value :
					c = incrementCardValue(c);
				}
				continue;
			}
		}

		if (token.size() == 4){

			if (range[0] != range[1] && range[2] == 'o' && range[3] == '+'){ 

				// range is offsuited and above, like AQo+

				string s1;
				s1 = range[0];
				char c = range[1];

				while(c != range[0]){

					string s2;
					s2 = c;

					result.push_back(s1 + 's' + s2 + 'd');
					result.push_back(s1 + 's' + s2 + 'c');
					result.push_back(s1 + 's' + s2 + 'h');

					result.push_back(s1 + 'd' + s2 + 's');
					result.push_back(s1 + 'd' + s2 + 'c');
					result.push_back(s1 + 'd' + s2 + 'h');

					result.push_back(s1 + 'h' + s2 + 'd');
					result.push_back(s1 + 'h' + s2 + 'c');
					result.push_back(s1 + 'h' + s2 + 's');

					result.push_back(s1 + 'c' + s2 + 'd');
					result.push_back(s1 + 'c' + s2 + 's');
					result.push_back(s1 + 'c' + s2 + 'h');

					// next value :
					c = incrementCardValue(c);
				}
				continue;

			}
			if (range[0] != range[1] && range[2] == 's' && range[3] == '+'){ 

				// range is suited and above, like AQs+

				string s1;
				s1 = range[0];
				char c = range[1];

				while(c != range[0]){

					string s2;
					s2 = c;

					result.push_back(s1 + 's' + s2 + 's');
					result.push_back(s1 + 'd' + s2 + 'd');
					result.push_back(s1 + 'h' + s2 + 'h');
					result.push_back(s1 + 'c' + s2 + 'c');

					// next value :
					c = incrementCardValue(c);
				}
				continue;
			}
		}
	}

	return result;

}

char Player::incrementCardValue(char c){

	switch (c){
		case '2' : return '3';
		case '3' : return '4';
		case '4' : return '5';
		case '5' : return '6';
		case '6' : return '7';
		case '7' : return '8';
		case '8' : return '9';
		case '9' : return 'T';
		case 'T' : return 'J';
		case 'J' : return 'Q';
		case 'Q' : return 'K';
		case 'K' : return 'A';
		default : return 'X';
	}
}

string Player::getFakeCard(char c){

	char tmp[3];  
	tmp[0] = c;
	tmp[1] = 'c'; 
	tmp[2] = NULL; 
	return string(tmp);
}

int Player::getPotOdd(){

	const int highestSet = min(myCash, currentHand->getCurrentBettingRound()->getHighestSet());

	int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();

	int odd = highestSet * 100 / pot;
	assert(odd >= 0 && odd <= 100);

#ifdef LOG_POKER_EXEC
	//cout << endl << "Pot odd : " << odd << endl;
#endif
	return odd;

}

float Player::getM(){

	int blinds = currentHand->getSmallBlind() + (currentHand->getSmallBlind() * 2) ; // assume for now that BB is 2 * SB
	return (float) myCash / blinds;

}

void Player::initializeRanges(const int utgHeadsUpRange, const int utgFullTableRange){

	const float step = (float)(utgHeadsUpRange - utgFullTableRange) / 8;

	// values are % best hands

	UTG_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	UTG_STARTING_RANGE[2] = utgHeadsUpRange;
	UTG_STARTING_RANGE[3] = utgHeadsUpRange - step;
	UTG_STARTING_RANGE[4] = utgHeadsUpRange - (2 * step);
	UTG_STARTING_RANGE[5] = utgHeadsUpRange - (3 * step);
	UTG_STARTING_RANGE[6] = utgHeadsUpRange - (4 * step);
	UTG_STARTING_RANGE[7] = utgFullTableRange + (3 * step);
	UTG_STARTING_RANGE[8] = utgFullTableRange + (2 * step);
	UTG_STARTING_RANGE[9] = utgFullTableRange + step;
	UTG_STARTING_RANGE[10] = utgFullTableRange;

	assert(UTG_STARTING_RANGE[7] < UTG_STARTING_RANGE[6]);

	// we have the UTG starting ranges. Now, dededuce the starting ranges for other positions :

	UTG_PLUS_ONE_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < UTG_PLUS_ONE_STARTING_RANGE.size(); i++){
		UTG_PLUS_ONE_STARTING_RANGE[i] = min(50, UTG_STARTING_RANGE[i] + 2);
	}

	UTG_PLUS_TWO_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < UTG_PLUS_TWO_STARTING_RANGE.size(); i++){
		UTG_PLUS_TWO_STARTING_RANGE[i] = min(50, UTG_PLUS_ONE_STARTING_RANGE[i] + 2);
	}

	MIDDLE_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < MIDDLE_STARTING_RANGE.size(); i++){
		MIDDLE_STARTING_RANGE[i] = min(50, UTG_PLUS_TWO_STARTING_RANGE[i] + 2);
	}

	MIDDLE_PLUS_ONE_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < MIDDLE_PLUS_ONE_STARTING_RANGE.size(); i++){
		MIDDLE_PLUS_ONE_STARTING_RANGE[i] = min(50, MIDDLE_STARTING_RANGE[i] + 2);
	}

	LATE_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < LATE_STARTING_RANGE.size(); i++){
		LATE_STARTING_RANGE[i] = min(50, MIDDLE_PLUS_ONE_STARTING_RANGE[i] + 2);
	}

	CUTOFF_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < CUTOFF_STARTING_RANGE.size(); i++){
		CUTOFF_STARTING_RANGE[i] = min(50,LATE_STARTING_RANGE[i] + 2);
	}

	BUTTON_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < BUTTON_STARTING_RANGE.size(); i++){
		BUTTON_STARTING_RANGE[i] = min(50,CUTOFF_STARTING_RANGE[i] + 2);
	}

	SB_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < SB_STARTING_RANGE.size(); i++){
		SB_STARTING_RANGE[i] = min(50, BUTTON_STARTING_RANGE[i] + 2);
	}

	BB_STARTING_RANGE.resize(MAX_NUMBER_OF_PLAYERS+1);
	for (int i=2; i < BB_STARTING_RANGE.size(); i++){
		BB_STARTING_RANGE[i] = min(50, SB_STARTING_RANGE[i] + 2);
	}
}

int Player::getRange(PlayerPosition p){

	int nbPlayers = currentHand->getActivePlayerList()->size(); 

	switch (p){

		case UTG : return UTG_STARTING_RANGE[nbPlayers]; break;
		case UTG_PLUS_ONE : return UTG_PLUS_ONE_STARTING_RANGE[nbPlayers]; break;
		case UTG_PLUS_TWO : return UTG_PLUS_TWO_STARTING_RANGE[nbPlayers]; break;
		case MIDDLE : return MIDDLE_STARTING_RANGE[nbPlayers]; break;
		case MIDDLE_PLUS_ONE : return MIDDLE_PLUS_ONE_STARTING_RANGE[nbPlayers]; break;			
		case LATE : return LATE_STARTING_RANGE[nbPlayers]; break;
		case CUTOFF : return CUTOFF_STARTING_RANGE[nbPlayers]; break;
		case BUTTON : return BUTTON_STARTING_RANGE[nbPlayers]; break;
		case SB : return SB_STARTING_RANGE[nbPlayers]; break;
		case BB : return BB_STARTING_RANGE[nbPlayers]; break;
		default : return 0;
	}
}
const SimResults Player::getHandSimulation(){

	SimResults r;
	const string cards = (getCardsValueString() + getStringBoard()).c_str();

	SimulateHand(cards.c_str() , &r, 0, 1, 0);
	float win = r.win; //save the value
	
	const int nbOpponents = max(1, currentHand->getRunningPlayerList()->size() - 1); // note that allin opponents are not "running" any more
	SimulateHandMulti(cards.c_str() , &r, 1300, 350, nbOpponents);
	r.win = win; // because SimulateHandMulti doesn't compute 'win'

	// evaluate my strength against my opponents's guessed ranges :
	float maxOpponentsStrengths = getMaxOpponentsStrengths();

	r.winRanged = 1 - maxOpponentsStrengths;

#ifdef LOG_POKER_EXEC
	cout	<< endl << "\tsimulation with " << cards << " : " << endl
			<< "\t\twin at showdown is " << r.winSd << endl
			<< "\t\ttie at showdown is " << r.tieSd << endl
			<< "\t\twin now (against random hands)  is " << r.win << endl
			<< "\t\twin now (against ranged hands) is " << r.winRanged << endl;

	if (getPotOdd() > 0)
		cout << "\t\tpot odd is " << getPotOdd() << endl;

#endif

	return r;
}

float Player::getMaxOpponentsStrengths(){

	std::map<int, float> strenghts = evaluateOpponentsStrengths(); // id player --> % of possible hands that beat us
	
	float maxOpponentsStrengths = 0;

	for (std::map<int, float>::const_iterator i = strenghts.begin(); i != strenghts.end(); i++){

		assert(i->second <= 1.0);
		if (i->second > maxOpponentsStrengths)
			maxOpponentsStrengths = i->second;
	}

	// adjust roughly maxOpponentsStrengths value according to the number of opponents : the more opponents, the more chances we are beaten

	if (strenghts.size() == 2) // 2 opponents
		maxOpponentsStrengths = maxOpponentsStrengths * 1.1;
	else
	if (strenghts.size() == 3) // 3 opponents
		maxOpponentsStrengths = maxOpponentsStrengths * 1.2;
	else
	if (strenghts.size() == 4) // 4 opponents
		maxOpponentsStrengths = maxOpponentsStrengths * 1.3;
	else 
	if (strenghts.size() > 4) 
		maxOpponentsStrengths = maxOpponentsStrengths * 1.4;

	// adjust roughly maxOpponentsStrengths value according to the number of raises : the more raises, the more chances we are beaten

	const int nbRaises =	currentHand->getFlopBetsOrRaisesNumber() +
							currentHand->getTurnBetsOrRaisesNumber() +
							currentHand->getRiverBetsOrRaisesNumber();

	if (nbRaises == 2) 
		maxOpponentsStrengths = maxOpponentsStrengths * 1.2;
	else
	if (nbRaises == 3) 
		maxOpponentsStrengths = maxOpponentsStrengths * 1.5;
	else
	if (nbRaises == 4) 
		maxOpponentsStrengths = maxOpponentsStrengths * 2;
	else 
	if (nbRaises > 4) 
		maxOpponentsStrengths = maxOpponentsStrengths * 3;

	if (maxOpponentsStrengths > 1)
		maxOpponentsStrengths = 1;

	return maxOpponentsStrengths;

}

// get an opponent winning hands % against me, giving his supposed range, and the board
float Player::getOpponentWinningHandsPercentage(std::string board, std::string stringRanges){

	float result = 0;
	
	// cout << "ranges : " << stringRanges << " , corresponding cards : " << endl;

	// split the ranges in atomic values
	vector<std::string> ranges = getRangeAtomicValues(stringRanges);

	assert(ranges.size() > 0);

	vector<std::string> newRanges;

	// delete hands that can't exist, given the known cards
	for (vector<std::string>::const_iterator i = ranges.begin(); i != ranges.end(); i++){
		
		string s1 = (*i).substr(0,2);
		string s2 = (*i).substr(2,4);

		if (board.find(s1) != string::npos || myCard1.find(s1) != string::npos || myCard2.find(s1) != string::npos ||			
			board.find(s2) != string::npos || myCard1.find(s2) != string::npos || myCard2.find(s2) != string::npos){
			// cout << "deleting " << (*i) << endl; 
			continue;
		}

		newRanges.push_back(*i);

	}
	if (newRanges.size() == 0){
		newRanges.push_back("AhAc");
		newRanges.push_back("KhKc");
	}

	const int myRank = RankHand((myCard1 + myCard2 + board).c_str());

	// compute winning hands % against my rank
	int nbWinningHands = 0;
	for (vector<std::string>::const_iterator i = newRanges.begin(); i != newRanges.end(); i++){
		// cout << (*i) << endl;
		if (RankHand(((*i) + board).c_str()) > myRank)
			nbWinningHands++;
	}
	assert(nbWinningHands / newRanges.size() <= 1.0);
	return (float)nbWinningHands / (float)newRanges.size();

}

void Player::DisplayHandState(const PostFlopState* state)   {

#ifdef LOG_POKER_EXEC

	cout << "\t";

	if (! state->UsesFirst && ! state->UsesSecond)
		cout << "Playing the board, ";
	else if (state->UsesFirst && ! state->UsesSecond)
		cout << "Using only first hole card, ";
	else if (! state->UsesFirst && state->UsesSecond)
		cout << "Using only second hole card, ";
	else if (state->UsesFirst && state->UsesSecond)
		cout << "Using both hole cards, ";

	if (state->IsNoPair)
	{
		if (state->IsOverCards)
			cout << "with over cards";
		else
			cout << "with high card";
	}
	else if (state->IsOnePair)
	{
		if (state->IsTopPair)
			cout << "with top pair";
		else if (state->IsMiddlePair)
			cout << "with middle pair";
		else if (state->IsBottomPair)
			cout << "with bottom pair";
		else if (state->IsOverPair)
			cout << "with over pair";
		else if (state->IsPocketPair)
			cout << "with pocket pair";
		else if (state->IsFullHousePossible)
			cout << "with one pair on board";
		else
			cout << "with one pair ";
	}
	else if (state->IsTwoPair)
		cout << "with two pair";
	else if (state->IsTrips)
		cout << "with trips";
	else if (state->IsStraight)
		cout << "with a straight";
	else if (state->IsFlush)
		cout << "with a flush";
	else if (state->IsFullHouse)
		cout << "with a full house";
	else if (state->IsQuads)
		cout << "with quads";
	else if (state->IsStFlush)
		cout << "with a straight flush";

	//Do we have a flush and straight draw?
	bool flushDraw = (state->Is3Flush || state->Is4Flush);
	bool straightDraw = (state->StraightOuts);
	bool anotherDraw = ( flushDraw && straightDraw);

	if (anotherDraw)
		cout << ", ";
	else
		if (flushDraw || straightDraw)
			cout << " and ";

	if (state->Is4Flush)
		cout << "4 flush cards (" << state->FlushOuts << " outs)";
	else if (state->Is3Flush)
		cout << "3 flush cards";

	if (anotherDraw)
		cout << ", and ";

	if (straightDraw)
		cout << state->StraightOuts << " outs to a straight";

	cout << ".";

	if (state->BetterOuts)
		cout << " " << state->BetterOuts << " outs to boat or better.";

	if (state->IsFlushPossible)
		cout << " Someone may have a flush.";
	else if (state->IsFlushDrawPossible)
		cout << " Someone may be drawing to a flush.";

	if (state->IsStraightPossible)
		cout << " Someone may have a straight.";
	else if (state->IsStraightDrawPossible)
		cout << " Someone may be drawing to a straight.";


	if (state->IsFullHousePossible)
		cout << " The board is paired.";

#endif

}


// returns a % chance, for a winning draw 
const int Player::getDrawingProbability(){

	PostFlopState state;

	if (currentHand->getCurrentRound() == GAME_STATE_FLOP)
		state = myFlopState;
	else if (currentHand->getCurrentRound() == GAME_STATE_TURN)
		state = myTurnState;
	else
		return 0;

	int outs = 0;

	// do not count outs for straight or flush, is the board is paired

	if (! state.IsFullHousePossible)
		outs = state.StraightOuts + state.FlushOuts + state.BetterOuts;
	else
		outs = state.BetterOuts;

	if (outs == 0)
		return 0;

	if (outs > 20)
		outs = 20;

	// if the last raiser is allin on flop : we must count our odds for the turn AND the river 
	if (currentHand->getCurrentRound() == GAME_STATE_FLOP){

		const int lastRaiserID = currentHand->getLastRaiserID();

		if (lastRaiserID != -1){
			boost::shared_ptr<Player> lastRaiser = getPlayerByUniqueId(lastRaiserID);
			const std::vector<PlayerAction> & actions = lastRaiser->getCurrentHandActions().getFlopActions();

			for (std::vector<PlayerAction>::const_iterator itAction = actions.begin(); itAction != actions.end(); itAction++)
				if	((*itAction) == PLAYER_ACTION_ALLIN) 
					return outsOddsTwoCard[outs];
		}
	}

	return outsOddsOneCard[outs];
}

const int Player::getImplicitOdd(){

	//const int nbPlayers =	currentHand->getRunningPlayerList()->size();

	// TODO compute implicit odd according to opponent's profiles and actions in this hand

	int implicitOdd = 0;

	PlayerList players = currentHand->getRunningPlayerList(); // note that all in players are not "running" any more

	for(PlayerListIterator it=players->begin(); it!=players->end(); ++it) {

		if ((*it)->getID() == myID)
			continue;

		if((*it)->getCash() >= currentHand->getBoard()->getPot() * 2)
			implicitOdd += 12;
		else
		if((*it)->getCash() >= currentHand->getBoard()->getPot())
			implicitOdd += 7;

	}

	return implicitOdd;
}

std::map<int, float> Player::evaluateOpponentsStrengths(){

	map<int,float> result;
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	PlayerList players = currentHand->getActivePlayerList();
	const int lastRaiserID = currentHand->getPreflopLastRaiserID();
	const int nbRaises = currentHand->getPreflopRaisesNumber();

#ifdef LOG_POKER_EXEC	
	cout << endl;
#endif

	for(PlayerListIterator it=players->begin(); it!=players->end(); ++it) {

		if ((*it)->getID() == myID || (*it)->getAction() == PLAYER_ACTION_FOLD)
			continue;

		PreflopStatistics stats = (*it)->getStatistics(nbPlayers).getPreflopStatistics();

		// if not enough hands, then try to use the statistics collected for (nbPlayers + 1), they should be more accurate
		if (stats.m_hands < 20 && nbPlayers < 10 && (*it)->getStatistics(nbPlayers + 1).getPreflopStatistics().m_hands > 20)
			stats = (*it)->getStatistics(nbPlayers + 1).getPreflopStatistics();

		int preflopRange = 0;
		
		if ((*it)->getID() == lastRaiserID)
			preflopRange = (int)stats.getPreflopRaise();
		else
			preflopRange = (int)stats.getVoluntaryPutMoneyInPot();

		if (((*it)->getPosition() == BUTTON || (*it)->getPosition() == CUTOFF) && currentHand->getRunningPlayerList()->size() > 5)
			preflopRange = preflopRange * 0.7;

		if (nbRaises == 2)
			preflopRange = preflopRange * 0.7;
		else
		if (nbRaises == 3)
			preflopRange = preflopRange * 0.5;
		else
		if (nbRaises == 4)
			preflopRange = preflopRange * 0.3;
		else
		if (nbRaises > 4)
			preflopRange = 1;

		if (preflopRange > 65)
			preflopRange = 65;

		if (stats.m_hands < 20 && preflopRange > 15) // not enough hands, assume the opponent is an average tight player
			preflopRange = 15;

		string estimatedRange;

		if (nbPlayers == 2)
			estimatedRange = TOP_RANGE_2_PLAYERS[preflopRange];
		else if (nbPlayers == 3)
			estimatedRange = TOP_RANGE_3_PLAYERS[preflopRange];
		else if (nbPlayers == 4)
			estimatedRange = TOP_RANGE_4_PLAYERS[preflopRange];
		else
			estimatedRange = TOP_RANGE_MORE_4_PLAYERS[preflopRange];

		const float estimatedOpponentWinningHands = getOpponentWinningHandsPercentage(getStringBoard(), estimatedRange);
		assert(estimatedOpponentWinningHands <= 1.0);

		result[(*it)->getID()] = estimatedOpponentWinningHands;

#ifdef LOG_POKER_EXEC			
		cout << endl << "\t" << (*it)->getName() << ", estimated winning hands : " << estimatedOpponentWinningHands 
				<< ", estimated range : " << preflopRange << "%  " << estimatedRange << endl;
#endif

	}

	return result;
}

bool Player::isDrawingProbOk(){

	const int potOdd = getPotOdd();

	if(! (currentHand->getCurrentRound() == GAME_STATE_FLOP || currentHand->getCurrentRound() == GAME_STATE_TURN))
		return false;

	int implicitOdd = getImplicitOdd();
	int drawingProb = getDrawingProbability();

	if (drawingProb > 0){
		if (drawingProb + implicitOdd >= potOdd){
#ifdef LOG_POKER_EXEC
			cout << endl << "Drawing prob is ok : " << drawingProb << " + " << implicitOdd << " > " << potOdd << endl;
#endif
			return true;
		}
	}		

	return false;
}

float Player::getPreflopCallingRange(){

	const int nbRaises = currentHand->getPreflopRaisesNumber();
	const int nbCalls = currentHand->getPreflopCallsNumber();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	assert(nbPlayers >= 2);
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int lastRaiserID = currentHand->getPreflopLastRaiserID();
	boost::shared_ptr<Player> lastRaiser = getPlayerByUniqueId(lastRaiserID);

	float callingRange = getRange(myPosition);

	if (nbRaises == 0 && nbCalls == 0 && myPosition < MIDDLE_PLUS_ONE && nbPlayers > 4)
		// never limp if nobody has limped, and early position
		return -1;

	if (nbRaises == 0 && nbCalls > 0) // 1 or more players have limped, but nobody has raised
		callingRange = callingRange * 1.2;
	
	if (nbRaises == 0){ 
		if (callingRange > 65)
			callingRange = 65;
		return callingRange;
	}		
		
	// one or more players raised or re-raised :

	PreflopStatistics raiserStats = lastRaiser->getStatistics(nbPlayers).getPreflopStatistics();

	// if not enough hands, then try to use the statistics collected for (nbPlayers + 1), they should be more accurate
	if (raiserStats.m_hands < 10 && nbPlayers < 10 && lastRaiser->getStatistics(nbPlayers + 1).getPreflopStatistics().m_hands > 10)
		raiserStats = lastRaiser->getStatistics(nbPlayers + 1).getPreflopStatistics();

	if (raiserStats.m_hands > 10 && raiserStats.getPreflopRaise() != 0)
		// adjust range according to the last raiser's stats
		if ((myPosition == BUTTON || myPosition == CUTOFF) && runningPlayers->size() > 5)
			callingRange = raiserStats.getPreflopRaise() * 0.7;
		else
			callingRange = raiserStats.getPreflopRaise() * 0.5;
	else
		// no stats available
		callingRange = (myPosition == BUTTON || myPosition == CUTOFF ?	callingRange * 0.8 : callingRange * 0.7);

	if (nbRaises == 2) // 3bet
		callingRange = callingRange * .4;
	else
	if (nbRaises == 3) // 4bet
		callingRange = callingRange * .1;			
	else
	if (nbRaises > 3) // 5bet or more
		callingRange = callingRange * .05;

	const int potOdd = getPotOdd();

	// if big bet, tighten again
	if (potOdd > 66 && potOdd < 85 ) 
		callingRange = callingRange * 0.7;
	else
		if (potOdd >= 85 && potOdd < 95 )
			callingRange = callingRange * 0.5;
		else
			if (potOdd >= 95 )
				callingRange = callingRange * 0.3;

	// if players have already called the big bet, tighten again
	callingRange = callingRange / (currentHand->getCallersPositions().size() + 1);

	if (callingRange < 1)
		callingRange = 1;

	// if the odds are good, call
	if (potOdd < 30 && potOdd > 20)
		callingRange = 30;

	if (potOdd <= 20)
		callingRange = 50;

	if (callingRange > 65)
		callingRange = 65;

	return callingRange;
}


float Player::getPreflopRaisingRange(){

	const int nbRaises = currentHand->getPreflopRaisesNumber();
	const int nbCalls = currentHand->getPreflopCallsNumber();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	assert(nbPlayers >= 2);
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();
	const int sets = currentHand->getBoard()->getSets();
	const int lastRaiserID = currentHand->getPreflopLastRaiserID();
	boost::shared_ptr<Player> lastRaiser = getPlayerByUniqueId(lastRaiserID);

	float raisingRange = getRange(myPosition);

	if (nbRaises == 0 && nbCalls > 0) // 1 or more players have limped, but nobody has raised
		raisingRange = raisingRange * 0.7;

	if (nbRaises > 0){ 

		PreflopStatistics raiserStats = lastRaiser->getStatistics(nbPlayers).getPreflopStatistics();;
		
		// if not enough hands, then try to use the statistics collected for (nbPlayers + 1), they should be more accurate
		if (raiserStats.m_hands < 10 && nbPlayers < 10 && lastRaiser->getStatistics(nbPlayers + 1).getPreflopStatistics().m_hands > 10)
			raiserStats = lastRaiser->getStatistics(nbPlayers + 1).getPreflopStatistics();

		if (raiserStats.m_hands > 10 && raiserStats.getPreflopRaise() != 0){
			// adjust range according to the raiser's stats
			raisingRange = raiserStats.getPreflopRaise() * (lastRaiser->getPosition() < LATE ? 0.4 : 0.7);
		}else
			// no stats available for last raiser : tighten a bit our usual range
			raisingRange = raisingRange * 0.7;

		if (nbRaises == 2) // 3bet
			raisingRange = raisingRange * 0.2;
		else
		if (nbRaises > 2) // 4bet
			raisingRange = 0; // raise with aces only

		const int potOdd = getPotOdd();

		// if big bet
		if (potOdd > 66 && potOdd < 85 ) 
			raisingRange = raisingRange * 0.6;
		else
		if (potOdd >= 85 && potOdd < 95 )
			raisingRange = raisingRange * 0.3;
		else
		if (potOdd >= 95 )
			raisingRange = min(1, raisingRange * 0.2);

		// if players have called the big bet, tighten again
		raisingRange = raisingRange / (currentHand->getCallersPositions().size() + 1);

	}else{	// no previous raise

		// adjust my raising range according to my stack :

		// index is remaining hands to play, if i just fold every hand. Value is the minimum corresponding range for raising
		static const int mToMinimumRange[] = { 100, 75, 50, 50, 49, 48, 47, 47, 46, 45, /* M = 1 (full ring) */
													45, 45, 45, 45, 45,	44, 43, 42, 40, /* M = 2 */
													40, 40, 40, 40, 40,	39, 39, 38, 37, /* M = 3 */
													37, 37, 37, 37, 36,	36, 36, 36, 35, /* M = 4 */
													35, 35, 35, 35, 35,	35, 34, 33, 33, /* M = 5 */
													33, 33, 33, 33, 32,	32, 32, 31, 30, /* M = 6 */
													30, 30, 30, 30, 30,	29, 29, 28, 27, /* M = 7 */
													27, 27, 27, 27, 27,	26, 26, 26, 25, /* M = 8 */
													25, 25, 25, 25, 25,	24, 24, 24, 23, /* M = 9 */
													23, 23, 23, 22, 22,	22, 21, 21, 20}; /* M = 10 */


		// hands remaining before beeing broke, only with the blind cost
		const int handsLeft = getM() * nbPlayers;

		if (handsLeft < 90)
			raisingRange = (mToMinimumRange[handsLeft] > raisingRange ? mToMinimumRange[handsLeft] : raisingRange);

		// steal blinds
		if (myPosition == SB || myPosition == BUTTON || myPosition == CUTOFF){
			int rand = 0;
			Tools::GetRand(1, 4, 1, &rand);
			if (rand == 2){
				raisingRange = 65;
			}
		}
	}

	if (raisingRange < 0)
		raisingRange = 0;

	if (raisingRange > 65)
		raisingRange = 65;

	if (getPreflopCallingRange() != -1 && raisingRange != 65)
		return min(raisingRange, getPreflopCallingRange());
	else
		return raisingRange;
}




