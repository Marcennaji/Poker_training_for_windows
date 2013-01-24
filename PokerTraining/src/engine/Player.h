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

#ifndef PLAYER_H
#define PLAYER_H

#include <engine/handinterface.h>
#include <engine/cardsvalue.h>

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <map>
#include "engine.h"
#include "game_defs.h"

#include <engine/psim/psim.hpp>
#include <sqlite3.h>

#include "PlayerStatistics.h"

enum PlayerType {
	PLAYER_TYPE_COMPUTER,
	PLAYER_TYPE_HUMAN
};

class ConfigFile;
class HandInterface;

class CurrentHandActions 
{
public:

	CurrentHandActions(){ reset();};
	~CurrentHandActions(){};

	void reset(); // init to zero

	std::vector<PlayerAction> & getPreflopActions();
	std::vector<PlayerAction> & getFlopActions();
	std::vector<PlayerAction> & getTurnActions();
	std::vector<PlayerAction> & getRiverActions();

protected :

	friend class Player;

	std::vector<PlayerAction> m_preflopActions;
	std::vector<PlayerAction> m_flopActions;
	std::vector<PlayerAction> m_turnActions;
	std::vector<PlayerAction> m_riverActions;
};

enum PlayerPosition{
					UNKNOWN=0,
					SB=1,
					BB=2,
					UTG=3,
					UTG_PLUS_ONE=4,
					UTG_PLUS_TWO=5,
					MIDDLE=6,
					MIDDLE_PLUS_ONE=7,
					LATE=8,
					CUTOFF=9,
					BUTTON=10					
					};

const char * TightAgressivePlayerName[];
const char * LargeAgressivePlayerName[];
const char * ManiacPlayerName[];
const char * HumanPlayerName[];

// values are odd %, according to the outs number. Array index is the number of outs
int outsOddsOneCard[];
int outsOddsTwoCard[];


class Player 
{
public:
	Player(ConfigFile*, int id, unsigned uniqueId, PlayerType type, std::string name, 
				std::string avatar, int sC, bool aS, bool sotS, int mB);

	~Player();

	void doPreflopAction();
	void doFlopAction();
	void doTurnAction();
	void doRiverAction();

	int			getID() const;
	unsigned	getUniqueID() const;
	void		setUniqueID(unsigned newId);
	void		setGuid(const std::string &theValue);
	std::string getGuid() const ;
	PlayerType	getType() const;
	void		setName(const std::string& theValue);
	std::string getName() const;
	void		setAvatar(const std::string& theValue);
	std::string getAvatar() const ;
	void		setCash(int theValue);
	int			getCash() const;
	void		setSet(int theValue);
	void		setSetAbsolute(int theValue);
	void		setSetNull();
	int			getSet() const;
	int			getLastRelativeSet() const;

	void setHand(HandInterface *);
	void		setAction(PlayerAction theValue, bool blind = 0);
	PlayerAction getAction() const;

	void		setButton(int theValue);
	int			getButton() const;
	void		setActiveStatus(bool theValue) ;
	bool		getActiveStatus() const ;

	void		setStayOnTableStatus(bool theValue);
	bool		getStayOnTableStatus() const;

	void		setCards(int* theValue);
	void		getCards(int* theValue) const;

	void		setTurn(bool theValue);
	bool		getTurn() const ;

	void		setCardsFlip(bool theValue, int state);
	bool		getCardsFlip() const;

	void		setCardsValueInt(int theValue) ;
	int			getCardsValueInt() const;

	void		setLogHoleCardsDone(bool theValue);

	bool		getLogHoleCardsDone() const;

	void		setBestHandPosition(int* theValue);
	void		getBestHandPosition(int* theValue) const ;

	void		setRoundStartCash(int theValue);
	int			getRoundStartCash() const;

	void		setLastMoneyWon ( int theValue );
	int			getLastMoneyWon() const;

	std::string getCardsValueString();

	void		action();

	PlayerPosition getPosition();
	void		setPosition();
	std::string getPositionLabel(PlayerPosition p);

	bool		getHavePosition(PlayerPosition myPos, PlayerList & runningPlayers);

	int			flopCardsValue(int*);

	void		setIsSessionActive(bool active);
	bool		isSessionActive() const;

	bool		checkIfINeedToShowCards();

	void		markRemoteAction();
	unsigned	getTimeSecSinceLastRemoteAction() const;

	float getM();

	const PlayerStatistics & getStatistics(const int nbPlayers) const;

	const PostFlopState getPostFlopState();
	CurrentHandActions & getCurrentHandActions();

	void updatePreflopStatistics();
	void updateFlopStatistics();
	void updateTurnStatistics();
	void updateRiverStatistics();

	boost::shared_ptr<Player> getPlayerByUniqueId(unsigned id);

	int getPotOdd();

	void DisplayHandState(const PostFlopState* state);

	float getOpponentWinningHandsPercentage(std::string board, std::string range);
	std::vector<std::string> getRangeAtomicValues(std::string range);

protected:

	virtual bool preflopShouldCall() = 0;
	virtual bool flopShouldCall() = 0;
	virtual bool turnShouldCall() = 0;
	virtual bool riverShouldCall() = 0;

	virtual bool preflopShouldRaise() = 0;
	virtual bool flopShouldRaise() = 0;
	virtual bool turnShouldRaise() = 0;
	virtual bool riverShouldRaise() = 0;

	virtual bool flopShouldBet() = 0;
	virtual bool turnShouldBet() = 0;
	virtual bool riverShouldBet() = 0;

	std::string getStringBoard();
	void loadStatistics();
	void resetPlayerStatistics();
	void simulateHand();
	bool isCardsInRange(std::string card1, std::string card2, std::string range);
	std::string getFakeCard(char c);
	void evaluateBetAmount();
	std::map<int, float> evaluateOpponentsStrengths();
	float getMaxOpponentsStrengths();

	void initializeRanges(const int utgHeadsUpRange, const int utgFullTableRange);
	float getPreflopCallingRange();
	float getPreflopRaisingRange();
	int getRange(PlayerPosition p);
	int getBoardCardsHigherThan(std::string card);
	const SimResults getHandSimulation();
	bool isDrawingProbOk();

	// returns a % chance, for a winning draw 
	const int getDrawingProbability();

	const int getImplicitOdd();

	char incrementCardValue(char c);

	// attributes

	// vector index is player position, value is range %
	std::vector<int> UTG_STARTING_RANGE;
	std::vector<int> UTG_PLUS_ONE_STARTING_RANGE;
	std::vector<int> UTG_PLUS_TWO_STARTING_RANGE;
	std::vector<int> MIDDLE_STARTING_RANGE;
	std::vector<int> MIDDLE_PLUS_ONE_STARTING_RANGE;
	std::vector<int> LATE_STARTING_RANGE;
	std::vector<int> CUTOFF_STARTING_RANGE;
	std::vector<int> BUTTON_STARTING_RANGE;
	std::vector<int> SB_STARTING_RANGE;
	std::vector<int> BB_STARTING_RANGE;

	ConfigFile *myConfig;
	HandInterface *currentHand;

	PostFlopState myFlopState;
	PostFlopState myTurnState;
	PostFlopState myRiverState;

	SimResults myFlopHandSimulation;
	SimResults myTurnHandSimulation;
	SimResults myRiverHandSimulation;

	CurrentHandActions myCurrentHandActions;

	//const
	int myID;
	unsigned myUniqueID;
	std::string myGuid;
	PlayerType myType;
	std::string myName;
	std::string myAvatar;

	// vars
	PlayerPosition myPosition;
	PlayerStatistics myStatistics[MAX_NUMBER_OF_PLAYERS+1];
	int myCardsValueInt;
	int myBestHandPosition[5];
	bool logHoleCardsDone;

	// current hand playing
	bool myShouldBet;
	bool myShouldRaise;
	bool myShouldCall;

	int myCards[2];
	std::string myCard1;
	std::string myCard2;
	int myCash;
	int mySet;
	int myRaiseAmount;
	int myBetAmount;
	int myLastRelativeSet;
	PlayerAction myAction;
	int myButton; // 0 = none, 1 = dealer, 2 =small, 3 = big
	bool myActiveStatus; // 0 = inactive, 1 = active
	bool myStayOnTableStatus; // 0 = left, 1 = stay
	bool myTurn; // 0 = no, 1 = yes
	bool myCardsFlip; // 0 = cards are not fliped, 1 = cards are already flipped,
	int myRoundStartCash;
	int lastMoneyWon;

	bool m_isSessionActive;

};

#endif
