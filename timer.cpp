// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#include "timer.hxx"
#include "ui_timer-widget.h"
#include "ui_newValueDialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QVBoxLayout>
#include <QMenu>


Timer::Timer(QWidget *parent, int _id)
    : QWidget(parent), ui(new Ui::Timer), newTimeDialogUi(new Ui::SetValueDialog), newNameDialogUi(new Ui::SetValueDialog)
{
	ui->setupUi(this);
	id        = _id;
	name      = "Timer"+QString("%1").arg(id);
	_started   = false;
	off       = false;
	countUp   = false;
	showSecs  = true;
	showBar   = false;
	secs      = 0;
	minutes   = 0;
	hours     = 0;
	// firstHide = false;
	newTimeDialog = NULL;
	newNameDialog  = NULL;
	timer   = new QTimer(this);
	timer->start(1000); // one second
	setName(name);
	
	connect( ui->startButton, SIGNAL( clicked() ), this, SLOT( start() ) );
	connect( ui->stopButton,  SIGNAL( clicked() ), this, SLOT( stopReset()  ) );
	// connect( ui->actionExit,  SIGNAL(triggered()), qApp, SLOT( quit()  ) );
	// connect( ui->actionShowSeconds, SIGNAL( toggled(bool) ), this, SLOT(showSeconds(bool) ) );
	// // Calling this function should cause the toggled() signal to be emitted:
	// connect( ui->actionShowProgressBar, SIGNAL( toggled(bool) ), this, SLOT( showProgressBar(bool) ) );
	// connect( ui->actionSetTime, SIGNAL( triggered() ), this, SLOT( showSetTimeDialog() ) );
	// connect( ui->actionSetName, SIGNAL( triggered() ), this, SLOT( showSetNameDialog() ) );
	// connect( ui->actionCountUp, SIGNAL( toggled(bool) ), this, SLOT( setCountUp(bool) ) );
	
	signalMapper = new QSignalMapper(this);
	connect( ui->hUpButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	connect( ui->mUpButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	connect( ui->sUpButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	connect( ui->hDownButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	connect( ui->mDownButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	connect( ui->sDownButton, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(ui->hUpButton, 0);
	signalMapper->setMapping(ui->mUpButton, 1);
	signalMapper->setMapping(ui->sUpButton, 2);
	signalMapper->setMapping(ui->hDownButton, 3);
	signalMapper->setMapping(ui->mDownButton, 4);
	signalMapper->setMapping(ui->sDownButton, 5);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(timeCtrlClicked(int)));
	connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT( setTime(const QString &) ));
	
	// trayMenu = new QMenu(this);
	
	fiveMinAction = new QAction("5:00",this);
	connect(fiveMinAction, SIGNAL(triggered()), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(fiveMinAction, "5:00");
	// trayMenu->addAction(fiveMinAction);
	
	tenMinAction = new QAction("10:00",this);
	connect(tenMinAction, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(tenMinAction, "10:00");
	// trayMenu->addAction(tenMinAction);
	
	fifteenMinAction = new QAction("15:00",this);
	connect(fifteenMinAction, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(fifteenMinAction, "15:00");
	// trayMenu->addAction(fifteenMinAction);
	
	halfHourAction = new QAction("30:00",this);
	connect(halfHourAction, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(halfHourAction, "30:00");
	// trayMenu->addAction(halfHourAction);
	
	oneHourAction = new QAction("1:00:00",this);
	connect(oneHourAction, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
	signalMapper->setMapping(oneHourAction, "1:00:00");
	// trayMenu->addAction(oneHourAction);
	
	// trayMenu->addSeparator();
	
	// trayMenu->addAction(ui->actionSetName);
	// trayMenu->setDefaultAction(ui->actionSetName);
	
	closeAction = new QAction(tr("&Close"), this);
	connect(closeAction, SIGNAL(triggered()), this, SLOT(closeRequest()));
	// trayMenu->addAction(quitAction);
	
	// redIcon  = new QIcon(":/Classic-Timer-Red-icon_32x32.png");
	// greyIcon = new QIcon(":/Classic-Timer-icon_32x32.png");
	// trayIcon = new QSystemTrayIcon(*greyIcon,this);
	// trayIcon->setContextMenu(trayMenu);
	
	// connect(trayIcon, SIGNAL( activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	// connect(trayIcon, SIGNAL( messageClicked() ), this, SLOT( messageClicked() ) );
	// trayIcon->show();
	
	// ui->actionShowSeconds->setChecked(showSecs);
	// ui->actionShowProgressBar->setChecked(showBar);
	actionShowSeconds = new QAction("Show &Seconds",this);
	actionShowSeconds->setCheckable(true);
	connect( actionShowSeconds, SIGNAL( toggled(bool) ), this, SLOT(showSeconds(bool) ) );
	actionShowSeconds->setChecked(showSecs);
	showSeconds(showSecs);
	
	actionShowProgressBar = new QAction("Show &Progress Bar",this);
	actionShowProgressBar->setCheckable(true);
	// Calling this function should cause the toggled() signal to be emitted:
	// what function? connect? 
	connect( actionShowProgressBar, SIGNAL( toggled(bool) ), this, SLOT( showProgressBar(bool) ) );
	actionShowProgressBar->setChecked(showBar);
	showProgressBar(showBar);
	
	actionCountUp = new QAction("&Count Up",this);
	actionCountUp->setCheckable(true);
	connect( actionCountUp, SIGNAL( toggled(bool) ), this, SLOT( setCountUp(bool) ) );
	actionCountUp->setChecked(countUp);
	setCountUp(countUp);
	
	actionSetTime = new QAction("Set &Time",this);
	connect( actionSetTime, SIGNAL( triggered() ), this, SLOT( showSetTimeDialog() ) );
	
	actionSetName = new QAction("Set &Name",this);
	connect( actionSetName, SIGNAL( triggered() ), this, SLOT( showSetNameDialog() ) );
	
	showTime(false);
}

Timer::~Timer()
{
	delete ui;
	delete timer;
	// delete signalMapper;
	// delete trayMenu;
	// delete trayIcon;
	// delete redIcon;
	// delete greyIcon;
	delete fiveMinAction;
	delete tenMinAction;
	delete fifteenMinAction;
	delete halfHourAction;
	delete oneHourAction;
	delete closeAction;
	delete newTimeDialog;
	delete newNameDialog;
	delete actionShowSeconds;
	delete actionShowProgressBar;
	delete actionSetTime;
	delete actionSetName;
	delete actionCountUp;
}

void Timer::contextMenuEvent( QContextMenuEvent * event ) 
{
	QMenu menu(this);
	menu.addAction(actionShowSeconds);
	menu.addAction(actionShowProgressBar);
	menu.addAction(actionSetTime);
	menu.addAction(actionSetName);
	menu.addAction(actionCountUp);
	menu.addSeparator();
	menu.addAction(fiveMinAction);
	menu.addAction(tenMinAction);
	menu.addAction(fifteenMinAction);
	menu.addAction(halfHourAction);
	menu.addAction(oneHourAction);
	menu.addSeparator();
	menu.addAction(closeAction);
	menu.exec(event->globalPos());
}

// void Timer::closeEvent(QCloseEvent *event)
// {
	// if (trayIcon->isVisible()) {
		// // QMessageBox::information(this, tr("Systray"),
										 // // tr("The program will keep running in the "
											 // // "system tray. To terminate the program, "
											 // // "choose <b>Quit</b> in the context menu "
											 // // "of the system tray entry."));
		// if (this->isVisible()) {
			// hide();
			// if (!firstHide) {
				// trayIcon->showMessage(tr("Timer is still running"),tr("Choose Quit to terminte the program"), QSystemTrayIcon::NoIcon);
				// firstHide = true;
			// }
			// event->ignore();
		// }
	// }
// }

void Timer::closeRequest(void)
{
	emit closeMe(id);
}
 
void Timer::start()
{
	if (_started) return;
	if (hours == 0 && minutes == 0 && secs == 0) {
		setCountUp(true);
		// ui->actionCountUp->setChecked(countUp);
	}
	// else{
		// countUp = false;
	// }
	
	_started = true;
	// disable gui elements:
	ui->startButton->setEnabled(false);
	ui->hUpButton->setEnabled(false);
	ui->mUpButton->setEnabled(false);
	ui->sUpButton->setEnabled(false);
	ui->hDownButton->setEnabled(false);
	ui->mDownButton->setEnabled(false);
	ui->sDownButton->setEnabled(false);
	connect(timer, SIGNAL( timeout() ), this, SLOT( updateTime() ) );
	//connect(timer, SIGNAL( timeout() ), this, SLOT( showTimeWithToggle() ) );
	off = true;
	//showTime(true);
	// trayIcon->setIcon(*greyIcon);
	fiveMinAction->setEnabled(false);
	tenMinAction->setEnabled(false);
	fifteenMinAction->setEnabled(false);
	halfHourAction->setEnabled(false);
	oneHourAction->setEnabled(false);
	emit started(id);
}

void Timer::stop()
{
	_started = false;
	//disconnect(countdownTimer, SIGNAL( timeout() ), this, SLOT( updateTime() ) );
	disconnect(timer, SIGNAL( timeout() ), this, SLOT( updateTime() ) );
	//disconnect(timer, SIGNAL( timeout() ), this, SLOT( showTimeWithToggle() ) );
	//off = false;
	//showTime(false);
	ui->startButton->setEnabled(true);
	ui->hUpButton->setEnabled(true);
	ui->mUpButton->setEnabled(true);
	ui->sUpButton->setEnabled(true);
	ui->hDownButton->setEnabled(true);
	ui->mDownButton->setEnabled(true);
	ui->sDownButton->setEnabled(true);
	fiveMinAction->setEnabled(true);
	tenMinAction->setEnabled(true);
	fifteenMinAction->setEnabled(true);
	halfHourAction->setEnabled(true);
	oneHourAction->setEnabled(true);
}

void Timer::stopReset()
{
	// Dual function button. If already stopped, reset the timer value:
	if (!_started) {
		//reset:
		hours = 0;
		minutes = 0;
		secs = 0;
		//off = false;
		showTime(false);
		// trayIcon->setIcon(*greyIcon);
		return;
	}
	stop();
}

void Timer::updateTime()
{
	bool done=false;
	if (countUp) {
		secs++;
		if (secs > 59 ) {
			secs = 0;
			minutes++;
		}
		if (minutes > 59) {
			minutes = 0;
			hours++;
		}
		// if (hours > 23) {
			// hours = 0;
		// }
	}
	else{
		// Count down:
		secs--;
		
		if (hours == 0 && minutes == 0 && secs == 0) {
			stop();
			done=true;
		}
		
		if (secs < 0 ) {
			secs = 59;
			minutes--;
		}
		if (minutes < 0) {
			minutes = 59;
			hours--;
		}
	}
	showTime(true);
	if (done) emit timesUp(name);
}

//TODO: clean up the blinking colon technology. This argument was related to that i think and it's no longer used.
void Timer::showTime(bool toggle_colon)
{
	QString time;
	if (showSecs) {
		//digits  = 8;
		ui->lcdNumber->setDigitCount(8);
		//ui->lcdNumber->display(QString("0:05:00"));
		
		time = QString("%1:%2:%3").arg(hours,2).arg(minutes,2,10,QChar('0')).arg(secs,2,10,QChar('0'));
		// if (toggle_colon) {
			// if (off) {
				// time[2]=' ';
				// time[5]=' ';
				// off = false;
			// }else{
				// off = true;
			// }
		// }
	}else{
		//digits  = 5;
		ui->lcdNumber->setDigitCount(5);
		
		time = QString("%1:%2").arg(hours,2).arg(minutes,2,10,QChar('0'));
		// if (toggle_colon) {
			// if (off) {
				// time[2]=' ';
				// off = false;
			// }else{
				// off = true;
			// }
		// }
	}
	ui->lcdNumber->display(time);
	// trayIcon->setToolTip(name+": "+time);
	ui->progressBar->setValue(secs);
}

void Timer::timeCtrlClicked(int b)
{
	if (_started) return;
	
	switch (b) {
		case 0:
			hours++;
			//if (hours > 23) hours=0; // let's be honest here
			break;
		case 1:
			minutes++;
			if (minutes > 59) minutes=0;
			break;
		case 2:
			secs++;
			if (secs > 59) secs=0;
			break;
		case 3:
			hours--;
			if (hours < 0) hours=0;
			break;
		case 4:
			minutes--;
			if (minutes < 0) minutes=0;
			break;
		case 5:
			secs--;
			if (secs < 0) secs=0;
			break;
		//default:
	}
	//off=false;
	showTime(false);
}
int Timer::getId() {
	return id;
}

void Timer::showSeconds(bool val)
{
	showSecs = val;
	if (val) {
		ui->sUpButton->show();
		ui->sDownButton->show();
	}
	else{
		ui->sUpButton->hide();
		ui->sDownButton->hide();
	}
	showTime(_started);
}

void Timer::showProgressBar(bool val)
{
	showBar = val;
	if (val) {
		ui->progressBar->show();
	}else{
		ui->progressBar->hide();
	}
	showTime(_started);
}

void Timer::showSetTimeDialog()
{
	if (!newTimeDialog) {
		newTimeDialog = new QDialog(this);
		newTimeDialogUi->setupUi(newTimeDialog);
		connect(newTimeDialog, SIGNAL( accepted() ), this, SLOT(setTimeFromDialog()) );
		newTimeDialogUi->lineEdit->setWhatsThis(tr("Enter new time value"));
	}
	newTimeDialogUi->lineEdit->setFocus(Qt::PopupFocusReason);
	newTimeDialog->exec();
}

void Timer::showSetNameDialog()
{
	if (!newNameDialog) {
		newNameDialog = new QDialog(this);
		newNameDialogUi->setupUi(newNameDialog);
		connect(newNameDialog, SIGNAL( accepted() ), this, SLOT(setNameFromDialog()) );
		newNameDialogUi->lineEdit->setWhatsThis(tr("Enter new name"));
	}
	newNameDialogUi->lineEdit->setText(name);
	newNameDialogUi->lineEdit->selectAll();
	newNameDialogUi->lineEdit->setFocus(Qt::PopupFocusReason);
	newNameDialog->exec();
}

void Timer::setTimeFromDialog()
{
	setTime(newTimeDialogUi->lineEdit->text());
}

void Timer::setNameFromDialog()
{
	setName(newNameDialogUi->lineEdit->text());
}

// void Timer::iconActivated(QSystemTrayIcon::ActivationReason reason)
// {
	// QString time;
	// switch (reason) {
		// case QSystemTrayIcon::Context:
		// // the context menu shows normally under this "reason"
		// //trayIcon->showMessage("Title", "Context");
		// break;
	// // Left click
	// case QSystemTrayIcon::Trigger:
		// // if (showSecs)
			// // time = QString("%1:%2:%3").arg(hours,2).arg(minutes,2,10,QChar('0')).arg(secs,2,10,QChar('0'));
		// // else
			// // time = QString("%1:%2").arg(hours,2).arg(minutes,2,10,QChar('0'));
		// // trayIcon->showMessage("Timer", time);
		// if (isHidden()) {
			// show();
		// }else{
			// hide();
		// }
		// break;
	// case QSystemTrayIcon::DoubleClick:
		// //trayIcon->showMessage("Title", "DoubleClick");
		// break;
	// case QSystemTrayIcon::MiddleClick:
		// //trayIcon->showMessage("Title", "MiddleClick");
		// break;
	// default:
		// ;
	// }
// }

void Timer::setTime(const QString &val)
{
	// validate the input value using a regex.
	// This will match anything other than numbers and colons
	QRegExp rx("[^\\d:]");
	// If no match, the return value will be -1
	if (rx.indexIn(val) != -1) {
		QMessageBox::warning(this,"Timer","Invalid value");
		return;
	}
	if (_started) {
		if (! isVisible()) {
			show();
		}
		return;
	}
	
	QStringList list = val.split(":");
	switch(list.size()) {
		case 1:
			hours   = 0;
			minutes = list[0].toInt();
			secs    = 0;
			break;
		case 2:
			hours   = 0;
			minutes = list[0].toInt();
			secs    = list[1].toInt();
			break;
		case 3:
			hours   = list[0].toInt();
			minutes = list[1].toInt();
			secs    = list[2].toInt();
	}
	minutes += secs / 60;
	secs    %= 60;
	hours   += minutes / 60;
	minutes %= 60;
	
	// update display
	showTime(false);
	
	if (! isVisible()) {
		//show();
		// go ahead and start counting down if called from tray icon:
		start();
	}
	
}

void Timer::setName(const QString &val)
{
	name = val;
	// setWindowTitle(val);
	ui->groupBox->setTitle(val);
	showTime(false);
}

// void Timer::messageClicked()
// {
	// trayIcon->setIcon(*greyIcon);
// }

void Timer::setCountUp(bool b)
{
	countUp = b;
	actionCountUp->setChecked(b);
}

// void Timer::resetHourSlider()
// {
	// ui->hourSlider->setValue(0);
// }

// void Timer::resetMinuteSlider()
// {
	// ui->minuteSlider->setValue(0);
// }

// void Timer::hourSliderMoved(int val)
// {
	// hours += val;
	// off=false;
	// showTime();
// }

// void Timer::on_pushButton_clicked()
// {
   // if (!_started) {
      // randomStopTime();
      // time->start();
      // connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
      // _started = true;
      // ui->pushButton->setText("Stop");
      // return;
   // }
   // else{
      // disconnect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
      // _started = false;
      // ui->pushButton->setText("Start");
      // checkResult();
   // }
// }

// void Timer::randomStopTime()
// {
   // targetSecs  = rand() % 10;
   // targetKsecs = (rand() % 1000) / 10;
   // ui->targetNumber->display(QString("%1:%2").arg(targetSecs,2).arg(targetKsecs,2));
   // //qDebug() << targetSecs << targetKsecs;
// }

// void Timer::checkResult()
// {
   // if (stopSecs == targetSecs && abs(targetKsecs - stopKsecs) < 10) {
      // QMessageBox::information(this, "STP", "Winner!");
   // }else{
      // QMessageBox::information(this, "STP", "meh");
   // }
// }
