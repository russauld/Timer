#-------------------------------------------------
#
# Project for Timer
#
#-------------------------------------------------

TARGET = Timer
TEMPLATE = app


SOURCES += main.cpp\
           timer.cpp

HEADERS  += timer.hxx

FORMS    += timer.ui \
            newValueDialog.ui

RESOURCES = timer.qrc
RC_FILE   = timer.rc
