#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QSettings>
#include <QNetworkInterface>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void communication(QTcpSocket & socket, QString msg);
    void smtpCommunication(QTcpSocket & socket);
    void readWelcome(QTcpSocket & socket);
    //smtp通信

    void writeSettings();
    void readSettings();
    //读写config配置文件

private slots:
    void on_pushButtonStart_clicked();
    void timerEvent();
    void replyFinished(QNetworkReply*);

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    QNetworkRequest request;
    QString SMTPHost,UserName,Password,Dest,Subject,Content;
    QHostInfo EmailedInfo,CurrentInfo;
    QTimer timer;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString ip,oldip;
    int timeCount;
    int interval;
    QSettings settings;
    bool autorun;
};

#endif // MAINWINDOW_H
