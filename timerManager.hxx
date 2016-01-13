// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#ifndef TIMERMANAGER_HXX
#define TIMERMANAGER_HXX

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QApplication>
#include <QList>

#include "timer.hxx"

class TimerManager : public QMainWindow
{
	Q_OBJECT

	public:
		TimerManager(QWidget *parent = 0);
		~TimerManager();
		
		enum LAYOUT { HORIZ=0, VERT, GRID };
		
	protected:
		void closeEvent(QCloseEvent *event);
		void resizeEvent(QResizeEvent *event);
		
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
		void setRadioBehavior(bool);
		void timerExpired(QString);
		void timerStarted(int);
		void timerReset(int);
		void timerRenamed(int);
		void debug();
		void resizeTimeout();
		void setLayoutType(int);
		void wrapItUp();
		void resetAll();
		
	//public signals:
		//	void timesUp();
		
	private:
		QSystemTrayIcon *trayIcon;
		QMenu           *trayMenu;
		QIcon  *redIcon;
		QIcon  *greyIcon;
		bool firstHide;
		bool radio;
		int nTimer;
		int resizeTimeoutVal;
		int layout;
		const int MAX_TIMERS = 10;
		QSignalMapper *signalMapper;
		QAction *quitAction;
		QAction *newAct;
		QAction *radioAction;
		QAction *debugAction;
		QAction *resetAllAction;
		QMenu   *fileMenu;
		QMenu   *optionMenu;
		QMenu   *layoutMenu;
		QActionGroup *layoutGroup;
		QAction *horizontalAction;
		QAction *verticalAction;
		QAction *gridAction;
		QWidget *centralWidget;
		QGridLayout *gridLayout;
		QList< Timer* > timerList;
		// QTimer *resizeTimer;
		void computeLayout(void);
		void writeSettings();
		void readSettings();
		void updateTrayMessage();

};

#endif // TIMERMANAGER_HXX
