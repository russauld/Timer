// Qt Timer application.
// Written by Russell Auld <russ@russauld.com>
//
// Class defintion for a single Timer object.
//
#ifndef TIMER_HXX
#define TIMER_HXX

#include <QWidget>
#include <QSignalMapper>
#include <QTimer>

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
		int getId();
		static const unsigned int  h = 180;
		static const unsigned int  w = 205;
		QString getName(void) const;
		bool getCountUp(void) const;
		bool getShowSeconds(void) const;
		bool getShowProgressBar(void) const;
		bool running(void) const;
		
	public slots:
		void stop();
		void showSeconds(bool);
		void showProgressBar(bool);
		void setName(const QString &);
		void setCountUp(bool);
		void stopReset();
		
	protected:
		void contextMenuEvent ( QContextMenuEvent * event );
		
	private slots:
		void updateTime();
		void showTime(void);
		void start();
		void timeCtrlClicked(int);
		void setTime(const QString &);
		void showSetTimeDialog();
		void setTimeFromDialog();
		void showSetNameDialog();
		void setNameFromDialog();
		void closeRequest();
		
	signals:
		void closeMe(int);
		void timesUp(QString);
		void started(int);
		void wasReset(int);
		void nameChanged(int);
		
	private:
		QString name;
		int id;
		QTimer *timer;
		QSignalMapper *signalMapper;
		Ui::Timer *ui;
		Ui::SetValueDialog *newTimeDialogUi;
		Ui::SetValueDialog *newNameDialogUi;
		bool _started;
		bool showSecs;
		bool showBar;
		bool countUp;
		int  secs;
		int  minutes;
		int  hours;
		bool off; //TODO: Review the use of this. Seems irrelevant - maybe related to the blinky colons
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
