#include "checkandemail.h"

CheckAndEmail::CheckAndEmail(Setting *settings, QObject *parent) : QObject(parent)
{
    this->settings=settings;
    file.setFileName("log.txt");
    timeCount=0;
    request.setUrl(QUrl("http://ip.chinaz.com/"));//查询外网ip的网址
    content="QT Email Test";
    manager = new QNetworkAccessManager(this);
    connect(&timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    connect(&smtp,SIGNAL(message(QString)),this,SLOT(log(QString)));
    connect(this,SIGNAL(message(QString)),this,SLOT(log(QString)));


}

CheckAndEmail::~CheckAndEmail()
{

}
void CheckAndEmail::runWithUi()
{
    window=new MainWindow(settings);
    connect(&smtp,SIGNAL(message(QString)),window,SLOT(showInfo(QString)));
    connect(window,SIGNAL(command(QString)),this,SLOT(command(QString)));
    connect(this,SIGNAL(message(QString)),window,SLOT(showInfo(QString)));

    window->show();
}
void CheckAndEmail::command(QString cmd)
{
    if(cmd=="start") this->run();
    if(cmd=="stop") this->stop();
}

void CheckAndEmail::run()
{
    timer.setInterval(settings->interval);
    timer.start();
    this->timerEvent();
}
void CheckAndEmail::stop()
{
    timer.stop();
}
void CheckAndEmail::log(QString message)
{
    file.open(QIODevice::Append);
    file.write(message.toLocal8Bit()+"\n");
    file.close();
}

void CheckAndEmail::timerEvent()
{
    reply = manager->get(request);
    timeCount++;
}

void CheckAndEmail::replyFinished(QNetworkReply *reply)
{
    emit message(date.currentDate().toString("yyyy-MM-dd ")+time.currentTime().toString());

    QRegExp reg(settings->pattern);
    ip.clear();
    ip.append(reply->readAll());
    ip=ip.mid(ip.indexOf(settings->pickIpFrom));
    int pos = reg.indexIn(ip);
    if (pos > -1)
    {
        ip= reg.cap(0);
        emit message("公网IP:"+ip);
    }
    else
    {
        emit message("公网IP查找失败");
        ip.clear();
    }
    currentInfo = QHostInfo::fromName(QHostInfo::localHostName());
    content=currentInfo.localHostName()+"\r\n";
    content+="网卡IP：\r\n";
    QHostAddress address;
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach (address, list)
    {
        content.append(address.toString()+"\r\n");
    }//获取本地网卡地址


    if(currentInfo.addresses()==emailedInfo.addresses()&&oldip==ip&&timeCount<(24*3600*1000/settings->interval))    return;
    timeCount=0;
    oldip=ip;
    content.append("公网IP："+ip);
    smtp.communicate(settings,content);

    emailedInfo=currentInfo;
}
