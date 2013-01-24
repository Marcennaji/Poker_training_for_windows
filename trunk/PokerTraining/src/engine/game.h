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

#ifndef GAME_H
#define GAME_H

#include <engine/engine.h>
#include "gamedata.h"

#include <third_party/boost/timers.hpp>

class GuiInterface;
class Log;
class HandInterface;
class BoardInterface;
class EngineFactory;
struct GameData;
struct StartData;


class Game
{

public:
	Game(GuiInterface *gui, boost::shared_ptr<EngineFactory> factory,
		 const PlayerList &playerList, const GameData &gameData,
		 const StartData &startData, int gameId, Log *myLog);

	~Game();

	void initHand();
	void startHand();

	boost::shared_ptr<HandInterface> getCurrentHand();
	const boost::shared_ptr<HandInterface> getCurrentHand() const;

	PlayerList getSeatsList() const {
		return seatsList;
	}
	PlayerList getActivePlayerList() const {
		return activePlayerList;
	}
	PlayerList getRunningPlayerList() const {
		return runningPlayerList;
	}

	void setStartQuantityPlayers(int theValue) {
		startQuantityPlayers = theValue;
	}
	int getStartQuantityPlayers() const {
		return startQuantityPlayers;
	}

	void setStartSmallBlind(int theValue) {
		startSmallBlind = theValue;
	}
	int getStartSmallBlind() const {
		return startSmallBlind;
	}

	void setStartCash(int theValue)	{
		startCash = theValue;
	}
	int getStartCash() const {
		return startCash;
	}

	int getGameID() const	{
		return myGameID;
	}

	void setCurrentSmallBlind(int theValue) {
		currentSmallBlind = theValue;
	}
	int getCurrentSmallBlind() const {
		return currentSmallBlind;
	}

	void setCurrentHandID(int theValue) {
		currentHandID = theValue;
	}
	int getCurrentHandID() const {
		return currentHandID;
	}

	unsigned getDealerPosition() const {
		return dealerPosition;
	}

	void replaceDealer(unsigned oldDealer, unsigned newDealer) {
		if (dealerPosition == oldDealer)
			dealerPosition = newDealer;
	}

	boost::shared_ptr<Player> getPlayerByUniqueId(unsigned id);
	boost::shared_ptr<Player> getPlayerByNumber(int number);
	boost::shared_ptr<Player> getPlayerByName(const std::string &name);
	boost::shared_ptr<Player> getCurrentPlayer();

	void raiseBlinds();

private:
	boost::shared_ptr<EngineFactory> myFactory;

	GuiInterface *myGui;
	Log *myLog;
	boost::shared_ptr<HandInterface> currentHand;
	boost::shared_ptr<BoardInterface> currentBoard;

	PlayerList seatsList;
	PlayerList activePlayerList; // used seats
	PlayerList runningPlayerList; // nonfolded and nonallin active players

	// start variables
	int startQuantityPlayers;
	int startCash;
	int startSmallBlind;
	int myGameID;

	// running variables
	int currentSmallBlind;
	int currentHandID;
	unsigned dealerPosition;
	int lastHandBlindsRaised;
	int lastTimeBlindsRaised;
	const GameData myGameData;
	std::list<int> blindsList;

	//timer
	boost::timers::portable::second_timer blindsTimer;
};

#endif
