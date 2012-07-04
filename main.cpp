# Timer application.
# Written by Russell Auld
#include <QtGui/QApplication>
#include "timer.hxx"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setQuitOnLastWindowClosed(false); // without this, any dialog that gets dismissed while the main gui is hidden will kill the app
	Timer w;
	w.show();
	return a.exec();
}
