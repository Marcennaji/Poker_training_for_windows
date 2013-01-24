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
#include <boost/asio.hpp>
#include "session.h"
#include <engine/game.h>
#include <engine/log.h>
#include <qt/guiinterface.h>
#include <configfile.h>
#include <qt/qttoolsinterface.h>
#include <engine/enginefactory.h>

#include <sstream>

#define NET_CLIENT_TERMINATE_TIMEOUT_MSEC	2000
#define NET_IRC_TERMINATE_TIMEOUT_MSEC		2000

#define NET_DEFAULT_GAME					"default"


using namespace std;

Session::Session(GuiInterface *g, ConfigFile *c, Log *l)
	: currentGameNum(0), myGui(g), myConfig(c), myLog(l)
{
	myQtToolsInterface = CreateQtToolsWrapper();
}


Session::~Session()
{
	delete myQtToolsInterface;
	myQtToolsInterface = 0;
	delete myLog;
	myLog = 0;
}

bool Session::init()
{
	return true;
}

void Session::startGame(const GameData &gameData, const StartData &startData)
{

	currentGame.reset();
	currentGameNum++;

	myGui->initGui(gameData.guiSpeed);

	boost::shared_ptr<EngineFactory> factory(new EngineFactory(myConfig)); // Engine erstellen


	PlayerList playerList;
	playerList.reset(new std::list<boost::shared_ptr<Player> >);

	for(int i = 0; i < startData.numberOfPlayers; i++) {

		//Namen und Avatarpfad abfragen
		ostringstream myName;
		if (i==0) {
			myName << "MyName";
		} else {
			myName << "Opponent" << i << "Name";
		}
		ostringstream myAvatar;
		if (i==0) {
			myAvatar << "MyAvatar";
		} else {
			myAvatar << "Opponent" << i << "Avatar";
		}

		//PlayerData erzeugen
		// UniqueId = PlayerNumber for  games.

		boost::shared_ptr<Player> player = 
					factory->createPlayer(i, i, 
											i == 0 ? PLAYER_TYPE_HUMAN : PLAYER_TYPE_COMPUTER, myName.str(), 
											myAvatar.str(), gameData.startMoney, startData.numberOfPlayers > i, 
											i == 0 ? true : false, 0);
		player->setIsSessionActive(true);

		player->setName(myConfig->readConfigString(myName.str()));
		//player->SetAvatarFile(myConfig->readConfigString(myAvatar.str()));

		playerList->push_back(player);
	}

	currentGame.reset(new Game(myGui, factory, playerList, gameData, startData, currentGameNum, myLog));

	currentGame->initHand();
	currentGame->startHand();

}

boost::shared_ptr<Game> Session::getCurrentGame()
{
	return currentGame;
}

GuiInterface *Session::getGui()
{
	return myGui;
}

