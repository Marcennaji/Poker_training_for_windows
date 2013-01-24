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
#include "mylefttabwidget.h"

MyLeftTabWidget::MyLeftTabWidget(QGroupBox *parent)
	: QTabWidget(parent), chatBlinkTimer(0), myTabBar(0)
{
	myTabBar = this->tabBar();

// 	chatBlinkTimer = new QTimer;
// 	connect(chatBlinkTimer, SIGNAL(timeout()), this, SLOT( blinkChatTab() ));
}


MyLeftTabWidget::~MyLeftTabWidget()
{
}

void MyLeftTabWidget::startBlinkChatTab()
{
	/*chatBlinkTimer->start(500);*/
}
void MyLeftTabWidget::stopBlinkChatTab()
{
	/*chatBlinkTimer->stop();*/
}
void MyLeftTabWidget::showDefaultChatTab()
{
	/*myTabBar->setTabTextColor(1, QColor(240,240,240));*/
}
void MyLeftTabWidget::disableTab(int tabIndex, bool yesNo)
{
	myTabBar->setTabEnabled(tabIndex, !yesNo);
}

void MyLeftTabWidget::blinkChatTab()
{
//TODO doesnt work while stylesheet is set :(
// 	if(myTabBar->tabTextColor(1).red() == 240) myTabBar->setTabTextColor(1, QColor(113,162,0));
// 	else myTabBar->setTabTextColor(1, QColor(240,240,240));
}

void MyLeftTabWidget::paintEvent(QPaintEvent * event)
{

	QTabWidget::paintEvent(event);

}
