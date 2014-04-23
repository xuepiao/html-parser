


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

    flag=1;     //���Ʒ���ҳ�����

    content = new QString();

    content2 = new QString();

    mgr = new QNetworkAccessManager(this);

    //�ź���۹���

    connect(mgr,SIGNAL(finished(QNetworkReply*)),this, SLOT(query(QNetworkReply*)));

    addrEdit = new QLineEdit(this);

    connect(addrEdit, SIGNAL(returnPressed()), this, SLOT(changeLocation()));

    //���ڲ���

    ui->mainToolBar->addWidget(addrEdit);
}



MainWindow::~MainWindow()
{
    delete ui;
}


//·���ı�

void MainWindow::changeLocation()

{

    QUrl url = QUrl(addrEdit->text());

    content->clear();

    content2->clear();

    mgr->get(QNetworkRequest(url));

}



//��ѯ

void MainWindow::query(QNetworkReply *reply)
{  

    //������Ч
    if(reply->error())
    {
        content->append("\nERROR,LOAD PAGE FAILED,PLEASE TRY AGAIN OR DIAGNOSE!");

        ui->contentEdit->setText(*content);

        ui->textEdit->setText(*content2);

        return;
    }


    //���ʻ�����Ϣҳ��
    if(flag)
    {
        flag=0;

        QWebPage page;

        QWebFrame *frame = page.mainFrame();

        QByteArray html= reply->peek(reply->size());

        frame->setContent(html);



        QWebElement doc= frame->documentElement();      //���ڵ�

        QWebElement imdbleft=doc.findFirst("#imdbleft");

        QWebElement imdbleft2=imdbleft.findFirst("#imdbleft2");

        QWebElement h1=imdbleft2.findFirst("h1");

        content->append(h1.toPlainText());

        ui->contentEdit->setText(*content);

        content->append("\n");

        ui->contentEdit->setText(*content);

        QWebElement imdbleft3=imdbleft.findFirst("#imdbleft3");

        QWebElementCollection trs=imdbleft3.findAll("tr");


        //���������Ϣ����

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


        //����url�ϳ�
        QWebElement span=imdbleft2.findFirst(".act");

        QWebElement a=span.findFirst("a");

        QUrl baseUrl = QUrl("http://www.imdb.cn");

        QUrl relativeUrl(a.attribute("href"));

        QUrl absoluteUrl = baseUrl.resolved(relativeUrl);

        mgr->get(QNetworkRequest(absoluteUrl));

    }



    //����Ӱ��ҳ��
    else
    {
        flag=1;

        QWebPage page2;

        QWebFrame *frame2 = page2.mainFrame();

        QByteArray html2= reply->peek(reply->size());

        frame2->setContent(html2);



        QWebElement doc2= frame2->documentElement();

        QWebElementCollection ctshs=doc2.findAll(".ctsh");


        //��Ӱ������
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



    }//���else


}//query

