#-------------------------------------------------
# PrestoPalette
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = PrestoPalette
TEMPLATE = app

VER_MAJ = 0
VER_MIN = 1
VER_PAT = 31
VERSION = $$sprintf("%1.%2.%3",$$VER_MAJ,$$VER_MIN,$$VER_PAT)

QMAKE_TARGET_COMPANY = John Cboins and Darryl T. Agostinelli
QMAKE_TARGET_PRODUCT = PrestoPalette
QMAKE_TARGET_DESCRIPTION = "An artist's tool for creating harmonious color palettes"
QMAKE_TARGET_COPYRIGHT = (c) 2018 by John Cboins and Darryl T. Agostinelli. All Rights Reserved.
QMAKE_INFO_PLIST = Info.plist

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	aboutdialog.cpp \
	circlepalette.cpp \
	clickablelabel.cpp \
	lightingsliderstyle.cpp \
	visualpalette.cpp \
	main.cpp \
	mainwindow.cpp

HEADERS += \
	aboutdialog.h \
	circlepalette.h \
	clickablelabel.h \
	gui_aboutdialog.h \
	gui_mainwindow.h \
	lightingsliderstyle.h \
	visualpalette.h \
	mainwindow.h

#FORMS += \
#	mainwindow.ui

RESOURCES += \
	resources.qrc

CONFIG(debug, debug|release) {
	DESTDIR = build/debug
} else {
	DESTDIR = build/release
}

# Windows only icon
RC_ICONS = graphics/favicon.ico

# Mac only icon
ICON = graphics/favicon.icns

