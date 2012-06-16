#ifndef TIMER_HXX
#define TIMER_HXX

#include <QtGui/QMainWindow>
#include <QLCDNumber>
//#include <QTime>
#include <QTimer>
#include <QSignalMapper>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui
{
	class Timer;
	class SetValueDialog;
}

class Timer : public QMainWindow
{
	Q_OBJECT

	public:
		Timer(QWidget *parent = 0);
		~Timer();
		
	protected:
		void closeEvent(QCloseEvent *event);
		
	private slots:
		void updateTime();
		void showTime(bool toggle_colon);
		//void showTimeWithToggle();
		void start();
		void stop();
		void timeCtrlClicked(int);
		void showSeconds(bool);
		void showProgressBar(bool);
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void setTime(const QString &);
		void setName(const QString &);
		void showSetTimeDialog();
		void setTimeFromDialog();
		void showSetNameDialog();
		void setNameFromDialog();
		void messageClicked();
		//void resetMinuteSlider();
		//void hourSliderMoved(int);
		
	//public signals:
		//	void timesUp();
		
	private:
		QString name;
		QTimer *timer;
		//QTimer *countdownTimer;
		QSignalMapper *signalMapper;
		QSystemTrayIcon *trayIcon;
		QMenu           * trayMenu;
		QIcon  *redIcon;
		QIcon  *greyIcon;
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
		bool off;
		void timesUp();
		bool firstHide;
		QAction *fiveMinAction;
		QAction *tenMinAction;
		QAction *fifteenMinAction;
		QAction *halfHourAction;
		QAction *oneHourAction;
		QAction *quitAction;
		QDialog *newTimeDialog;
		QDialog *newNameDialog;
};

#endif // TIMER_HXX
