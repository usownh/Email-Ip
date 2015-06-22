#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QTimer>
#include <setting.h>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Setting *settings,QWidget *parent = 0);
    ~MainWindow();

signals:
    void command(QString);
public slots:
    void showInfo(QString);

private slots:
    void on_pushButtonStart_clicked();


private:
    Ui::MainWindow *ui;
    Setting *settings;
//
//    QNetworkRequest request;
//    QString SMTPHost,UserName,Password,Dest,Subject,Content;
//    QHostInfo EmailedInfo,CurrentInfo;
//    QTimer timer;
//    QNetworkAccessManager *manager;
//    QNetworkReply *reply;
//
//    int timeCount;
//    int interval;
//    QSettings settings;
//    bool autorun;
};

#endif // MAINWINDOW_H
