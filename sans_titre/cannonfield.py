#!/usr/bin/env python
# -*- coding: utf-8 -*-

#***************************************************************************
#
# Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
# Contact: Qt Software Information (qt-info@nokia.com)
#
# This file is part of the example classes of the Qt Toolkit.
#
# Commercial Usage
# Licensees holding valid Qt Commercial licenses may use self file in
# accordance with the Qt Commercial License Agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and Nokia.
#
#
# GNU General Public License Usage
# Alternatively, self file may be used under the terms of the GNU
# General Public License versions 2.0 or 3.0 as published by the Free
# Software Foundation and appearing in the file LICENSE.GPL included in
# the packaging of self file.  Please review the following information
# to ensure GNU General Public Licensing requirements will be met:
# http:#www.fsf.org/licensing/licenses/info/GPLv2.html and
# http:#www.gnu.org/copyleft/gpl.html.  In addition, as a special
# exception, Nokia gives you certain additional rights. These rights
# are described in the Nokia Qt GPL Exception version 1.3, included in
# the file GPL_EXCEPTION.txt in self package.
#
# Qt for Windows(R) Licensees
# As a special exception, Nokia, as the sole copyright holder for Qt
# Designer, grants users of the Qt/Eclipse Integration plug-in the
# right for the Qt/Eclipse Integration to link to functionality
# provided by Qt Designer and its related libraries.
#
# If you are unsure which license is appropriate for your use, please
# contact the sales department at qt-sales@nokia.com.
#
#**************************************************************************

import math
import random
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class CannonField(QWidget):
        barrelRect = QRect(30, -5, 20, 10)
        firstTime = True

        def __init__(self, parent=None):
                QWidget.__init__(self, parent)
                self.__currentAngle = 45
                self.__currentForce = 0
                self.__timerCount = 0
                self.__autoShootTimer = QTimer(self)
                self.connect(
                        self.__autoShootTimer,
                        SIGNAL("timeout()"),
                        self.__moveShot,
                )
                self.__shootAngle = 0
                self.__shootForce = 0
                self.__target = QPoint(0, 0)
                self.__gameEnded = False
                #! [0]
                self.__barrelPressed = False
                #! [0]
                self.setPalette(QPalette(QColor(250, 250, 200)))
                self.setAutoFillBackground(True)
                self.newTarget()
        # __init__()

        def setAngle(self, angle):
                if angle < 5:
                        angle = 5
                if angle > 70:
                        angle = 70
                if self.__currentAngle == angle:
                        return
                self.__currentAngle = angle
                self.update(self.__cannonRect())
                self.emit(SIGNAL("angleChanged(int)"), self.__currentAngle)
        # setAngle()

        def setForce(self, force):
                if force < 0:
                        force = 0
                if self.__currentForce == force:
                        return
                self.__currentForce = force
                self.emit(SIGNAL("forceChanged(int)"), self.__currentForce)
        # setForce()

        def shoot(self):
                if self.isShooting():
                        return
                self.__timerCount = 0
                self.__shootAngle = self.__currentAngle
                self.__shootForce = self.__currentForce
                self.__autoShootTimer.start(5)
                self.emit(SIGNAL("canShoot(bool)"), False)
        # shoot()

        def newTarget(self):
                if CannonField.firstTime:
                        CannonField.firstTime = False
                        midnight = QTime(0, 0, 0)
                        random.seed(midnight.secsTo(QTime.currentTime()))
                # if
                self.__target = QPoint(
                        200 + random.randint(0, 190 - 1),
                        10 + random.randint(0, 255 - 1),
                )
                self.update()
        # newTarget()

        def setGameOver(self):
                if self.__gameEnded:
                        return
                if self.isShooting():
                        autoShootTimer.stop()
                self.__gameEnded = True
                self.update()
        # setGameOver()

        def restartGame(self):
                if self.isShooting():
                        self.__autoShootTimer.stop()
                self.__gameEnded = False
                self.update()
                self.emit(SIGNAL("canShoot(bool)"), True)
        # restartGame()

        def __moveShot(self):
                region = QRegion(self.__shotRect())
                self.__timerCount += 1

                shotR = self.__shotRect()

                if shotR.intersects(self.__targetRect()):
                        self.__autoShootTimer.stop()
                        self.emit(SIGNAL("hit()"))
                        self.emit(SIGNAL("canShoot(bool)"), True)
        #! [1]
                elif shotR.x() > self.width() or shotR.y() > self.height()\
                        or shotR.intersects(self.__barrierRect()):
        #! [1]
                        self.__autoShootTimer.stop()
                        self.emit(SIGNAL("missed()"))
                        self.emit(SIGNAL("canShoot(bool)"), True)
                else:
                        region = region.unite(QRegion(shotR))

                self.update(region)
        # __moveShot()

        #! [2]
        def mousePressEvent(self, event):
                if event.button() != Qt.LeftButton:
                        return
                if self.barrelHit(event.pos()):
                        self.__barrelPressed = True
        # mousePressEvent()
        #! [2]

        #! [3]
        def mouseMoveEvent(self, event):
                if not self.__barrelPressed:
                        return
                pos = event.pos()
                if pos.x() <= 0:
                        pos.setX(1)
                if pos.y() >= height():
                        pos.setY(height() - 1)
                rad = atan((double(rect().bottom()) - pos.y()) / pos.x())
                self.setAngle(qRound(rad * 180 / 3.14159265))
        #! [3] #! [4]
        # mouseMoveEvent()
        #! [4]

        #! [5]
        def mouseReleaseEvent(self, event):
                if event.button() == Qt.LeftButton:
                        self.__barrelPressed = False
        # mouseReleaseEvent():
        #! [5]

        def paintEvent(self, event):
                painter=QPainter(self)

                if self.__gameEnded:
                        painter.setPen(Qt.black)
                        painter.setFont(QFont("Courier", 48, QFont.Bold))
                        painter.drawText(
                                self.rect(),
                                Qt.AlignCenter,
                                self.tr("Game Over"),
                        )
                # if
                self.__paintCannon(painter)
                #! [6]
                self.__paintBarrier(painter)
                #! [6]
                if self.isShooting():
                        self.__paintShot(painter)
                if not self.__gameEnded:
                        self.__paintTarget(painter)
        # paintEvent()

        def __paintShot(self, painter):
                painter.setPen(Qt.NoPen)
                painter.setBrush(Qt.black)
                painter.drawRect(self.__shotRect())
        # __paintShot()

        def __paintTarget(self, painter):
                painter.setPen(Qt.black)
                painter.setBrush(Qt.red)
                painter.drawRect(self.__targetRect())
        # __paintTarget()

        #! [7]
        def __paintBarrier(self, painter):
                painter.setPen(Qt.black)
                painter.setBrush(Qt.yellow)
                painter.drawRect(self.__barrierRect())
        # __paintBarrier()
        #! [7]

        def __paintCannon(self, painter):
                painter.setPen(Qt.NoPen)
                painter.setBrush(Qt.blue)

                painter.save()
                painter.translate(0, self.height())
                painter.drawPie(QRect(-35, -35, 70, 70), 0, 90 * 16)
                painter.rotate(-self.__currentAngle)
                painter.drawRect(CannonField.barrelRect)
                painter.restore()
        # __paintCannon()

        def __cannonRect(self):
                result = QRect(0, 0, 50, 50)
                result.moveBottomLeft(self.rect().bottomLeft())
                return result
        # __cannonRect()

        def __shotRect(self):
                gravity = 4.0

                time = self.__timerCount / 40.0
                velocity = self.__shootForce
                radians = self.__shootAngle * 3.14159265 / 180

                velx = velocity * math.cos(radians)
                vely = velocity * math.sin(radians)
                x0 = (CannonField.barrelRect.right() + 5) * math.cos(radians)
                y0 = (CannonField.barrelRect.right() + 5) * math.sin(radians)
                x = x0 + velx * time
                y = y0 + vely * time - 0.5 * gravity * time * time

                result = QRect(0, 0, 6, 6)
                result.moveCenter(
                        QPoint(qRound(x), self.height() - 1 - qRound(y))
                )
                return result
        # __shotRect()

        def __targetRect(self):
                result = QRect(0, 0, 20, 10)
                result.moveCenter(
                        QPoint(self.__target.x(), self.height() - 1 - self.__target.y())
                )
                return result
        # __targetRect()

        #! [8]
        def __barrierRect(self):
                return QRect(145, self.height() - 100, 15, 99)
        # __barrierRect()
        #! [8]

        #! [9]
        def barrelHit(self, pos):
                matrix=QMatrix()
                matrix.translate(0, self.height())
                matrix.rotate(-self.__currentAngle)
                (matrix, invertible) = matrix.inverted()
                return self.barrelRect.contains(matrix.map(pos))
        #! [9]

        def gameOver(self):
                return self.__gameEnded
        # gameOver()

        def isShooting(self):
                return self.__autoShootTimer.isActive()
        # isShooting()

        def sizeHint(self):
                return QSize(400, 300)
        # sizeHint()
# class CannonField
