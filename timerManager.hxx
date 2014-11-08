// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#ifndef TIMERMANAGER_HXX
#define TIMERMANAGER_HXX

#include <QtGui/QMainWindow>
// #include <QLCDNumber>
// #include <QTimer>
#include <QSignalMapper>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QApplication>
#include <QList>

#include "timer.hxx"

// namespace Ui
// {
	// class Timer;
	// class SetValueDialog;
// }

class TimerManager : public QMainWindow
{
	Q_OBJECT

	public:
		TimerManager(QWidget *parent = 0);
		~TimerManager();
		
	protected:
		void closeEvent(QCloseEvent *event);
		
	private slots:
		// void updateTime();
		// void showTime(bool toggle_colon);
		// //void showTimeWithToggle();
		// void start();
		// void stop();
		// void timeCtrlClicked(int);
		// void showSeconds(bool);
		// void showProgressBar(bool);
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		// void setTime(const QString &);
		// void setName(const QString &);
		// void showSetTimeDialog();
		// void setTimeFromDialog();
		// void showSetNameDialog();
		// void setNameFromDialog();
		void messageClicked();
		// void setCountUp(bool);
		// //void resetMinuteSlider();
		// //void hourSliderMoved(int);
		void newTimer();
		void closeTimer(int);
		
	//public signals:
		//	void timesUp();
		
	private:
		// QString name;
		// QTimer *timer;
		//QTimer *countdownTimer;
		QSignalMapper *signalMapper;
		QSystemTrayIcon *trayIcon;
		QMenu           * trayMenu;
		QIcon  *redIcon;
		QIcon  *greyIcon;
		// Ui::Timer *ui;
		// Ui::SetValueDialog *newTimeDialogUi;
		// Ui::SetValueDialog *newNameDialogUi;
		// bool started;
		// bool showSecs;
		// bool showBar;
		// bool countUp;
		// int  secs;
		// int  minutes;
		// int  hours;
		// bool off;
		void timesUp();
		bool firstHide;
		// QAction *fiveMinAction;
		// QAction *tenMinAction;
		// QAction *fifteenMinAction;
		// QAction *halfHourAction;
		// QAction *oneHourAction;
		QAction *quitAction;
		QAction *newAct;
		QAction *radioAction;
		QMenu *fileMenu;
		// QDialog *newTimeDialog;
		// QDialog *newNameDialog;
		QWidget *centralWidget;
		QGridLayout *gridLayout;
		QList< Timer* > timerList;
};

#endif // TIMERMANAGER_HXX
