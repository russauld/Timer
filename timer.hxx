// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>

#ifndef TIMER_HXX
#define TIMER_HXX

#include <QWidget>
#include <QSignalMapper>
#include <QTimer>
// #include <QSystemTrayIcon>
// #include <QCloseEvent>

namespace Ui
{
	class Timer;
	class SetValueDialog;
}

class Timer : public QWidget
{
	Q_OBJECT

	public:
		Timer(QWidget *parent, int id);
		~Timer();
		
	protected:
		// void closeEvent(QCloseEvent *event);
		void contextMenuEvent ( QContextMenuEvent * event );
		
	private slots:
		void updateTime();
		void showTime(bool toggle_colon);
		//void showTimeWithToggle();
		void start();
		void stop();
		void timeCtrlClicked(int);
		void showSeconds(bool);
		void showProgressBar(bool);
		// void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void setTime(const QString &);
		void setName(const QString &);
		void showSetTimeDialog();
		void setTimeFromDialog();
		void showSetNameDialog();
		void setNameFromDialog();
		// void messageClicked();
		void setCountUp(bool);
		//void resetMinuteSlider();
		//void hourSliderMoved(int);
		void closeRequest();
		
	signals:
		void closeMe(int);
		
	private:
		QString name;
		int id;
		QTimer *timer;
		// //QTimer *countdownTimer;
		QSignalMapper *signalMapper;
		// QSystemTrayIcon *trayIcon;
		// QMenu           * trayMenu;
		// QIcon  *redIcon;
		// QIcon  *greyIcon;
		Ui::Timer *ui;
		Ui::SetValueDialog *newTimeDialogUi;
		Ui::SetValueDialog *newNameDialogUi;
		bool started;
		bool showSecs;
		bool showBar;
		bool countUp;
		int  secs;
		int  minutes;
		int  hours;
		bool off; //TODO: Review the use of this. Seems irrelevant - maybe related to the blinky colons
		// void timesUp();
		// bool firstHide;
		QAction *fiveMinAction;
		QAction *tenMinAction;
		QAction *fifteenMinAction;
		QAction *halfHourAction;
		QAction *oneHourAction;
		QAction *closeAction;
		QDialog *newTimeDialog;
		QDialog *newNameDialog;
		QAction *actionShowSeconds;
		QAction *actionShowProgressBar;
		QAction *actionSetTime;
		QAction *actionSetName;
		QAction *actionCountUp;
};

#endif // TIMER_HXX
