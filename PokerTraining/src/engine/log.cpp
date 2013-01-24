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

#include "log.h"

#include "configfile.h"
#include "cardsvalue.h"

#include <sqlite3.h>
#include <dirent.h>
#include <boost/lexical_cast.hpp>
#include "Player.h"

#include "game_defs.h"

using namespace std;

Log::Log(ConfigFile *c) : mySqliteLogDb(0), mySqliteLogFileName(""), myConfig(c), uniqueGameID(0), currentHandID(0), 
						currentRound(GAME_STATE_PREFLOP), sql("")
{
}

Log::~Log()
{
	if(SQLITE_LOG) {
		sqlite3_close(mySqliteLogDb);
	}
}

void
Log::init()
{

	if(SQLITE_LOG) {

		// logging activated
		if(myConfig->readConfigInt("LogOnOff")) {

			DIR *logDir;
			logDir = opendir((myConfig->readConfigString("LogDir")).c_str());
			bool dirExists = logDir != NULL;
			closedir(logDir);

			// check if logging path exist
			if(myConfig->readConfigString("LogDir") != "" && dirExists) {

				mySqliteLogFileName.clear();
				mySqliteLogFileName /= myConfig->readConfigString("LogDir");
				mySqliteLogFileName /= string("pokerTraining-log.pdb");

				bool databaseExists = false;
				if (FILE * file = fopen(mySqliteLogFileName.string().c_str(), "r"))  {
					fclose(file);
					databaseExists = true;
				}else{
#ifdef LOG_POKER_EXEC
					cout << "warning : database does not exist, will be created" << endl;
#endif
				}

				// open sqlite-db
				sqlite3_open(mySqliteLogFileName.string().c_str(), &mySqliteLogDb);

				if( mySqliteLogDb != 0 ) {
					
					if (!  databaseExists)
						createDatabase();
				}
			}
		}
	}
}

void Log::createDatabase(){

	int i;
	// create session table
	sql += "CREATE TABLE IF NOT EXISTS Session (";
	sql += "PokerTraining_Version TEXT NOT NULL";
	sql += ",LogVersion INTEGER NOT NULL) ;";

	sql += "INSERT OR IGNORE INTO Session (";
	sql += "PokerTraining_Version";
	sql += ",LogVersion";
	sql += ") VALUES (";
	sql += "\"" + boost::lexical_cast<string>(POKERTRAINING_BETA_RELEASE_STRING) + "\",";
	sql += boost::lexical_cast<string>(SQLITE_LOG_VERSION) + ");";

	// create game table
	sql += "CREATE TABLE IF NOT EXISTS Game (";
	sql += "UniqueGameID INTEGER PRIMARY KEY";
	sql += ",GameID INTEGER NOT NULL";
	sql += ",Startmoney INTEGER NOT NULL";
	sql += ",StartSb INTEGER NOT NULL";
	sql += ",DealerPos INTEGER NOT NULL";
	sql += ",Winner_Seat INTEGER";
	sql += ") ;";

	// create player table
	sql += "CREATE TABLE  IF NOT EXISTS Player (";
	sql += "UniqueGameID INTEGER NOT NULL";
	sql += ",Seat INTEGER NOT NULL";
	sql += ",Player TEXT NOT NULL";
	sql += ",PRIMARY KEY(UniqueGameID,Seat));";

	// create hand table
	sql += "CREATE TABLE IF NOT EXISTS Hand (";
	sql += "HandID INTEGER NOT NULL";
	sql += ",UniqueGameID INTEGER NOT NULL";
	sql += ",Dealer_Seat INTEGER";
	sql += ",Sb_Amount INTEGER NOT NULL";
	sql += ",Sb_Seat INTEGER NOT NULL";
	sql += ",Bb_Amount INTEGER NOT NULL";
	sql += ",Bb_Seat INTEGER NOT NULL";
	for(i=1; i<=MAX_NUMBER_OF_PLAYERS; i++) {
		sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Cash INTEGER";
		sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Card_1 INTEGER";
		sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Card_2 INTEGER";
		sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Hand_text TEXT";
		sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Hand_int INTEGER";
	}
	for(i=1; i<=5; i++) {
		sql += ",BoardCard_" + boost::lexical_cast<std::string>(i) + " INTEGER";
	}
	sql += ",PRIMARY KEY(HandID,UniqueGameID));";

	// create action table
	sql += "CREATE TABLE IF NOT EXISTS Action (";
	sql += "ActionID INTEGER PRIMARY KEY AUTOINCREMENT";
	sql += ",HandID INTEGER NOT NULL";
	sql += ",UniqueGameID INTEGER NOT NULL";
	sql += ",BeRo INTEGER NOT NULL";
	sql += ",Player INTEGER NOT NULL";
	sql += ",Action TEXT NOT NULL";
	sql += ",Amount INTEGER";
	sql += ");";

	// create stats table
	sql += "CREATE TABLE  IF NOT EXISTS PlayersStatistics (";
	sql += "player_name VARCHAR NOT NULL";
	sql += ", nb_players SMALLINT NOT NULL";
	sql += ", pf_hands LARGEINT "; 
	// preflop stats :
	sql += ", pf_folds LARGEINT ";
	sql += ", pf_limps LARGEINT ";
	sql += ", pf_checks LARGEINT ";
	sql += ", pf_calls LARGEINT ";
	sql += ", pf_raises LARGEINT ";
	sql += ", pf_threeBets LARGEINT ";
	sql += ", pf_fourBets LARGEINT ";
	// flop stats :
	sql += ", f_hands LARGEINT ";
	sql += ", f_folds LARGEINT ";
	sql += ", f_checks LARGEINT ";
	sql += ", f_bets LARGEINT ";
	sql += ", f_calls LARGEINT ";
	sql += ", f_raises LARGEINT ";
	sql += ", f_threeBets LARGEINT ";
	sql += ", f_fourBets LARGEINT ";
	sql += ", f_continuationBets LARGEINT ";
	sql += ", f_continuationBetsOpportunities LARGEINT ";
	// turn stats :
	sql += ", t_hands LARGEINT ";
	sql += ", t_folds LARGEINT ";
	sql += ", t_checks LARGEINT ";
	sql += ", t_calls LARGEINT ";
	sql += ", t_bets LARGEINT ";
	sql += ", t_raises LARGEINT ";
	sql += ", t_threeBets LARGEINT ";
	sql += ", t_fourBets LARGEINT ";
	// river stats :
	sql += ", r_hands LARGEINT ";
	sql += ", r_folds LARGEINT ";
	sql += ", r_bets LARGEINT ";
	sql += ", r_checks LARGEINT ";
	sql += ", r_calls LARGEINT ";
	sql += ", r_raises LARGEINT ";
	sql += ", r_threeBets LARGEINT ";
	sql += ", r_fourBets LARGEINT ";

	sql += ", PRIMARY KEY(player_name, nb_players));";

	exec_transaction();

	for(int i=0; i < MAX_NUMBER_OF_PLAYERS; i++) {

		for (int j = 2; j <= MAX_NUMBER_OF_PLAYERS; j++){ 
			InitializePlayersStatistics(TightAgressivePlayerName[i], j);
			InitializePlayersStatistics(LargeAgressivePlayerName[i], j);
			InitializePlayersStatistics(ManiacPlayerName[i], j);
		}
	}
	for (int j = 2; j <= MAX_NUMBER_OF_PLAYERS; j++){ 
		InitializePlayersStatistics(HumanPlayerName[0], j);
	}
}

void Log::InitializePlayersStatistics(const string playerName, const int nbPlayers){

	sql += "INSERT OR IGNORE INTO PlayersStatistics (";
	sql += "player_name,nb_players";
	sql += ",pf_hands,pf_checks,pf_calls,pf_raises,pf_threeBets,pf_fourBets,pf_folds,pf_limps";
	sql += ",f_hands,f_checks,f_bets,f_calls,f_raises,f_threeBets,f_fourBets,f_folds,f_continuationBets,f_continuationBetsOpportunities" ;
	sql += ",t_hands,t_checks,t_bets,t_calls,t_raises,t_threeBets,t_fourBets,t_folds";
	sql += ",r_hands,r_checks,r_bets,r_calls,r_raises,r_threeBets,r_fourBets,r_folds";
	sql += ") VALUES (";
	sql += "'" ;
	sql += playerName;
	sql += "',";
	sql += boost::lexical_cast<string>(nbPlayers);
	sql += ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);";

	exec_transaction();
}

void
Log::logNewGameMsg(int gameID, int startCash, int startSmallBlind, unsigned dealerPosition, PlayerList seatsList)
{
	uniqueGameID++;

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			PlayerListConstIterator it_c;

			if( mySqliteLogDb != 0 ) {
				// sqlite-db is open
				int i;

				sql += "INSERT OR IGNORE INTO Game (";
				sql += "UniqueGameID";
				sql += ",GameID";
				sql += ",Startmoney";
				sql += ",StartSb";
				sql += ",DealerPos";
				sql += ") VALUES (";
				sql += boost::lexical_cast<string>(uniqueGameID);
				sql += "," + boost::lexical_cast<string>(gameID);
				sql += "," + boost::lexical_cast<string>(startCash);
				sql += "," + boost::lexical_cast<string>(startSmallBlind);
				sql += "," + boost::lexical_cast<string>(dealerPosition);
				sql += ");";

				i = 1;
				for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
					if((*it_c)->getActiveStatus()) {
						sql += "INSERT OR IGNORE INTO Player (";
						sql += "UniqueGameID";
						sql += ",Seat";
						sql += ",Player";
						sql += ") VALUES (";
						sql += boost::lexical_cast<string>(uniqueGameID);
						sql += "," + boost::lexical_cast<string>(i);
						sql += ",\"" + (*it_c)->getName() +"\"";
						sql += ");";
					}
					i++;
				}

				exec_transaction();
			}
		}
	}
}

void
Log::logNewHandMsg(int handID, unsigned dealerPosition, int smallBlind, unsigned smallBlindPosition, int bigBlind, unsigned bigBlindPosition, PlayerList seatsList)
{
	if (! SQLITE_LOG_ALL)
		return;

	currentRound = GAME_STATE_PREFLOP;
	currentHandID = handID;
	PlayerListConstIterator it_c;
	for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
		(*it_c)->setLogHoleCardsDone(false);
	}

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			if( mySqliteLogDb != 0 ) {
				// sqlite-db is open
				int i;

				sql += "INSERT OR IGNORE INTO Hand (";
				sql += "HandID";
				sql += ",UniqueGameID";
				sql += ",Dealer_Seat";
				sql += ",Sb_Amount";
				sql += ",Sb_Seat";
				sql += ",Bb_Amount";
				sql += ",Bb_Seat";
				for(i=1; i<=MAX_NUMBER_OF_PLAYERS; i++) {
					sql += ",Seat_" + boost::lexical_cast<std::string>(i) + "_Cash";
				}
				sql += ") VALUES (";
				sql += boost::lexical_cast<string>(currentHandID);
				sql += "," + boost::lexical_cast<string>(uniqueGameID);
				sql += "," + boost::lexical_cast<string>(dealerPosition);
				sql += "," + boost::lexical_cast<string>(smallBlind);
				sql += "," + boost::lexical_cast<string>(smallBlindPosition);
				sql += "," + boost::lexical_cast<string>(bigBlind);
				sql += "," + boost::lexical_cast<string>(bigBlindPosition);
				for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
					if((*it_c)->getActiveStatus()) {
						sql += "," + boost::lexical_cast<string>((*it_c)->getRoundStartCash());
					} else {
						sql += ",NULL";
					}
				}
				sql += ");";
				if(myConfig->readConfigInt("LogInterval") == 0) {
					exec_transaction();
				}

				// !! TODO !! Hack, weil Button-Regel noch falsch und dealerPosition noch teilweise falsche ID enthÃ¤lt (HeadsUp: dealerPosition=bigBlindPosition <-- falsch)
				bool dealerButtonOnTable = false;
				int countActivePlayer = 0;
				for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
					if((*it_c)->getActiveStatus()) {
						countActivePlayer++;
						if((*it_c)->getButton()==BUTTON_DEALER && (*it_c)->getActiveStatus()) {
							dealerButtonOnTable = true;
						}
					}
				}
				if(countActivePlayer==2) {
					logPlayerAction(smallBlindPosition,LOG_ACTION_DEALER);
				} else {
					if(dealerButtonOnTable) {
						logPlayerAction(dealerPosition,LOG_ACTION_DEALER);
					}
				}

				// log blinds
				for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
					if((*it_c)->getButton() == BUTTON_SMALL_BLIND && (*it_c)->getSet()>0) {
						logPlayerAction(smallBlindPosition,LOG_ACTION_SMALL_BLIND,(*it_c)->getSet());
					}
				}
				for(it_c = seatsList->begin(); it_c!=seatsList->end(); ++it_c) {
					if((*it_c)->getButton() == BUTTON_BIG_BLIND && (*it_c)->getSet()>0) {
						logPlayerAction(bigBlindPosition,LOG_ACTION_BIG_BLIND,(*it_c)->getSet());
					}
				}

				// (*it_c)->getSet() ist ein Hack, da es im Internetspiel vorkam, dass ein Spieler zweimal geloggt wurde mit Blind - einmal jedoch mit $0

				// !! TODO !! Hack

			}
		}
	}
}

void
Log::logPlayerAction(string playerName, PlayerActionLog action, int amount)
{
	if (! SQLITE_LOG_ALL)
		return;

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			if( mySqliteLogDb != 0 ) {
				// sqlite-db is open

				char **result_Player=0;
				int nRow_Player=0;
				int nCol_Player=0;
				char *errmsg = 0;

				// read seat
				string sql_select = "SELECT Seat FROM Player WHERE UniqueGameID=" + boost::lexical_cast<std::string>(uniqueGameID);
				sql_select += " AND ";
				sql_select += "Player=\"" + playerName +"\"";
				if(sqlite3_get_table(mySqliteLogDb,sql_select.c_str(),&result_Player,&nRow_Player,&nCol_Player,&errmsg) != SQLITE_OK) {
					cout << "Error in statement: " << sql_select.c_str() << "[" << errmsg << "]." << endl;
				} else {
					if(nRow_Player == 1) {
						logPlayerAction(boost::lexical_cast<int>(result_Player[1]), action, amount);
					} else {
						cout << "Implausible information about player " << playerName << " in log-db!" << endl;
					}
				}

				sqlite3_free_table(result_Player);
			}
		}
	}
}

void
Log::logPlayerAction(int seat, PlayerActionLog action, int amount)
{
	if (! SQLITE_LOG_ALL)
		return;

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			if( mySqliteLogDb != 0 ) {
				// sqlite-db is open

				if(action!=LOG_ACTION_NONE) {
					sql += "INSERT OR IGNORE INTO Action (";
					sql += "HandID";
					sql += ",UniqueGameID";
					sql += ",BeRo";
					sql += ",Player";
					sql += ",Action";
					sql += ",Amount";
					sql += ") VALUES (";
					sql += boost::lexical_cast<string>(currentHandID);
					sql += "," + boost::lexical_cast<string>(uniqueGameID);
					sql += "," + boost::lexical_cast<string>(currentRound);;
					sql += "," + boost::lexical_cast<string>(seat);
					switch(action) {
					case LOG_ACTION_DEALER:
						sql += ",'starts as dealer'";
						sql += ",NULL";
						break;
					case LOG_ACTION_SMALL_BLIND:
						sql += ",'posts small blind'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_BIG_BLIND:
						sql += ",'posts big blind'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_FOLD:
						sql += ",'folds'";
						sql += ",NULL";
						break;
					case LOG_ACTION_CHECK:
						sql += ",'checks'";
						sql += ",NULL";
						break;
					case LOG_ACTION_CALL:
						sql += ",'calls'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_BET:
						sql += ",'bets'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_ALL_IN:
						sql += ",'is all in with'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_SHOW:
						sql += ",'shows'";
						sql += ",NULL";
						break;
					case LOG_ACTION_HAS:
						sql += ",'has'";
						sql += ",NULL";
						break;
					case LOG_ACTION_WIN:
						sql += ",'wins'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_WIN_SIDE_POT:
						sql += ",'wins (side pot)'";
						sql += "," + boost::lexical_cast<string>(amount);
						break;
					case LOG_ACTION_SIT_OUT:
						sql += ",'sits out'";
						sql += ",NULL";
						break;
					case LOG_ACTION_WIN_GAME:
						sql += ",'wins game'";
						sql += ",NULL";
						break;
					default:
						return;
					}
					sql += ");";
					if(myConfig->readConfigInt("LogInterval") == 0) {
						exec_transaction();
					}
				}
			}
		}
	}
}

PlayerActionLog
Log::transformPlayerActionLog(PlayerAction action)
{
	switch(action) {
	case PLAYER_ACTION_FOLD:
		return LOG_ACTION_FOLD;
		break;
	case PLAYER_ACTION_CHECK:
		return LOG_ACTION_CHECK;
		break;
	case PLAYER_ACTION_CALL:
		return LOG_ACTION_CALL;
		break;
	case PLAYER_ACTION_BET:
	case PLAYER_ACTION_RAISE:
		return LOG_ACTION_BET;
		break;
	case PLAYER_ACTION_ALLIN:
		return LOG_ACTION_ALL_IN;
		break;
	default:
		return LOG_ACTION_NONE;
	}
}

void
Log::logBoardCards(int boardCards[5])
{
	if (! SQLITE_LOG_ALL)
		return;

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			if( mySqliteLogDb != 0 ) {
				// sqlite-db is open

				switch(currentRound) {
				case GAME_STATE_FLOP: {
					sql += "UPDATE Hand SET ";
					sql += "BoardCard_1=" + boost::lexical_cast<string>(boardCards[0]) + ",";
					sql += "BoardCard_2=" + boost::lexical_cast<string>(boardCards[1]) + ",";
					sql += "BoardCard_3=" + boost::lexical_cast<string>(boardCards[2]);
				}
				break;
				case GAME_STATE_TURN: {
					sql += "UPDATE Hand SET ";
					sql += "BoardCard_4=" + boost::lexical_cast<string>(boardCards[3]);
				}
				break;
				case GAME_STATE_RIVER: {
					sql += "UPDATE Hand SET ";
					sql += "BoardCard_5=" + boost::lexical_cast<string>(boardCards[4]);
				}
				break;
				default:
					return;
				}
				sql += " WHERE ";
				sql += "UniqueGameID=" + boost::lexical_cast<string>(uniqueGameID) + " AND ";
				sql += "HandID=" + boost::lexical_cast<string>(currentHandID);
				sql += ";";
				if(myConfig->readConfigInt("LogInterval") == 0) {
					exec_transaction();
				}
			}
		}
	}
}

void
Log::logHoleCardsHandName(PlayerList activePlayerList)
{
	if (! SQLITE_LOG_ALL)
		return;

	PlayerListConstIterator it_c;

	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

//		if( (*it_c)->getAction() != PLAYER_ACTION_FOLD && ( ((*it_c)->checkIfINeedToShowCards() && currentRound==GAME_STATE_POST_RIVER ) || ( currentRound!=GAME_STATE_POST_RIVER && !(*it_c)->getLogHoleCardsDone()) ) ) {

			logHoleCardsHandName(activePlayerList, *it_c);

//		}
	}
}

void
Log::logHoleCardsHandName(PlayerList activePlayerList, boost::shared_ptr<Player> player, bool forceExecLog)
{
	if (! SQLITE_LOG_ALL)
		return;

	if(SQLITE_LOG) {

		if(myConfig->readConfigInt("LogOnOff")) {
			//if write logfiles is enabled

			if( mySqliteLogDb != 0) {

				int myCards[2];
				player->getCards(myCards);
				sql += "UPDATE Hand SET ";
				if(currentRound==GAME_STATE_POST_RIVER && player->getCardsValueInt()>0) {
					sql += "Seat_" + boost::lexical_cast<string>(player->getID()+1) + "_Hand_text=\"" + CardsValue::determineHandName(player->getCardsValueInt(),activePlayerList) + "\"";
					sql += ",Seat_" + boost::lexical_cast<string>(player->getID()+1) + "_Hand_int=" + boost::lexical_cast<string>(player->getCardsValueInt());
				}
				if(currentRound==GAME_STATE_POST_RIVER && player->getCardsValueInt()>0 && !player->getLogHoleCardsDone()) {
					sql+= ",";
				}
				if(!player->getLogHoleCardsDone()) {
					sql += "Seat_" + boost::lexical_cast<string>(player->getID()+1) + "_Card_1=" + boost::lexical_cast<string>(myCards[0]);
					sql += ",Seat_" + boost::lexical_cast<string>(player->getID()+1) + "_Card_2=" + boost::lexical_cast<string>(myCards[1]);
				}
				sql += " WHERE ";
				sql += "UniqueGameID=" + boost::lexical_cast<string>(uniqueGameID) + " AND ";
				sql += "HandID=" + boost::lexical_cast<string>(currentHandID);
				sql += ";";
				if(myConfig->readConfigInt("LogInterval") == 0 || forceExecLog) {
					exec_transaction();
				}

				if(!player->getLogHoleCardsDone()) {
					logPlayerAction(player->getName(),LOG_ACTION_SHOW);
				} else {
					logPlayerAction(player->getName(),LOG_ACTION_HAS);
				}

				player->setLogHoleCardsDone(true);

			}
		}
	}
}

void
Log::logHandWinner(PlayerList activePlayerList, int highestCardsValue, std::list<unsigned> winners)
{

	if (! SQLITE_LOG_ALL)
		return;

	PlayerListConstIterator it_c;
	list<unsigned>::iterator it_int;

	// log winner
	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() == highestCardsValue) {
			logPlayerAction((*it_c)->getName(),LOG_ACTION_WIN,(*it_c)->getLastMoneyWon());
		}
	}

	// log side pot winner
	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if((*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() != highestCardsValue ) {

			for(it_int = winners.begin(); it_int != winners.end(); ++it_int) {
				if((*it_int) == (*it_c)->getUniqueID()) {
					logPlayerAction((*it_c)->getName(),LOG_ACTION_WIN_SIDE_POT,(*it_c)->getLastMoneyWon());
				}
			}
		}
	}

}

void
Log::logGameWinner(PlayerList activePlayerList)
{
	if (! SQLITE_LOG_ALL)
		return;

	int playersPositiveCashCounter = 0;
	PlayerListConstIterator it_c;
	for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
		if ((*it_c)->getCash() > 0) playersPositiveCashCounter++;
	}
	if (playersPositiveCashCounter==1) {
		for (it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {
			if ((*it_c)->getCash() > 0) {
				logPlayerAction((*it_c)->getName(),LOG_ACTION_WIN_GAME);
			}
		}
		// for log after every game
		logAfterGame();
	}
}

void
Log::logPlayerSitsOut(PlayerList activePlayerList)
{
	if (! SQLITE_LOG_ALL)
		return;

	PlayerListConstIterator it_c;

	for(it_c=activePlayerList->begin(); it_c!=activePlayerList->end(); ++it_c) {

		if((*it_c)->getCash() == 0) {
			logPlayerAction((*it_c)->getName(), LOG_ACTION_SIT_OUT);
		}
	}

}

void
Log::logAfterHand()
{
	if(myConfig->readConfigInt("LogInterval") == 1) {
		exec_transaction();
	}
}

void
Log::logAfterGame()
{
	if(myConfig->readConfigInt("LogInterval") == 2) {
		exec_transaction();
	}
}

void
Log::exec_transaction()
{
	char *errmsg = NULL;

	string sql_transaction = "BEGIN;" + sql + "COMMIT;";
	sql = ""; 
	//cout << endl << "SQL : " << sql_transaction << endl << endl;
	if(sqlite3_exec(mySqliteLogDb, sql_transaction.c_str(), 0, 0, &errmsg) != SQLITE_OK) {
		cout << "Error in statement: " << sql_transaction.c_str() << "[" << errmsg << "]." << endl;
		sqlite3_free(errmsg);
		errmsg = NULL;
	}
}

void
Log::logPlayersStatistics(PlayerList activePlayerList)
{

	PlayerListConstIterator it_c;

	const int i = activePlayerList->size();

	for(it_c=activePlayerList->begin(); it_c != activePlayerList->end(); ++it_c) {

		if ((*it_c)->getStatistics(i).getPreflopStatistics().m_hands == 0){
			return;
		}

		sql =  "UPDATE PlayersStatistics SET ";

		sql += "pf_hands = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_hands);
		sql += ",pf_checks = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_checks);
		sql += ",pf_calls = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_calls);
		sql += ",pf_raises = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_raises);
		sql += ",pf_threeBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_threeBets);
		sql += ",pf_fourBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_fourBets);
		sql += ",pf_folds = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_folds);
		sql += ",pf_limps = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getPreflopStatistics().m_limps);

		sql += ",f_hands = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_hands);
		sql += ",f_bets = "			+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_bets);
		sql += ",f_checks = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_checks);
		sql += ",f_calls = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_calls);
		sql += ",f_raises = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_raises);
		sql += ",f_threeBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_threeBets);
		sql += ",f_fourBets = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_fourBets);
		sql += ",f_folds = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_folds);
		sql += ",f_continuationBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_continuationBets);
		sql += ",f_continuationBetsOpportunities = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getFlopStatistics().m_continuationBetsOpportunities);

		sql += ",t_hands = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_hands);
		sql += ",t_checks = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_checks);
		sql += ",t_bets = "			+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_bets);
		sql += ",t_calls = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_calls);
		sql += ",t_raises = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_raises);
		sql += ",t_threeBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_threeBets);
		sql += ",t_fourBets = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_fourBets);
		sql += ",t_folds = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getTurnStatistics().m_folds);

		sql += ",r_hands = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_hands);
		sql += ",r_checks = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_checks);
		sql += ",r_bets = "			+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_bets);
		sql += ",r_calls = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_calls);
		sql += ",r_raises = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_raises);
		sql += ",r_threeBets = "	+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_threeBets);
		sql += ",r_fourBets = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_fourBets);
		sql += ",r_folds = "		+ boost::lexical_cast<string>((*it_c)->getStatistics(i).getRiverStatistics().m_folds);

		sql += " WHERE player_name = '" + (*it_c)->getName() + "' AND nb_players = " + boost::lexical_cast<string>(i) + ";";

		exec_transaction();
	}

}

//void
//Log::closeLogDbAtExit()
//{
//    if(SQLITE_LOG) {
//        // close sqlite-db
//        sqlite3_close(mySqliteLogDb);
//        mySqliteLogDb = NULL;
//    }
//}
