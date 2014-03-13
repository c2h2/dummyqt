#include "traingui.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TrainGUI w;
    QFont font("Times",12,QFont::Normal,FALSE);
    a.setFont(font);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    /*QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());*/
	w.show();
    //w.showFullScreen();
	return a.exec();
}
