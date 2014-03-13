#include "traingui.h"
#include <QtGui/QDesktopWidget>
#include <QtCore/QDateTime>
ScrollWidget::ScrollWidget(QWidget *parent):QWidget(parent)
{
    offset = 0;
    myTimerId = 0;
}


ScrollWidget::~ScrollWidget()
{
}


void ScrollWidget::setText(const QString &newText)
{
     myText = newText;
     update();
     updateGeometry();
}


QSize ScrollWidget::sizeHint() const
{
     return fontMetrics().size(0, text());
}


void ScrollWidget::paintEvent(QPaintEvent * )
{
     QPainter painter(this);
     int textWidth = fontMetrics().width(text());
     if (textWidth < 1)
         return;
     int x = -offset;
     while (x < width()) {
         painter.drawText(x, 0, textWidth, height(),
                         Qt::AlignRight | Qt::AlignVCenter, text());
         x += textWidth;
     }
}


void ScrollWidget::showEvent(QShowEvent * )
{
     myTimerId = startTimer(30);
}


void ScrollWidget::timerEvent(QTimerEvent *event)

{
     if (event->timerId() == myTimerId) {
         ++offset;
         if (offset >= fontMetrics().width(text()))
             offset = 0;
         scroll(-1, 0);
     } else {
         QWidget::timerEvent(event);
     }
}


void ScrollWidget::hideEvent(QHideEvent * )
{
     killTimer(myTimerId);
     myTimerId = 0;
}

QCustom::QCustom(QWidget *parent): QTabWidget(parent)
{
	//tabBar()->setStyleSheet("background-color:rgb(170, 0, 255);font:bold;font-size:24px;selection-color:rgb(155,200,33);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-attachment: fixed;background-attachment: fixed;background-clip: padding");
}

QCustom::~QCustom()
{

}

TrainGUI::TrainGUI(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
    setWindowFlags(Qt::Popup|Qt::Dialog|Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect cRect = desktopWidget->screenGeometry();
    setStyleSheet("color:white;background:black;font:bold;font-size:24px;");
    //resize(cRect.width(),cRect.height());
    resize(1024,768);
	setupUi(this);
	tabWidget->tabpage = QCustom::TAB_PAGE_STATION;
    tabWidget->setStyleSheet("QTabWidget::pane{color:white;border: 2px;border-color:white;border:2px groove gray;}"
            "QTabWidget::tab-bar{color:white;alignment:left;border:8px;border-color:white;}"
            "QTabWidget::tab-bar{color:white;border:2px groove gray;border-radius:10px;padding:2px 4px;}"
            "QTabBar::tab{color:white;border:2px groove gray;border-radius:10px;padding:2px 4px;}"
            "QTabBar::tab{color:white;background:red;border:8px;border-color:white; min-width:20ex; min-height:5ex;}"
            "QTabBar::tab:hover{color:white;background:green;}"
            "QTabBar::tab:selected{color:white;background:darkblue;}");
    scrollWidget->setStyleSheet("background-color:black;color:white;font:bold;font-size:24px;");
    webView_0_1->setStyleSheet("background-color:black;font:bold;font-size:24px;selection-color:rgb(155,200,33);background-repeat: repeat-xy;background-position: center;");
    webView_0_2->setStyleSheet("background-color:black;font:bold;font-size:24px;selection-color:rgb(155,200,33);background-repeat: repeat-xy;background-position: center;");
    webView_0_3->setStyleSheet("background-color:black;font:bold;font-size:24px;selection-color:rgb(155,200,33);background-repeat: repeat-xy;background-position: center;");
    webView_0_4->setStyleSheet("background-color:black;font:bold;font-size:24px;selection-color:rgb(155,200,33);background-repeat: repeat-xy;background-position: center;");
    system_status->setStyleSheet("color:darkgreen");
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    system_time->setText(str);//在标签上显示时间
    InitBtns(QCustom::TAB_PAGE_STATION);
    SetBtnSelected(QCustom::TAB_PAGE_STATION);
    tabWidget->setCurrentIndex(0);
	gridLayout->setRowStretch(0,1);
    gridLayout->setRowStretch(1,19);
	gridLayout->setRowStretch(2,1);
    scrollWidget->setText(QApplication::translate("TrainGUIClass", "各位旅客，上海体育馆就要到了，请要下车的乘客做好准备。\t We are arriving at Shanghai Stadium soon.\t\t", 0, QApplication::UnicodeUTF8));
    OnChanged(0);
    timer_id = startTimer(1000);
}

void TrainGUI::timerEvent(QTimerEvent *event)

{
     if (event->timerId() == timer_id) {
         QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
         QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
         system_time->setText(str);//在标签上显示时间
     } else {
         QWidget::timerEvent(event);
     }
}

void TrainGUI::InitBtns(int excpet)
{
    if ( excpet != QCustom::TAB_PAGE_STATION  )
        station->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:red;}"
                                 "QPushButton:hover{border-color:green; color:black;background:green;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
    if ( excpet != QCustom::TAB_PAGE_BROADCAST  )
        broadcast->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                 "QPushButton{border:1px solid lightgray; background:red;}"
                                 "QPushButton:hover{border-color:green; color:black;background:green;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
    if ( excpet != QCustom::TAB_PAGE_MONITOR  )
        monitor->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:red;}"
                                 "QPushButton:hover{border-color:green; color:black;background:green;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
    if ( excpet != QCustom::TAB_PAGE_MOVIE  )
        movie->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:red;}"
                                 "QPushButton:hover{border-color:green; color:black;background:green;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
   if ( excpet != QCustom::TAB_PAGE_SYSTEM  )
        system->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:red;}"
                                 "QPushButton:hover{border-color:green; color:black;background:green;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");

}

void TrainGUI::SetBtnSelected(int pressed)
{
    if ( pressed == QCustom::TAB_PAGE_STATION  )
        station->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:darkblue;}"
                                 "QPushButton:hover{border-color:green; color:black;background:darkblue;}");
    if ( pressed == QCustom::TAB_PAGE_BROADCAST  )
        broadcast->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                 "QPushButton{border:1px solid lightgray; background:darkblue;}"
                                 "QPushButton:hover{border-color:green; color:black;background:darkblue;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
    if ( pressed == QCustom::TAB_PAGE_MONITOR  )
        monitor->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:darkblue;}"
                                 "QPushButton:hover{border-color:green; color:black;background:darkblue;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
    if ( pressed == QCustom::TAB_PAGE_MOVIE  )
        movie->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:darkblue;}"
                                 "QPushButton:hover{border-color:green; color:black;background:darkblue;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
   if ( pressed == QCustom::TAB_PAGE_SYSTEM  )
        system->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                "QPushButton{border:1px solid lightgray; background:darkblue;}"
                                 "QPushButton:hover{border-color:green; color:black;background:darkblue;}"
                                 "QPushButton:pressed{border-color:green; color:black;background:darkblue;}");
}

void TrainGUI::OnBroadCast()
{
	if ( tabWidget->tabpage == QCustom::TAB_PAGE_BROADCAST ) 
		return;

    InitBtns(QCustom::TAB_PAGE_BROADCAST);
    SetBtnSelected(QCustom::TAB_PAGE_BROADCAST);
    tabWidget->clear();
    qDebug("OnBroadCast");
    tabWidget->addTab(webView_0_1, QString());
	webView_0_1->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_2, QString());
	webView_0_2->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_3, QString());
	webView_0_3->setUrl(QUrl("about:blank"));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "实时会话", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "司机对讲台1", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_3), QApplication::translate("TrainGUIClass", "司机对讲台2", 0, QApplication::UnicodeUTF8));
    tabWidget->tabpage = QCustom::TAB_PAGE_BROADCAST;
    OnChanged(0);
}

void TrainGUI::OnMonitor()
{
	if ( tabWidget->tabpage == QCustom::TAB_PAGE_MONITOR ) 
		return;

    InitBtns(QCustom::TAB_PAGE_MONITOR);
    SetBtnSelected(QCustom::TAB_PAGE_MONITOR);
    tabWidget->clear();
    qDebug("OnMonitor");
	tabWidget->addTab(webView_0_1, QString());
	webView_0_1->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_2, QString());
	webView_0_2->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_3, QString());
	webView_0_3->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_4, QString());
	webView_0_4->setUrl(QUrl("about:blank"));
    tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "实时视频", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "监控管理", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_3), QApplication::translate("TrainGUIClass", "开始轮循", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_4), QApplication::translate("TrainGUIClass", "视频回放", 0, QApplication::UnicodeUTF8));
	tabWidget->tabpage = QCustom::TAB_PAGE_MONITOR;
    OnChanged(0);
}

void TrainGUI::OnMonvie()
{
	if ( tabWidget->tabpage == QCustom::TAB_PAGE_MOVIE ) 
		return;

    InitBtns(QCustom::TAB_PAGE_MOVIE);
    SetBtnSelected(QCustom::TAB_PAGE_MOVIE);
    tabWidget->clear();
    qDebug("OnBroadCast");
	tabWidget->addTab(webView_0_1, QString());
	webView_0_1->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_2, QString());
	webView_0_2->setUrl(QUrl("about:blank"));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "视频广播", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "视频预览", 0, QApplication::UnicodeUTF8));
	tabWidget->tabpage = QCustom::TAB_PAGE_MOVIE;
    OnChanged(0);
}

void TrainGUI::OnStation()
{
	if ( tabWidget->tabpage == QCustom::TAB_PAGE_STATION ) 
		return;
    InitBtns(QCustom::TAB_PAGE_STATION);
    SetBtnSelected(QCustom::TAB_PAGE_STATION);
    tabWidget->clear();
    qDebug("OnStation");
	tabWidget->addTab(webView_0_1, QString());
	webView_0_1->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_2, QString());
	webView_0_2->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_3, QString());
	webView_0_3->setUrl(QUrl("about:blank"));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "手动报站", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "语音广播", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_3), QApplication::translate("TrainGUIClass", "提示字幕", 0, QApplication::UnicodeUTF8));
	tabWidget->tabpage = QCustom::TAB_PAGE_STATION;
    OnChanged(0);
}

void TrainGUI::OnChanged(int index)
{

	switch ( tabWidget->tabpage )
	{
	case QCustom::TAB_PAGE_STATION:
		{
           qDebug("TAB_PAGE_STATION - %d\n",index);
			switch ( index )
			{
			case 0:
                webView_0_1->load(QUrl("http://192.168.11.8:81/current_route/show_for_qt"));
                //webView_0_1->load(QUrl("http://www.sina.com.cn"));
				break;
			case 1:
				webView_0_2->load(QUrl("http://192.168.11.8:81/voice_packs/index_for_qt"));
				break;
			case 2:
				webView_0_3->load(QUrl("http://192.168.11.8:81/tickers/index_for_qt"));
				break;
			default:
				break;
			}
		}
		break;
	case QCustom::TAB_PAGE_MONITOR:
		{
            qDebug("TAB_PAGE_MONITOR - %d\n",index);
			switch ( index )
			{
			case 0:
			case 1:
			case 2:
			case 3:
			default:
				break;
			}
		}
		break;
	case QCustom::TAB_PAGE_BROADCAST:
		{
            qDebug("TAB_PAGE_BROADCAST - %d\n",index);
			switch ( index )
			{
			case 0:
				webView_0_1->load(QUrl("http://192.168.11.8/call/index_for_qt"));
                break;
			case 1:
				webView_0_2->load(QUrl("http://192.168.11.10/login_without_account"));
                break;
			case 2:
				webView_0_3->load(QUrl("http://192.168.11.15/login_without_account"));
                break;
			default:
				break;
			}
		}
		break;
	case QCustom::TAB_PAGE_MOVIE:
		{
            qDebug("TAB_PAGE_MOVIE - %d\n",index);
			switch ( index )
			{
			case 0:
				webView_0_1->load(QUrl("about:blank"));
				break;
			case 1:
				webView_0_2->load(QUrl("about:blank"));
				break;
			default:
				break;
			}
		}
		break;
	case QCustom::TAB_PAGE_SYSTEM:
		{
            qDebug("TAB_PAGE_SYSTEM - %d\n",index);
			switch ( index )
			{
			case 0:
				webView_0_1->load(QUrl("http://192.168.11.8:81/device_states/index_for_qt"));
                break;
			case 1:
				webView_0_2->load(QUrl("about:blank"));
                break;
			case 2:
				webView_0_3->load(QUrl("about:blank"));
				break;
			default:
				break;
			}
		}
        break;
	default:
		break;
	}
}

void TrainGUI::OnSystem()
{
	if ( tabWidget->tabpage == QCustom::TAB_PAGE_SYSTEM ) 
		return;

    InitBtns(QCustom::TAB_PAGE_SYSTEM);
    SetBtnSelected(QCustom::TAB_PAGE_SYSTEM);
    tabWidget->clear();
    qDebug("OnSystem");
	tabWidget->addTab(webView_0_1, QString());
	webView_0_1->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_2, QString());
	webView_0_2->setUrl(QUrl("about:blank"));
	tabWidget->addTab(webView_0_3, QString());
	webView_0_3->setUrl(QUrl("about:blank"));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_1), QApplication::translate("TrainGUIClass", "设备状态", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_2), QApplication::translate("TrainGUIClass", "网络配置", 0, QApplication::UnicodeUTF8));
	tabWidget->setTabText(tabWidget->indexOf(webView_0_3), QApplication::translate("TrainGUIClass", "关闭系统", 0, QApplication::UnicodeUTF8));
	tabWidget->tabpage = QCustom::TAB_PAGE_SYSTEM;
    OnChanged(0);
}

TrainGUI::~TrainGUI()
{
    killTimer(timer_id);
}
