#-------------------------------------------------
#
# Project for Timer
#
#-------------------------------------------------

TARGET = Timer
TEMPLATE = app


SOURCES += main.cpp \
           timer.cpp \
           timerManager.cpp

HEADERS  += timer.hxx \
            timerManager.hxx

FORMS    += timer-widget.ui \
            newValueDialog.ui

RESOURCES = timer.qrc
RC_FILE   = timer.rc
