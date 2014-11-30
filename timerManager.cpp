// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#include "timerManager.hxx"

#include <QMessageBox>

TimerManager::TimerManager(QWidget *parent)
    : QMainWindow(parent)
{
	firstHide = false;
	radio     = true;
	nTimer    = 0;
	resizeTimeoutVal = 250; // msecs
	
	trayMenu = new QMenu(this);
	
	// trayMenu->setDefaultAction(ui->actionSetName);
	// instead of this, call a private function that will handle what the default action is.
	// it also needs to be accounted for in the iconActivated() function. See below where hook up the signals from the tray icon.
	this->setGeometry(100,100,100,100);
	centralWidget = new QWidget(this);
	gridLayout = new QGridLayout(centralWidget);
	gridLayout->setContentsMargins(3,3,3,3);
	gridLayout->setSpacing(3);
	
	setCentralWidget(centralWidget);
	
	quitAction = new QAction(tr("&Quit"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	trayMenu->addAction(quitAction);
	
	redIcon  = new QIcon(":/Classic-Timer-Red-icon_32x32.png");
	greyIcon = new QIcon(":/Classic-Timer-icon_32x32.png");
	
	trayIcon = new QSystemTrayIcon(*greyIcon,this);
	trayIcon->setContextMenu(trayMenu);
	
	connect(trayIcon, SIGNAL( activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	connect(trayIcon, SIGNAL( messageClicked() ), this, SLOT( messageClicked() ) );
	trayIcon->show();
	
	newAct = new QAction("&New",this);
	connect( newAct, SIGNAL( triggered() ), this, SLOT( newTimer() ) );
	
	radioAction = new QAction("&Radio Behavior",this);
	radioAction->setCheckable(true);
	radioAction->setChecked(radio);
	connect( radioAction, SIGNAL(toggled(bool)), this, SLOT(setRadioBehavior(bool)));
	setRadioBehavior(radio);
	
	debugAction = new QAction("Debug",this);
	connect( debugAction, SIGNAL(triggered()), this, SLOT(debug()));
	
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(radioAction);
	// fileMenu->addAction(debugAction);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);
	
	layoutGroup = new QActionGroup(this);
	horizontalAction = new QAction(tr("&Horizontal"),layoutGroup);
	horizontalAction->setCheckable(true);
	// connect(horizontalAction, SIGNAL(triggered()), this, SLOT(setLayoutType()) );
	
	verticalAction = new QAction(tr("&Vertical"),layoutGroup);
	verticalAction->setCheckable(true);
	// connect(verticalAction, SIGNAL(triggered()), this, SLOT(setLayoutType()) );
	
	gridAction = new QAction(tr("&Grid"),layoutGroup);
	gridAction->setCheckable(true);
	// connect(gridAction, SIGNAL(triggered()), this, SLOT(setLayoutType()) );

	signalMapper = new QSignalMapper(this);
	connect(horizontalAction, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
	connect(verticalAction, SIGNAL(triggered()), signalMapper, SLOT( map() ) );
	connect(gridAction, SIGNAL(triggered()), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(horizontalAction, 0);
	signalMapper->setMapping(verticalAction, 1);
	signalMapper->setMapping(gridAction, 2);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setLayoutType(int)) );

	layout = 2;
	gridAction->setChecked(true);
	
	optionMenu = menuBar()->addMenu(tr("&Option"));
	layoutMenu = optionMenu->addMenu(tr("&Layout"));
	layoutMenu->addAction(horizontalAction);
	layoutMenu->addAction(verticalAction);
	layoutMenu->addAction(gridAction);
	
	// resizeTimer = new QTimer(this);
	// connect(resizeTimer, SIGNAL( timeout() ), this, SLOT( resizeTimeout() ) );
}

TimerManager::~TimerManager()
{
	delete trayMenu;
	delete trayIcon;
	delete redIcon;
	delete greyIcon;
	delete quitAction;
	delete centralWidget;
	delete newAct;
	delete radioAction;
	delete debugAction;
	delete fileMenu;
	delete layoutMenu;
	delete optionMenu;
	// delete resizeTimer;
	delete layoutGroup;
}

void TimerManager::closeEvent(QCloseEvent *event)
{
	if (trayIcon->isVisible()) {
		// QMessageBox::information(this, tr("Systray"),
										 // tr("The program will keep running in the "
											 // "system tray. To terminate the program, "
											 // "choose <b>Quit</b> in the context menu "
											 // "of the system tray entry."));
		if (this->isVisible()) {
			hide();
			if (!firstHide) {
				trayIcon->showMessage(tr("Timer is still running"),tr("Choose Quit to terminte the program"), QSystemTrayIcon::NoIcon);
				firstHide = true;
			}
			event->ignore();
		}
	}
}

void TimerManager::resizeEvent(QResizeEvent *event)
{
	// This will get called repeatedly as the window is dragged. We only want to update occasionally, so we use a timer.
	// resizeTimer->stop();
	// resizeTimer->start(resizeTimeoutVal);
	QMainWindow::resizeEvent(event);
}

void TimerManager::newTimer()
{
	int id = timerList.length(); 
	Timer *t = new Timer(centralWidget, id);
	timerList.push_back(t);
	connect( t, SIGNAL( closeMe(int) ), this, SLOT(closeTimer(int)) );
	connect( t, SIGNAL( timesUp(QString) ), this, SLOT(timerExpired(QString)) );
	connect( t, SIGNAL( started(int) ), this, SLOT( timerStarted(int) ) );
	// int row = nTimer % 2;
	// int col = nTimer / 2;
	// gridLayout->addWidget(t,row,col);
	// QSize x = t->size();
	// QString s = QString("id: %1, h=%2, w=%3").arg(id).arg(x.height()).arg(x.width());
	// QMessageBox::information(this,"DEBUG",s);
	nTimer++;
	computeLayout();
}

void TimerManager::debug()
{
	QString s;
	QList< Timer* >::const_iterator i;
	for ( i = timerList.constBegin(); i != timerList.constEnd(); ++i ) {
		if (*i != NULL) {
			QSize x = (*i)->size();
			s += QString("id: %1, h=%2, w=%3\n").arg( (*i)->getId()).arg(x.height()).arg(x.width());
		}
	}
	QMessageBox::information(this,"DEBUG", s);
}

void TimerManager::closeTimer(int _id)
{
	if (_id < timerList.length() ) {
		timerList[_id]->close();
		gridLayout->removeWidget(timerList[_id]);
		//Timer *t = timerList[_id];
		timerList[_id] = NULL;
		//delete t;
		// deleting the widget crashes the GUI
		// Maybe due to chained constructors?
		// when we create the widget, we set the parent as this, so in principle it will clean up at the end.
		// The layout takes ownership of the widget so it will handle the delete.
		nTimer--;
		computeLayout();
	}
}

void TimerManager::setRadioBehavior(bool v)
{
	radio = v;
}

void TimerManager::setLayoutType(int t)
{
	int oldlayout = layout;
	layout = t;
	if (oldlayout != layout)
		computeLayout();
}

void TimerManager::timerExpired(QString name)
{
	if (isVisible()) {
		QMessageBox::information(this,"Time's up!", "Hey! Timer \""+name+"\" expired!");
	} else {
		trayIcon->showMessage("Hey! Time's up!", name+" has expired", QSystemTrayIcon::Critical, 60000);
	}
	trayIcon->setIcon(*redIcon);

}

// Slot to receive started events from the timers.
// When working in radio mode, stop all the other timers when one starts.
void TimerManager::timerStarted(int c)
{
	if (radio) {
		QList< Timer* >::const_iterator i;
		for ( i = timerList.constBegin(); i != timerList.constEnd(); ++i ) {
			if (*i != NULL) {
				if ( c != (*i)->getId()) {
					(*i)->stop();
				}
			}
		}
	}
}

void TimerManager::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	QString time;
	switch (reason) {
		case QSystemTrayIcon::Context:
		// the context menu shows normally under this "reason"
		//trayIcon->showMessage("Title", "Context");
		break;
	// Left click
	case QSystemTrayIcon::Trigger:
		// if (showSecs)
			// time = QString("%1:%2:%3").arg(hours,2).arg(minutes,2,10,QChar('0')).arg(secs,2,10,QChar('0'));
		// else
			// time = QString("%1:%2").arg(hours,2).arg(minutes,2,10,QChar('0'));
		// trayIcon->showMessage("Timer", time);
		
		// Do the default action here rather than show/hide. See constructor for default context menu action.
		if (isHidden()) {
			show();
		}else{
			hide();
		}
		break;
	case QSystemTrayIcon::DoubleClick:
		//trayIcon->showMessage("Title", "DoubleClick");
		break;
	case QSystemTrayIcon::MiddleClick:
		//trayIcon->showMessage("Title", "MiddleClick");
		break;
	default:
		;
	}
}

// Slot connected to our resizeTimer. 
void TimerManager::resizeTimeout(void)
{
	// resizeTimer->stop();
	// computeLayout();
}

void TimerManager::computeLayout(void)
{
	// remove all widgets from the grid layout:
	QList< Timer* >::const_iterator i;
	for ( i = timerList.constBegin(); i != timerList.constEnd(); ++i ) {
		if (*i != NULL) {
			gridLayout->removeWidget(*i);
		}
	}
	
	// Compute number of columns and rows:
	int nrow=0,ncol=0;
	bool done = false;
	for (int j=1; layout == 2 && !done; j++) {
		if ( nTimer > ((j-1)*(j-1)) && nTimer <= (j*j) ) {
			ncol = j;
			nrow = j;
			done = true;
		}
	}
	// int ncol = this->width()  / Timer::w;
	// int nrow = this->height() / Timer::h;
	// if (nTimer > ncol*nrow) ncol++;
	
	// Create new layout:
	int col = 0,row = 0;
	for ( i = timerList.constBegin(); i != timerList.constEnd(); ++i ) {
		if (*i != NULL) {
			gridLayout->addWidget((*i), row, col);
			switch(layout) {
				case 0: // horizontalAction
					col++;
					break;
				case 1: // verticalAction
					row++;
					break;
				case 2: // gridAction
					// column major:
					col++;
					if (col > ncol-1) {
						col = 0;
						row++;
					}
					// row major:
					// row++;
					// if (row > nrow-1) {
						// row = 0;
						// col++;
					// }
			}
		}
	}
}

void TimerManager::messageClicked()
{
	trayIcon->setIcon(*greyIcon);
}
