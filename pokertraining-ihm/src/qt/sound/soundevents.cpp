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
#include <qt/sound/sdlplayer.h>
#include <configfile.h>
#include "session.h"
#include <engine/game.h>
#include "soundevents.h"

SoundEvents::SoundEvents(ConfigFile *c): myConfig(c), lastSBValue(0), lastSBLevel(0), newGameNow(false)
{
	mySDLPlayer = new SDLPlayer(myConfig);
}

SoundEvents::~SoundEvents()
{
	mySDLPlayer->deleteLater();
}

void SoundEvents::blindsWereSet(int sB)
{
	if(newGameNow) {
		lastSBLevel = 0;
		lastSBValue = sB;
		newGameNow = false;
	}

	if(sB > lastSBValue) {

		lastSBValue = sB;
		++lastSBLevel;

		if(myConfig->readConfigInt("PlayBlindRaiseNotification")) {
			if(lastSBLevel == 1 || lastSBLevel == 2) {
				mySDLPlayer->playSound("blinds_raises_level1", 0);
			}
			if(lastSBLevel == 3 || lastSBLevel == 4) {
				mySDLPlayer->playSound("blinds_raises_level2", 0);
			}
			if(lastSBLevel >= 5) {
				mySDLPlayer->playSound("blinds_raises_level3", 0);
			}
		}
	}
}

void SoundEvents::newGameStarts()
{
	newGameNow = true;
}
