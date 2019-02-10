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

from PyQt4.QtCore import *
from PyQt4.QtGui import *

class LCDRange(QWidget):
        def __init__(self, text=None, parent=None):
                QWidget.__init__(self, parent)
                self.__init()
                if text:
                        self.setText(text)
        # __init__()

        def __init(self):
                lcd = QLCDNumber(2)
                lcd.setSegmentStyle(QLCDNumber.Filled)

                self.__slider = QSlider(Qt.Horizontal)
                self.__slider.setRange(0, 99)
                self.__slider.setValue(0)
                self.__label = QLabel()
                self.__label.setAlignment(Qt.AlignHCenter | Qt.AlignTop)
                #! [0]
                self.__label.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
                #! [0]

                self.connect(
                        self.__slider,
                        SIGNAL("valueChanged(int)"),
                        lcd,
                        SLOT("display(int)"),
                )
                self.connect(
                        self.__slider,
                        SIGNAL("valueChanged(int)"),
                        self,
                        SIGNAL("valueChanged(int)"),
                )

                layout = QVBoxLayout()
                layout.addWidget(lcd)
                layout.addWidget(self.__slider)
                layout.addWidget(self.__label)
                self.setLayout(layout)

                self.setFocusProxy(self.__slider)
        # __init()

        def value(self):
                return self.__slider.value()
        # value()

        def text(self):
                return self.__label.text()
        # text()

        def setValue(self, value):
                self.__slider.setValue(value)
        # setValue()

        def setRange(self, minValue, maxValue):
                if minValue < 0 or maxValue > 99 or minValue > maxValue:
                        qWarning("LCDRange.setRange(%d, %d)\n"
                                 "\tRange must be 0..99\n"
                                 "\tand minValue must not be greater than maxValue",
                                 minValue, maxValue)
                return
                self.__slider.setRange(minValue, maxValue)
        # setRange()

        def setText(self, text):
                self.__label.setText(text)
        # setText()
# class LCDRange
