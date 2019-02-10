#!/usr/bin/env python
# -*- coding: utf-8 -*-

#****************************************************************************
#*
#* Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
#* Contact: Qt Software Information (qt-info@nokia.com)
#*
#* This file is part of the example classes of the Qt Toolkit.
#*
#* Commercial Usage
#* Licensees holding valid Qt Commercial licenses may use self file in
#* accordance with the Qt Commercial License Agreement provided with the
#* Software or, alternatively, in accordance with the terms contained in
#* a written agreement between you and Nokia.
#*
#*
#* GNU General Public License Usage
#* Alternatively, self file may be used under the terms of the GNU
#* General Public License versions 2.0 or 3.0 as published by the Free
#* Software Foundation and appearing in the file LICENSE.GPL included in
#* the packaging of self file.  Please review the following information
#* to ensure GNU General Public Licensing requirements will be met:
#* http:#www.fsf.org/licensing/licenses/info/GPLv2.html and
#* http:#www.gnu.org/copyleft/gpl.html.  In addition, as a special
#* exception, Nokia gives you certain additional rights. These rights
#* are described in the Nokia Qt GPL Exception version 1.3, included in
#* the file GPL_EXCEPTION.txt in self package.
#*
#* Qt for Windows(R) Licensees
#* As a special exception, Nokia, as the sole copyright holder for Qt
#* Designer, grants users of the Qt/Eclipse Integration plug-in the
#* right for the Qt/Eclipse Integration to link to functionality
#* provided by Qt Designer and its related libraries.
#*
#* If you are unsure which license is appropriate for your use, please
#* contact the sales department at qt-sales@nokia.com.
#*
#***************************************************************************

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from lcdrange import *
from cannonfield import *

class GameBoard(QWidget):
        def __init__(self, parent=None):
                QWidget.__init__(self, parent)
                quit=QPushButton(QString.fromUtf8(self.tr("&Quit")))
                quit.setFont(QFont("Times", 18, QFont.Bold))

                self.connect(
                        quit,
                        SIGNAL("clicked()"),
                        qApp,
                        SLOT("quit()"),
                )

                angle=LCDRange(QString.fromUtf8(self.tr("ANGLE")))
                angle.setRange(5, 70)

                force=LCDRange(QString.fromUtf8(self.tr("FORCE")))
                force.setRange(10, 50)

                cannonBox=QFrame()
                cannonBox.setFrameStyle(QFrame.WinPanel | QFrame.Sunken)

                self.__cannonField=CannonField()

                self.connect(
                        angle,
                        SIGNAL("valueChanged(int)"),
                        self.__cannonField.setAngle,
                )
                self.connect(
                        self.__cannonField,
                        SIGNAL("angleChanged(int)"),
                        angle.setValue,
                )

                self.connect(
                        force,
                        SIGNAL("valueChanged(int)"),
                        self.__cannonField.setForce,
                )
                self.connect(
                        self.__cannonField,
                        SIGNAL("forceChanged(int)"),
                        force.setValue,
                )

                self.connect(
                        self.__cannonField,
                        SIGNAL("hit()"),
                        self.__hit,
                )
                self.connect(
                        self.__cannonField,
                        SIGNAL("missed()"),
                        self.__missed,
                )

                shoot=QPushButton(QString.fromUtf8(self.tr("&Shoot")))
                shoot.setFont(QFont("Times", 18, QFont.Bold))

                self.connect(
                        shoot,
                        SIGNAL("clicked()"),
                        self.__fire,
                )
                self.connect(
                        self.__cannonField,
                        SIGNAL("canShoot(bool)"),
                        shoot,
                        SLOT("setEnabled(bool)"),
                )

                restart=QPushButton(QString.fromUtf8(self.tr("&New Game")))
                restart.setFont(QFont("Times", 18, QFont.Bold))

                self.connect(
                        restart,
                        SIGNAL("clicked()"),
                        self.__newGame,
                )

                self.__hits=QLCDNumber(2)
                self.__hits.setSegmentStyle(QLCDNumber.Filled)

                self.__shotsLeft=QLCDNumber(2)
                self.__shotsLeft.setSegmentStyle(QLCDNumber.Filled)

                hitsLabel=QLabel(QString.fromUtf8(self.tr("HITS")))
                shotsLeftLabel=QLabel(QString.fromUtf8(self.tr("SHOTS LEFT")))

                #! [2]
                QShortcut(Qt.Key_Enter, self, self.__fire)
                #! [2] #! [3]
                QShortcut(Qt.Key_Return, self, self.__fire)
                #! [3] #! [4]
                QShortcut(Qt.CTRL + Qt.Key_Q, self, SLOT("close()"))
                #! [4]

                topLayout=QHBoxLayout()
                topLayout.addWidget(shoot)
                topLayout.addWidget(self.__hits)
                topLayout.addWidget(hitsLabel)
                topLayout.addWidget(self.__shotsLeft)
                topLayout.addWidget(shotsLeftLabel)
                topLayout.addStretch(1)
                topLayout.addWidget(restart)

                leftLayout=QVBoxLayout()
                leftLayout.addWidget(angle)
                leftLayout.addWidget(force)

                #! [5]
                cannonLayout=QVBoxLayout()
                #! [5] #! [6]
                cannonLayout.addWidget(self.__cannonField)
                cannonBox.setLayout(cannonLayout)

                gridLayout=QGridLayout()
                gridLayout.addWidget(quit, 0, 0)
                gridLayout.addLayout(topLayout, 0, 1)
                gridLayout.addLayout(leftLayout, 1, 0)
                gridLayout.addWidget(cannonBox, 1, 1, 2, 1)
                gridLayout.setColumnStretch(1, 10)
                self.setLayout(gridLayout)
                #! [6]

                angle.setValue(60)
                force.setValue(25)
                angle.setFocus()

                self.__newGame()
        # __init__()

        def __fire(self):
                if self.__cannonField.gameOver() or self.__cannonField.isShooting():
                        return
                self.__shotsLeft.display(self.__shotsLeft.intValue() - 1)
                self.__cannonField.shoot()
        # __fire()

        def __hit(self):
                self.__hits.display(self.__hits.intValue() + 1)
                if self.__shotsLeft.intValue() == 0:
                        self.__cannonField.setGameOver()
                else:
                        self.__cannonField.newTarget()
                # if
        # __hit()

        def __missed(self):
                if self.__shotsLeft.intValue() == 0:
                        self.__cannonField.setGameOver()
        # __missed()

        def __newGame(self):
                self.__shotsLeft.display(15)
                self.__hits.display(0)
                self.__cannonField.restartGame()
                self.__cannonField.newTarget()
        # __newGame()
# class GameBoard
