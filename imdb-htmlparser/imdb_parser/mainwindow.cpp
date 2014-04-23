


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKit>
#include <QString>
#include <QNetworkReply>
#include <QByteArray>
#include <QWebElement>
#include <QWebElementCollection>
#include <QUrl>
#include <QWidget>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag=1;     //控制访问页面次序

    content = new QString();

    content2 = new QString();

    mgr = new QNetworkAccessManager(this);

    //信号与槽关联

    connect(mgr,SIGNAL(finished(QNetworkReply*)),this, SLOT(query(QNetworkReply*)));

    addrEdit = new QLineEdit(this);

    connect(addrEdit, SIGNAL(returnPressed()), this, SLOT(changeLocation()));

    //窗口部件

    ui->mainToolBar->addWidget(addrEdit);
}



MainWindow::~MainWindow()
{
    delete ui;
}


//路径改变

void MainWindow::changeLocation()

{

    QUrl url = QUrl(addrEdit->text());

    content->clear();

    content2->clear();

    mgr->get(QNetworkRequest(url));

}



//查询

void MainWindow::query(QNetworkReply *reply)
{  

    //访问无效
    if(reply->error())
    {
        content->append("\nERROR,LOAD PAGE FAILED,PLEASE TRY AGAIN OR DIAGNOSE!");

        ui->contentEdit->setText(*content);

        ui->textEdit->setText(*content2);

        return;
    }


    //访问基本信息页面
    if(flag)
    {
        flag=0;

        QWebPage page;

        QWebFrame *frame = page.mainFrame();

        QByteArray html= reply->peek(reply->size());

        frame->setContent(html);



        QWebElement doc= frame->documentElement();      //跟节点

        QWebElement imdbleft=doc.findFirst("#imdbleft");

        QWebElement imdbleft2=imdbleft.findFirst("#imdbleft2");

        QWebElement h1=imdbleft2.findFirst("h1");

        content->append(h1.toPlainText());

        ui->contentEdit->setText(*content);

        content->append("\n");

        ui->contentEdit->setText(*content);

        QWebElement imdbleft3=imdbleft.findFirst("#imdbleft3");

        QWebElementCollection trs=imdbleft3.findAll("tr");


        //具体多余信息处理

        QWebElementCollection tr7s=trs.at(8).findAll("a");

        tr7s.at(1).setPlainText("\t");

        QWebElementCollection tr8s=trs.at(8).findAll("a");

        tr8s.at(1).setPlainText("\t");

        QWebElement tr14=trs.at(14).findFirst("a");

        tr14.setPlainText("\t");

        QWebElement tr16=trs.at(16).findFirst("a");

        tr16.setPlainText("\t");



        //parser text
        for(int count=0;count<trs.count()-1;count++)
        {

            QWebElementCollection tds=trs.at(count).findAll("td");


            for(int count2=0;count2<tds.count();count2++)
            {
                content->append(tds.at(count2).toPlainText());

                ui->contentEdit->setText(*content);

                content->append("\n");

                ui->contentEdit->setText(*content);
            }

            content->append("\n");

            ui->contentEdit->setText(*content);
        }



        QWebElementCollection imdbjqbodys=imdbleft.findAll("#imdbjqbody");

        content->append(imdbjqbodys.at(0).toPlainText());

        ui->contentEdit->setText(*content);

        content->append("\n");

        ui->contentEdit->setText(*content);


        //链接url合成
        QWebElement span=imdbleft2.findFirst(".act");

        QWebElement a=span.findFirst("a");

        QUrl baseUrl = QUrl("http://www.imdb.cn");

        QUrl relativeUrl(a.attribute("href"));

        QUrl absoluteUrl = baseUrl.resolved(relativeUrl);

        mgr->get(QNetworkRequest(absoluteUrl));

    }



    //访问影评页面
    else
    {
        flag=1;

        QWebPage page2;

        QWebFrame *frame2 = page2.mainFrame();

        QByteArray html2= reply->peek(reply->size());

        frame2->setContent(html2);



        QWebElement doc2= frame2->documentElement();

        QWebElementCollection ctshs=doc2.findAll(".ctsh");


        //无影评内容
        if(!ctshs.count())
        {
            content2->append("\n\nNO COMMENTARY!");

            ui->textEdit->setText(*content2);
        }


        else
        {

            for(int count=0;count<ctshs.count();count++)
            {

                QWebElement span1=ctshs.at(count).findFirst(".pl");

                span1.setPlainText("\t");

                QWebElement a1=ctshs.at(count).findFirst("a");

                a1.setPlainText("\t");

                content2->append(ctshs.at(count).toPlainText());

                ui->textEdit->setText(*content2);

            }//for



        }//else



    }//外层else


}//query

