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
#include <engine/LargeAgressivePlayer.h>

#include <engine/handinterface.h>
#include <engine/tools.h>
#include <engine/cardsvalue.h>
#include <configfile.h>
#include <loghelper.h>
#include <engine/psim/simulate.hpp>
#include "Exception.h"
#include "engine_msg.h"
#include "ranges.h"

#include <qt/guiwrapper.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

LargeAgressivePlayer::LargeAgressivePlayer(ConfigFile *c, int id, unsigned uniqueId, PlayerType type, std::string name, 
						std::string avatar, int sC, bool aS, bool sotS, int mB):
	Player(c, id, uniqueId, type, name, avatar, sC, aS, sotS, mB){
	
	// initialize utg starting range, in a full table 
	int utgFullTableRange = 0;
	Tools::GetRand(12, 15, 1, &utgFullTableRange);
	initializeRanges(50, utgFullTableRange);	
}

	
LargeAgressivePlayer::~LargeAgressivePlayer(){}


bool LargeAgressivePlayer::preflopShouldCall(){

	const int nbRaises = currentHand->getPreflopRaisesNumber();
	const int nbCalls = currentHand->getPreflopCallsNumber();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

	float callingRange = getPreflopCallingRange();

	if (callingRange == -1)
		return false;// never call : raise or fold

	string stringCallingRange;

	const char * * RANGES_STRING;

	if (nbPlayers == 2)
		RANGES_STRING = TOP_RANGE_2_PLAYERS;
	else if (nbPlayers == 3)
		RANGES_STRING = TOP_RANGE_3_PLAYERS;
	else if (nbPlayers == 4)
		RANGES_STRING = TOP_RANGE_4_PLAYERS;
	else RANGES_STRING = TOP_RANGE_MORE_4_PLAYERS;

	stringCallingRange = RANGES_STRING[(int)callingRange];

	if (nbRaises < 3)
		stringCallingRange += HIGH_PAIRS;

	if (nbRaises < 2){

		stringCallingRange += HIGH_SUITED_CONNECTORS;
		stringCallingRange += HIGH_SUITED_ACES;
		stringCallingRange += PAIRS;

		if (currentHand->getRunningPlayerList()->size() > 2 && nbRaises + nbCalls > 1 && myPosition >= LATE){
			stringCallingRange += SUITED_CONNECTORS;
			stringCallingRange += SUITED_ONE_GAPED;
			stringCallingRange += SUITED_TWO_GAPED;
		}
	}

#ifdef LOG_POKER_EXEC
	cout << "\t\tcalling range : " << stringCallingRange << endl;
#endif

	return isCardsInRange(myCard1, myCard2, stringCallingRange);

}

bool LargeAgressivePlayer::preflopShouldRaise(){

	const int nbRaises = currentHand->getPreflopRaisesNumber();
	const int nbCalls = currentHand->getPreflopCallsNumber();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 

	float raisingRange = getPreflopRaisingRange();

	string stringRaisingRange;

	const char * * RANGES_STRING;

	if (nbPlayers == 2)
		RANGES_STRING = TOP_RANGE_2_PLAYERS;
	else if (nbPlayers == 3)
		RANGES_STRING = TOP_RANGE_3_PLAYERS;
	else if (nbPlayers == 4)
		RANGES_STRING = TOP_RANGE_4_PLAYERS;
	else RANGES_STRING = TOP_RANGE_MORE_4_PLAYERS;

	stringRaisingRange = RANGES_STRING[(int)raisingRange];

	int rand = 0;
	Tools::GetRand(1, 6, 1, &rand);
	if (rand == 1 && nbRaises < 2){
		stringRaisingRange += HIGH_SUITED_CONNECTORS;
		stringRaisingRange += HIGH_SUITED_ACES;
		stringRaisingRange += PAIRS;
	}

#ifdef LOG_POKER_EXEC
	cout << "\t\traising range : " << stringRaisingRange << endl;
#endif

	if (! isCardsInRange(myCard1, myCard2, stringRaisingRange))
		return false;

	// determine raise amount
	if (nbRaises == 0){ // first to raise

		myRaiseAmount = (getM() > 6 ? 5 : 3) * currentHand->getSmallBlind();

		if (currentHand->getPreflopCallsNumber() > 0) // increase raise amount if there are limpers
			myRaiseAmount += (currentHand->getPreflopCallsNumber() * (getM() > 6 ? 3 : 2) * currentHand->getSmallBlind());

	}else // not first to raise, I will 3bet or 4bet
		myRaiseAmount = currentHand->getCurrentBettingRound()->getHighestSet() * 3;

	// if i would be commited in the pot, just go allin preflop
	if (myRaiseAmount > (myCash * 0.5))
		myRaiseAmount = myCash;

	return true;
}


bool LargeAgressivePlayer::flopShouldBet(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	const int lastRaiserID = currentHand->getPreflopLastRaiserID();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());

	assert(nbPlayers >= 2);

	const int nbPreflopRaises = currentHand->getPreflopRaisesNumber();
	const int nbFlopRaises = currentHand->getFlopBetsOrRaisesNumber();

	if (nbFlopRaises > 0)
		return false;

	if (getDrawingProbability() > 15 && ! bHavePosition){
		int rand = 0;
		Tools::GetRand(1, 2, 1, &rand);
		if (rand == 1){
			myBetAmount = pot * 0.8;
			return true;
		}
	}

	// if pretty good hand
	if (myFlopHandSimulation.winRanged > 0.6){

		// always bet if my hand will lose a lot of its value on next betting rounds
		if (myFlopHandSimulation.winRanged - myFlopHandSimulation.winSd > 0.15){
			myBetAmount = pot;
			return true;
		}

		int rand = 0;
		Tools::GetRand(1, 6, 1, &rand);
		if (rand == 1 && ! bHavePosition)
			return false;// may check-raise or check-call
		
		// if no raise preflop, or if more than 1 opponent
		if (currentHand->getPreflopRaisesNumber() == 0 || runningPlayers->size() > 2){

			if (runningPlayers->size() < 4)
				myBetAmount = pot * 0.8;
			else
				myBetAmount = pot * 1.2;
			return true;
		}

		// if i have raised preflop, bet
		if (lastRaiserID == myID && currentHand->getPreflopRaisesNumber() > 0){

			if (runningPlayers->size() < 4)
				myBetAmount = pot * 0.8;
			else
				myBetAmount = pot;

			return true;
		}

	}else{

		///////////  if bad flop for me

		// if there was a lot of action preflop, and i was not the last raiser : don't bet
		if (nbPreflopRaises > 2 && lastRaiserID != myID)
			return false;

		// if I was the last raiser preflop, I may bet with not much
		if (lastRaiserID == myID && myFlopHandSimulation.winRanged > 0.25 && runningPlayers->size() < 4){

			if (runningPlayers->size() < 4)
				myBetAmount = pot * 0.6;
			else
				myBetAmount = pot;
			return true;
		}
	}

	return false;

}
bool LargeAgressivePlayer::flopShouldCall(){

	const int nbRaises = currentHand->getFlopBetsOrRaisesNumber();

	if (nbRaises == 0)
		return false;

	if (isDrawingProbOk())
		return true;

	if (myFlopHandSimulation.winRanged == 1)
		return true;

	if (myFlopHandSimulation.winRanged * 100 < getPotOdd() * 0.8)
		return false;

	return true; 
}

bool LargeAgressivePlayer::flopShouldRaise(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());
	const int potOdd = getPotOdd();
	const int nbPlayers = currentHand->getActivePlayerList()->size(); 
	assert(nbPlayers >= 2);

	const int nbRaises = currentHand->getFlopBetsOrRaisesNumber();

	if (nbRaises == 0)
		return false;

	if (nbRaises == 1 && myFlopHandSimulation.win < 0.90)
		return false;

	if (nbRaises == 2 && myFlopHandSimulation.win < 0.95)
		return false;

	if (nbRaises == 3 && myFlopHandSimulation.win < 0.98)
		return false;

	if (nbRaises > 3 && myFlopHandSimulation.win != 1)
		return false;

	if ((isDrawingProbOk() || bHavePosition) && runningPlayers->size() == 2){
		int rand = 0;
		Tools::GetRand(1, 3, 1, &rand);
		if (rand == 2){
			myRaiseAmount = pot;
			return true;
		}
	}

	if (myFlopHandSimulation.winRanged * 100 < getPotOdd()){

		if (getPotOdd() < 30 && runningPlayers->size() < 4){

			int rand = 0;
			Tools::GetRand(1, 4, 1, &rand);
			if (rand == 2 && myFlopHandSimulation.winRanged > 0.3){
				myRaiseAmount = pot;
				return true;
			}
		}
		return false;
	}

	if (myFlopHandSimulation.winRanged > 0.7){
		myRaiseAmount = pot;
		return true;
	}

	return false;
}


bool LargeAgressivePlayer::turnShouldBet(){

	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	const int nbRaises = currentHand->getTurnBetsOrRaisesNumber();

	if (nbRaises > 0)
		return false;

	if (myTurnHandSimulation.winRanged < 0.45)
		return false;

	
	if (! (myTurnState.IsNoPair || myTurnState.IsBottomPair)){

		if (runningPlayers->size() < 4)
			myBetAmount = pot * 0.6;
		else
			myBetAmount = pot;
		return true;
	}

	// i don't have much, but i may bet, if i have a draw
	if (myTurnState.Is4Flush || myTurnState.FlushOuts > 4 || myTurnState.StraightOuts > 4){
		int rand = 0;
		Tools::GetRand(1, 3, 1, &rand);
		if (rand != 2){
			myBetAmount = pot * 0.6;
			return true;
		}
	}else{
		// no draw, not a good hand, but last to speak and nobody has bet
		if (bHavePosition){
			int rand = 0;
			Tools::GetRand(1, 5, 1, &rand);
			if (rand != 2){
				if (runningPlayers->size() < 4)
					myBetAmount = pot * 0.6;
				else
					myBetAmount = pot;
				return true;
			}
		}
	}

	return false;
}

bool LargeAgressivePlayer::turnShouldCall(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> raisersPositions = currentHand->getRaisersPositions();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();
	const int nbRaises = currentHand->getTurnBetsOrRaisesNumber();
	const int potOdd = getPotOdd();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());

	if (nbRaises == 0)
		return false;

	if (myTurnHandSimulation.winRanged * 100 < getPotOdd() && myTurnHandSimulation.winRanged < 0.9)
		return false;

	if (nbRaises > 1 && myTurnHandSimulation.winRanged < 0.7)
		return false;

	if (myTurnState.IsOnePair){
		
		if ((myTurnState.UsesFirst && getBoardCardsHigherThan(myCard1) > (nbRaises == 0 ? 1 : 0)) ||
			(myTurnState.UsesSecond && getBoardCardsHigherThan(myCard2) > (nbRaises == 0 ? 1 : 0)))
			return false;
	}

	if (getImplicitOdd() + getDrawingProbability() > potOdd || potOdd < 20)
		return true;

	if (myTurnHandSimulation.winRanged > 0.6)
		return true;

	return false;
}

bool LargeAgressivePlayer::turnShouldRaise(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> raisersPositions = currentHand->getRaisersPositions();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();
	const int nbRaises = currentHand->getTurnBetsOrRaisesNumber();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());

	if (nbRaises == 0)
		return false;

	if (nbRaises == 1 && myTurnHandSimulation.win < 0.94)
		return false;

	if (nbRaises == 2 && myTurnHandSimulation.win < 0.98)
		return false;

	if (nbRaises > 2 && myTurnHandSimulation.win != 1)
		return false;

	if (myTurnHandSimulation.win == 1 || (myTurnHandSimulation.winRanged == 1 && nbRaises < 3)){
		myRaiseAmount = pot;
		return true;
	}

	if (myTurnHandSimulation.winRanged * 100 < getPotOdd() && myTurnHandSimulation.winRanged < 0.9)
		return false;

	// if more than 1 card on board are higher than my pair, don't raise
	if (myTurnState.IsOnePair){
		
		if ((myTurnState.UsesFirst && getBoardCardsHigherThan(myCard1) > 1) ||
			(myTurnState.UsesSecond && getBoardCardsHigherThan(myCard2) > 1))
			return false;

		// pot control : don't raise with only a single pair, if there was lot of action on the flop
		if (currentHand->getFlopBetsOrRaisesNumber() > 2)
			return false;

	}

	if (! (myTurnState.IsNoPair || myTurnState.IsBottomPair) && nbRaises == 1){

		if (runningPlayers->size() < 3){
			myRaiseAmount = pot;
			return true;
		}	
	}
	if (myTurnState.IsTrips && nbRaises < 4){
		myRaiseAmount = pot;
		return true;
	}
	if (myTurnState.IsStraight || myTurnState.IsFlush || myTurnState.IsFullHouse || myTurnState.IsQuads || myTurnState.IsStFlush){
		myRaiseAmount = pot;
		return true;
	}
	return false;
}

bool LargeAgressivePlayer::riverShouldBet(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> raisersPositions = currentHand->getRaisersPositions();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();
	const int nbRaises = currentHand->getRiverBetsOrRaisesNumber();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());
	
	if (nbRaises > 0)
		return false;

	if ( myRiverHandSimulation.winSd > .94 || (bHavePosition && myRiverHandSimulation.winSd > .9)){ 
		myBetAmount = pot * 0.4;
		return true;
	}
	if ( myRiverHandSimulation.winRanged > .8 || (bHavePosition && myRiverHandSimulation.winRanged > .7)){ 
		myBetAmount = pot * 0.4;
		return true;
	}
	return false;
}

bool LargeAgressivePlayer::riverShouldCall(){

	const int nbRaises = currentHand->getRiverBetsOrRaisesNumber();
	
	if (nbRaises == 0)
		return false;

	if (myRiverHandSimulation.win > .95){
		return true;
	}

	if (myRiverHandSimulation.winRanged * 100 < getPotOdd())
		return false;

	if (myRiverHandSimulation.winRanged < .3){
		return false;
	}
    return true;
}

bool LargeAgressivePlayer::riverShouldRaise(){

	const int pot = currentHand->getBoard()->getPot() + currentHand->getBoard()->getSets();
	PlayerList runningPlayers = currentHand->getRunningPlayerList();
	std::vector<PlayerPosition> raisersPositions = currentHand->getRaisersPositions();
	std::vector<PlayerPosition> callersPositions = currentHand->getCallersPositions();
	const int highestSet = currentHand->getCurrentBettingRound()->getHighestSet();
	const int nbRaises = currentHand->getRiverBetsOrRaisesNumber();
	const bool bHavePosition = getHavePosition(myPosition, currentHand->getRunningPlayerList());

	if (nbRaises == 0)
		return false;

	//  raise if i have the nuts. TODO : analyze previous actions, and determine if we must bet for value, without the nuts
	if (myRiverHandSimulation.winSd == 1 || myRiverState.IsQuads){

		myRaiseAmount = pot * 0.8;
		return true;
	}

	if (nbRaises < 2 && myRiverHandSimulation.winRanged * 100 > getPotOdd() && myRiverHandSimulation.winRanged > 0.9){

		myRaiseAmount = pot * 0.6;
		return true;
	}

	return false;
}
