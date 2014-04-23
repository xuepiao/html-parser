///////////////////////////////////////////////////////////////////////////////////////////////////////

//name:   imdb parse
//author: ren meng
//data:   from 2014-3-7 to 2014-3-12
//introduction:   uses only for fixed-format URL.Such as beging with http://www.imdb.cn/title/tt******

/////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtGui/QApplication>
#include "mainwindow.h"
#include<QTextCodec>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    //QTextCodec *codec= QTextCodec::codecForName("utf-8");

    QApplication::addLibraryPath("./plugins");

    QTextCodec*codec= QTextCodec::codecForName("GB2312");

    QTextCodec::setCodecForLocale(codec);

    QTextCodec::setCodecForCStrings(codec);

    QTextCodec::setCodecForTr(codec);



    //´°¿ÚÎ»ÖÃ

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;

    int screenHeight, height;

    int x, y;

    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen

    screenHeight = desktop->height(); // get height of screen

    windowSize = w.size(); // size of our application window

    width = windowSize.width();

    height = windowSize.height();

    x = (screenWidth - width) / 2;

    y = (screenHeight - height) / 2;

    y -= 50;

    w.move(x, y );



    w.show();

    return a.exec();
}
