#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Setting *settings,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(settings)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("程序未运行");

    ui->lineEditDestination->setText(settings->dest);
    ui->lineEditSMTP->setText(settings->smtpHost);
    ui->lineEditUserName->setText(settings->userName);
    ui->lineEditPassword->setText(settings->password);
    ui->lineEditCheckIpUrl->setText(settings->checkIpUrl);
    ui->lineEditPickIpRegExp->setText(settings->pickIpFrom);
    //自动根据配置文件config填写表单
    if(settings->autorun) this->on_pushButtonStart_clicked();//自动运行
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showInfo(QString info)
{
    ui->textBrowser->append(info);
}

void MainWindow::on_pushButtonStart_clicked()
{
    if (ui->pushButtonStart->text()=="启动")
    {
        settings->smtpHost=ui->lineEditSMTP->text();
        settings->userName=ui->lineEditUserName->text();
        settings->password=ui->lineEditPassword->text();
        settings->dest=ui->lineEditDestination->text();
        settings->checkIpUrl=ui->lineEditCheckIpUrl->text();
        settings->pickIpFrom=ui->lineEditPickIpRegExp->text();
        settings->writeSettings();
        emit command("start");
        ui->pushButtonStart->setText("停止");
        ui->statusBar->showMessage("程序运行中");
    }
    else
    {
        emit command("start");
        ui->pushButtonStart->setText("启动");
        ui->statusBar->showMessage("程序未运行");
    }

}




