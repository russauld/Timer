// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#include <QtGui/QApplication>
#include "timerManager.hxx"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setQuitOnLastWindowClosed(false); // without this, any dialog that gets dismissed while the main gui is hidden will kill the app
	TimerManager w;
	w.show();
	return a.exec();
}
