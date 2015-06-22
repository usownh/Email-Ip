#ifndef CHECKANDEMAIL_H
#define CHECKANDEMAIL_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <mainwindow.h>
#include <setting.h>
#include <QNetworkInterface>
#include <smtp.h>
#include <QFile>
#include <QTime>
#include <QDate>
#include <QRegExp>


class CheckAndEmail : public QObject
{
    Q_OBJECT
public:
    explicit CheckAndEmail(Setting *settings,QObject *parent = 0);
    ~CheckAndEmail();
    void runWithUi();
    void run();
    void stop();
signals:
    void message(QString);
public slots:
    void timerEvent();
    void replyFinished(QNetworkReply*);
    void log(QString);
    void command(QString);
private:
    int timeCount;
    QTimer timer;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QHostInfo emailedInfo,currentInfo;
    QNetworkRequest request;
    Smtp smtp;
    QFile file;
    QString content;
    QString ip,oldip;
    MainWindow *window;
    QTime time;
    QDate date;
    Setting *settings;
};

#endif // CHECKANDEMAIL_H
