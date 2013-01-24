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

#ifndef LOG_H
#define LOG_H

#define SQLLITE_COMPLETE_LOG

#include <string>
#include <boost/filesystem.hpp>

#include "engine.h"
#include "game_defs.h"

struct sqlite3;

class ConfigFile;

class Log
{

public:
	Log(ConfigFile *c);

	~Log();

	void init();
	void logNewGameMsg(int gameID, int startCash, int startSmallBlind, unsigned dealerPosition, PlayerList seatsList);
	void logNewHandMsg(int handID, unsigned dealerPosition, int smallBlind, unsigned smallBlindPosition, int bigBlind, unsigned bigBlindPosition, PlayerList seatsList);
	void logPlayerAction(std::string playerName, PlayerActionLog action, int amount = 0);
	void logPlayerAction(int seat, PlayerActionLog action, int amount = 0);
	PlayerActionLog transformPlayerActionLog(PlayerAction action);
	void logBoardCards(int boardCards[5]);
	void logHoleCardsHandName(PlayerList activePlayerList);
	void logHoleCardsHandName(PlayerList activePlayerList, boost::shared_ptr<Player> player, bool forceExecLog = 0);
	void logHandWinner(PlayerList activePlayerList, int highestCardsValue, std::list<unsigned> winners);
	void logGameWinner(PlayerList activePlayerList);
	void logPlayerSitsOut(PlayerList activePlayerList);
	void logAfterHand();
	void logAfterGame();
	void logPlayersStatistics(PlayerList activePlayerList);
//    void closeLogDbAtExit();
	void InitializePlayersStatistics(const std::string playerName, const int nbPlayers);
	void createDatabase();

	void setCurrentRound(GameState theValue) {
		currentRound = theValue;
	}

	std::string getSqliteLogFileName() {
		return mySqliteLogFileName.string();
	}

private:

	void exec_transaction();

	sqlite3 *mySqliteLogDb;
	boost::filesystem::path mySqliteLogFileName;
	ConfigFile *myConfig;
	int uniqueGameID;
	int currentHandID;
	GameState currentRound;
	std::string sql;
};

#endif // LOG_H
