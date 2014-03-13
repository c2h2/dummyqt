#ifndef TRAINGUI_H
#define TRAINGUI_H

#include <QtGui/QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QTabWidget>
#include <QtWebKit/QWebView>

class ScrollWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
public:
    explicit ScrollWidget(QWidget *parent = 0);
    ~ScrollWidget();
    void setText(const QString &newText);
    QString text() const { return myText; }
    QSize sizeHint() const;
protected:
     void paintEvent(QPaintEvent *event);
     void timerEvent(QTimerEvent *event);
     void showEvent(QShowEvent *event);
     void hideEvent(QHideEvent *event);
private:
     QString myText;
     int offset;
     int myTimerId;
};
class QCustom: public QTabWidget
{
public:
	enum
	{
		TAB_PAGE_STATION,
		TAB_PAGE_MONITOR,
		TAB_PAGE_BROADCAST,
		TAB_PAGE_MOVIE,
		TAB_PAGE_SYSTEM,
	};
public:
	int     tabpage;
	explicit QCustom(QWidget *parent = 0);
	~QCustom();
};

class TrainGUI : public QWidget
{
	Q_OBJECT
public:
	QWidget *gridLayoutWidget;
	QGridLayout *gridLayout;
	QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_bottom;
	QPushButton *broadcast;
	QPushButton *monitor;
	QPushButton *movie;
	QPushButton *station;
    QLabel      *system_bottom;
    QLabel      *system_status;
    QLabel      *system_time;
	//QPushButton *status;
	QPushButton *system;
	QCustom *tabWidget;
	QWebView *webView_0_1;
	QWebView *webView_0_2;
	QWebView *webView_0_3;
	QWebView *webView_0_4;
    ScrollWidget *scrollWidget;
    int      timer_id;
public slots:
	void OnBroadCast();
	void OnMonitor();
	void OnMonvie();
	void OnStation();
	void OnSystem();
	void OnChanged(int index);
protected:
     void timerEvent(QTimerEvent *event);
public:
	TrainGUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TrainGUI();
    void InitBtns(int excpet);
    void SetBtnSelected(int pressed);

	void setupUi(QWidget *TrainGUIClass)
	{
		if (TrainGUIClass->objectName().isEmpty())
			TrainGUIClass->setObjectName(QString::fromUtf8("TrainGUIClass"));
		gridLayoutWidget = new QWidget(TrainGUIClass);
		gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
		gridLayoutWidget->setGeometry(QRect(0, 0, TrainGUIClass->geometry().width(), TrainGUIClass->geometry().height()));
		gridLayout = new QGridLayout(gridLayoutWidget);
		gridLayout->setSpacing(6);
		gridLayout->setContentsMargins(11, 11, 11, 11);
		gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
		gridLayout->setContentsMargins(0, 0, 0, 0);
		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setSpacing(6);
		horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        station = new QPushButton(gridLayoutWidget);
        station->setObjectName(QString::fromUtf8("station"));

        horizontalLayout->addWidget(station);

		broadcast = new QPushButton(gridLayoutWidget);
        monitor = new QPushButton(gridLayoutWidget);
        monitor->setObjectName(QString::fromUtf8("monitor"));

        horizontalLayout->addWidget(monitor);

        //QIcon icon1("Resources/11.png");
        //broadcast->setIcon(icon1);

        broadcast->setObjectName(QString::fromUtf8("broadcast"));

		horizontalLayout->addWidget(broadcast);


		movie = new QPushButton(gridLayoutWidget);
		movie->setObjectName(QString::fromUtf8("movie"));

		horizontalLayout->addWidget(movie);

		//status = new QPushButton(gridLayoutWidget);
		//status->setObjectName(QString::fromUtf8("status"));

		//horizontalLayout->addWidget(status);

		system = new QPushButton(gridLayoutWidget);
		system->setObjectName(QString::fromUtf8("system"));

		horizontalLayout->addWidget(system);


		gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);
		tabWidget = new QCustom(gridLayoutWidget);
		tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
		tabWidget->setDocumentMode(false);
		tabWidget->setTabsClosable(false);
		tabWidget->setMovable(false);

		webView_0_1 = new QWebView();
		webView_0_1->setObjectName(QString::fromUtf8("webView_0_1"));
		tabWidget->addTab(webView_0_1, QString());
		webView_0_1->setUrl(QUrl("about:blank"));

		webView_0_2 = new QWebView();
		webView_0_2->setObjectName(QString::fromUtf8("webView_0_2"));
		tabWidget->addTab(webView_0_2, QString());
		webView_0_2->setUrl(QUrl("about:blank"));

		webView_0_3 = new QWebView();
		webView_0_3->setObjectName(QString::fromUtf8("webView_0_3"));
		tabWidget->addTab(webView_0_3, QString());
		webView_0_3->setUrl(QUrl("about:blank"));

		webView_0_4 = new QWebView();
		webView_0_4->setObjectName(QString::fromUtf8("webView_0_4"));
		tabWidget->addTab(webView_0_4, QString());
		webView_0_4->setUrl(QUrl("about:blank"));

		gridLayout->addWidget(tabWidget, 1, 0, 1, 1);

        horizontalLayout_bottom = new QHBoxLayout();
        horizontalLayout_bottom->setSpacing(6);
        horizontalLayout_bottom->setObjectName(QString::fromUtf8("horizontalLayout_bottom"));

        scrollWidget = new ScrollWidget(gridLayoutWidget);
        scrollWidget->setObjectName(QString::fromUtf8("scrollWidget"));
        horizontalLayout_bottom->addWidget(scrollWidget);
        system_bottom = new QLabel(gridLayoutWidget);
        system_bottom->setObjectName(QString::fromUtf8("system_bottom"));
        horizontalLayout_bottom->addWidget(system_bottom);
        system_status = new QLabel(gridLayoutWidget);
        system_status->setObjectName(QString::fromUtf8("system_status"));
        horizontalLayout_bottom->addWidget(system_status);
        system_time = new QLabel(gridLayoutWidget);
        system_time->setObjectName(QString::fromUtf8("system_time"));
        horizontalLayout_bottom->addWidget(system_time);

        gridLayout->addLayout(horizontalLayout_bottom, 2, 0, 1, 1);


		retranslateUi(TrainGUIClass);
		QObject::connect(broadcast, SIGNAL(clicked()), TrainGUIClass, SLOT(OnBroadCast()));
		QObject::connect(monitor, SIGNAL(clicked()), TrainGUIClass, SLOT(OnMonitor()));
		QObject::connect(movie, SIGNAL(clicked()), TrainGUIClass, SLOT(OnMonvie()));
		QObject::connect(station, SIGNAL(clicked()), TrainGUIClass, SLOT(OnStation()));
		QObject::connect(system, SIGNAL(clicked()), TrainGUIClass, SLOT(OnSystem()));
		QObject::connect(tabWidget, SIGNAL(currentChanged(int)), TrainGUIClass, SLOT(OnChanged(int)));
		QMetaObject::connectSlotsByName(TrainGUIClass);
	} // setupUi

	void retranslateUi(QWidget *TrainGUIClass)
	{
        TrainGUIClass->setWindowTitle(QObject::tr("TrainGUI"));//QApplication::translate("TrainGUIClass", "TrainGUI", 0, QApplication::UnicodeUTF8));
        station->setText(QApplication::translate("TrainGUIClass", "报站系统", 0, QApplication::UnicodeUTF8));
        monitor->setText(QApplication::translate("TrainGUIClass", "视频监控", 0, QApplication::UnicodeUTF8));
        broadcast->setText(QApplication::translate("TrainGUIClass", "广播对讲", 0, QApplication::UnicodeUTF8));
        movie->setText(QApplication::translate("TrainGUIClass", "娱乐视频", 0, QApplication::UnicodeUTF8));
        system->setText(QApplication::translate("TrainGUIClass", "系统设置", 0, QApplication::UnicodeUTF8));
        system_bottom->setText(QApplication::translate("TrainGUIClass", "SYSTEM:", 0, QApplication::UnicodeUTF8));
        system_status->setText(QApplication::translate("TrainGUIClass", " OK ", 0, QApplication::UnicodeUTF8));
        system_time->setText(QApplication::translate("TrainGUIClass", "", 0, QApplication::UnicodeUTF8));

		tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "\346\211\213\345\212\250\346\212\245\347\253\231", 0, QApplication::UnicodeUTF8));
		tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "\350\257\255\351\237\263\345\271\277\346\222\255", 0, QApplication::UnicodeUTF8));
		tabWidget->setTabText(tabWidget->indexOf(webView_0_3), QApplication::translate("TrainGUIClass", "\346\217\220\347\244\272\345\255\227\345\271\225", 0, QApplication::UnicodeUTF8));
		tabWidget->setTabText(tabWidget->indexOf(webView_0_4), QApplication::translate("TrainGUIClass", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
	} // retranslateUi
};

#endif // TRAINGUI_H
