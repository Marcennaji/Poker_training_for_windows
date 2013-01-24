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

#ifndef PLAYER_STATISTICS_H
#define PLAYER_STATISTICS_H


class PreflopStatistics{
	
	public :

		float getVoluntaryPutMoneyInPot() const;
		float getPreflopRaise() const;

		void reset();

		long m_hands;
		long m_folds;
		long m_limps;
		long m_checks;
		long m_calls;
		long m_raises;
		long m_threeBets;
		long m_fourBets;
};

class FlopStatistics{
	
	public :

		float getAgressionFactor() const;
		float getAgressionFrequency() const;
		float getContinuationBetFrequency() const;

		void reset();

		long m_hands;
		long m_folds;
		long m_checks;
		long m_calls;
		long m_raises;
		long m_threeBets;
		long m_fourBets;
		long m_bets;
		long m_continuationBetsOpportunities;
		long m_continuationBets;
};

class TurnStatistics{
	
	public :

		void reset();

		float getAgressionFrequency() const;

		long m_hands;
		long m_folds;
		long m_checks;
		long m_calls;
		long m_bets;
		long m_raises;
		long m_threeBets;
		long m_fourBets;
};

class RiverStatistics{
	
	public :

		void reset();

		float getAgressionFrequency() const;

		long m_hands;
		long m_folds;
		long m_checks;
		long m_calls;
		long m_bets;
		long m_raises;
		long m_threeBets;
		long m_fourBets;
};


class PlayerStatistics 
{
public:

	PlayerStatistics(){ reset();};
	~PlayerStatistics(){};

	const PreflopStatistics & getPreflopStatistics() const;
	const FlopStatistics & getFlopStatistics() const;
	const TurnStatistics & getTurnStatistics() const;
	const RiverStatistics & getRiverStatistics() const;
	void reset(); // init to zero

protected :

	friend class Player;

	long m_toTalHands;
	PreflopStatistics m_preflopStatistics;
	FlopStatistics m_flopStatistics;
	TurnStatistics m_turnStatistics;
	RiverStatistics m_riverStatistics;
};

#endif