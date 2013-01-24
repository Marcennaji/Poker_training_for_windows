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

#include "game.h"

#include <engine/enginefactory.h>
#include <qt/guiinterface.h>
#include <engine/log.h>

#include <engine/exception.h>
#include <engine/engine_msg.h>

#include <iostream>

using namespace std;

Game::Game(GuiInterface* gui, boost::shared_ptr<EngineFactory> factory,
		   const PlayerList &playerList, const GameData &gameData,
		   const StartData &startData, int gameId, Log* log)
	: myFactory(factory), myGui(gui), myLog(log), startQuantityPlayers(startData.numberOfPlayers),
	  startCash(gameData.startMoney), startSmallBlind(gameData.firstSmallBlind),
	  myGameID(gameId), currentSmallBlind(gameData.firstSmallBlind), currentHandID(0), dealerPosition(0),
	  lastHandBlindsRaised(1), lastTimeBlindsRaised(0), myGameData(gameData),
	  blindsTimer(boost::posix_time::time_duration(0, 0, 0), boost::timers::portable::second_timer::manual_start)
{

	blindsList = myGameData.manualBlindsList;

	dealerPosition = startData.startDealerPlayerId;

	if(DEBUG_MODE) {
		startSmallBlind = 10;
		currentSmallBlind = startSmallBlind;
		dealerPosition = 4;
	}

	int i;

	// determine dealer position
	PlayerListConstIterator player_i = playerList->begin();
	PlayerListConstIterator player_end = playerList->end();

	while (player_i != player_end) {
		if ((*player_i)->getUniqueID() == dealerPosition)
			break;
		++player_i;
	}
	if (player_i == player_end)
		throw Exception(__FILE__, __LINE__, ERR_DEALER_NOT_FOUND);

	// create board
	currentBoard = myFactory->createBoard(dealerPosition);

	// create player lists
	seatsList.reset(new std::list<boost::shared_ptr<Player> >);
	activePlayerList.reset(new std::list<boost::shared_ptr<Player> >);
	runningPlayerList.reset(new std::list<boost::shared_ptr<Player> >);

	// create player
	player_i = playerList->begin();
	player_end = playerList->end();
	for(i=0; i < startData.numberOfPlayers; i++) {

		string myName;
		string myAvatarFile;
		string myGuid;
		unsigned uniqueId = 0;
		PlayerType type = PLAYER_TYPE_COMPUTER;
		int myStartCash = startCash;
		bool myStayOnTableStatus = false;

		if (player_i != player_end) {
			uniqueId = (*player_i)->getUniqueID();
			type = (*player_i)->getType();
			myName = (*player_i)->getName();
			//myAvatarFile = (*player_i)->getAvatarFile();
			myGuid = (*player_i)->getGuid();
			if ((*player_i)->getCash() >= 0)
				myStartCash = (*player_i)->getCash();
			myStayOnTableStatus = type == PLAYER_TYPE_HUMAN;
			++player_i;
		}

		// create player objects
		boost::shared_ptr<Player> tmpPlayer = 
					myFactory->createPlayer(i, uniqueId, type, myName, 
											myAvatarFile, myStartCash, startQuantityPlayers > i, 
											myStayOnTableStatus, 0);
		tmpPlayer->setIsSessionActive(true);
		tmpPlayer->setGuid(myGuid);

		// fill player lists
		seatsList->push_back(tmpPlayer);
		if(startQuantityPlayers > i) {
			activePlayerList->push_back(tmpPlayer);
		}
		(*runningPlayerList) = (*activePlayerList);

	}

	currentBoard->setPlayerLists(seatsList, activePlayerList, runningPlayerList);

	// log game data
	if(myLog) 
		myLog->logNewGameMsg(myGameID, startCash, startSmallBlind, 
							getPlayerByUniqueId(dealerPosition)->getID()+1, seatsList);

	//start timer
	blindsTimer.reset();
	blindsTimer.start();
}

Game::~Game()
{
}

boost::shared_ptr<HandInterface> Game::getCurrentHand()
{
	return currentHand;
}

const boost::shared_ptr<HandInterface> Game::getCurrentHand() const
{
	return currentHand;
}

void Game::initHand()
{

	size_t i;
	PlayerListConstIterator it_c;
	PlayerListIterator it;

	currentHandID++;

	// calculate smallBlind
	raiseBlinds();

	// set player action none
	for(it=seatsList->begin(); it!=seatsList->end(); ++it) {
		(*it)->setAction(PLAYER_ACTION_NONE);
	}

	// set player with empty cash inactive
	it = activePlayerList->begin();
	while( it!=activePlayerList->end() ) {

		if((*it)->getCash() == 0) {
			(*it)->setActiveStatus(false);
			it = activePlayerList->erase(it);
		} else {
			++it;
		}
	}

	runningPlayerList->clear();
	(*runningPlayerList) = (*activePlayerList);

	// create Hand
	currentHand = myFactory->createHand(myFactory, myGui, currentBoard, myLog, seatsList, activePlayerList, runningPlayerList, currentHandID, startQuantityPlayers, dealerPosition, currentSmallBlind, startCash);

	// shifting dealer button -> TODO exception-rule !!!
	bool nextDealerFound = false;
	PlayerListConstIterator dealerPositionIt = currentHand->getSeatIt(dealerPosition);
	if(dealerPositionIt == seatsList->end()) {
		throw Exception(__FILE__, __LINE__, ERR_SEAT_NOT_FOUND);
	}

	for(i=0; i<seatsList->size(); i++) {

		++dealerPositionIt;
		if(dealerPositionIt == seatsList->end()) dealerPositionIt = seatsList->begin();

		it_c = currentHand->getActivePlayerIt( (*dealerPositionIt)->getUniqueID() );
		if(it_c != activePlayerList->end() ) {
			nextDealerFound = true;
			dealerPosition = (*it_c)->getUniqueID();
			break;
		}
	}
	if(!nextDealerFound) {
		throw Exception(__FILE__, __LINE__, ERR_NEXT_DEALER_NOT_FOUND);
	}
}

void Game::startHand()
{
	myGui->nextRoundCleanGui();

	// log new hand
	myGui->logNewGameHandMsg(myGameID, currentHandID);
	myGui->flushLogAtGame(myGameID);

	currentHand->start();
}

boost::shared_ptr<Player> Game::getPlayerByUniqueId(unsigned id)
{
	boost::shared_ptr<Player> tmpPlayer;
	PlayerListIterator i = getSeatsList()->begin();
	PlayerListIterator end = getSeatsList()->end();
	while (i != end) {
		if ((*i)->getUniqueID() == id) {
			tmpPlayer = *i;
			break;
		}
		++i;
	}
	return tmpPlayer;
}

boost::shared_ptr<Player> Game::getPlayerByNumber(int number)
{
	boost::shared_ptr<Player> tmpPlayer;
	PlayerListIterator i = getSeatsList()->begin();
	PlayerListIterator end = getSeatsList()->end();
	while (i != end) {
		if ((*i)->getID() == number) {
			tmpPlayer = *i;
			break;
		}
		++i;
	}
	return tmpPlayer;
}

boost::shared_ptr<Player> Game::getCurrentPlayer()
{
	boost::shared_ptr<Player> tmpPlayer = getPlayerByUniqueId(getCurrentHand()->getCurrentBettingRound()->getCurrentPlayersTurnId());
	if (!tmpPlayer.get())
		throw Exception(__FILE__, __LINE__, ERR_CURRENT_PLAYER_NOT_FOUND);
	return tmpPlayer;
}

boost::shared_ptr<Player> Game::getPlayerByName(const std::string &name)
{
	boost::shared_ptr<Player> tmpPlayer;
	PlayerListIterator i = getSeatsList()->begin();
	PlayerListIterator end = getSeatsList()->end();
	while (i != end) {
		if ((*i)->getName() == name) {
			tmpPlayer = *i;
			break;
		}
		++i;
	}
	return tmpPlayer;
}

void Game::raiseBlinds()
{

	bool raiseBlinds = false;

	if (myGameData.raiseIntervalMode == RAISE_ON_HANDNUMBER) {
		if (lastHandBlindsRaised + myGameData.raiseSmallBlindEveryHandsValue <= currentHandID) {
			raiseBlinds = true;
			lastHandBlindsRaised = currentHandID;
		}
	} else {
		if (lastTimeBlindsRaised + myGameData.raiseSmallBlindEveryMinutesValue <= blindsTimer.elapsed().total_seconds()/60) {
			raiseBlinds = true;
			lastTimeBlindsRaised = blindsTimer.elapsed().total_seconds()/60;
		}
	}
	if (raiseBlinds) {
		// At this point, the blinds must be raised
		// Now we check how the blinds should be raised
		if (myGameData.raiseMode == DOUBLE_BLINDS) {
			currentSmallBlind *= 2;
		} else {
			if(!blindsList.empty()) {
				currentSmallBlind = blindsList.front();
				blindsList.pop_front();
			} else {
				// The position exceeds the list
				if (myGameData.afterManualBlindsMode == AFTERMB_DOUBLE_BLINDS) {
					currentSmallBlind *= 2;
				} else {
					if(myGameData.afterManualBlindsMode == AFTERMB_RAISE_ABOUT) {
						currentSmallBlind += myGameData.afterMBAlwaysRaiseValue;
					}
				}
			}
		}
		currentSmallBlind = min(currentSmallBlind,startQuantityPlayers*startCash/2);
	}
}
