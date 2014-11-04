#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    autorun=false;
    ui->statusBar->showMessage("程序未运行");
    Subject="QT EMAIL";
    Content="QT Email Test";
    request.setUrl(QUrl("http://ip.chinaz.com/"));//查询外网ip的网址
    manager = new QNetworkAccessManager(this);
    connect(&timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    timeCount=0;
    readSettings();
    ui->lineEditDestination->setText(Dest);
    ui->lineEditSMTP->setText(SMTPHost);
    ui->lineEditUserName->setText(UserName);
    ui->lineEditPassword->setText(Password);
    //自动根据配置文件config填写表单
    if(autorun) this->on_pushButtonStart_clicked();//自动运行
}


void MainWindow::writeSettings()
{
    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("CONFIG");
    settings.setValue("AUTORUN",autorun);//自动运行
    settings.setValue("INTERVAL",interval);//定时查询间隔
    settings.setValue("SMTPSERVER",SMTPHost);//SMTP服务器地址 仅测试了sina网邮箱
    settings.setValue("USER",UserName);//用户名  XX@sina.cn
    settings.setValue("DESTMAIL",Dest);//发送的目标邮箱
    settings.setValue("Password",Password);//邮箱密码
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("CONFIG");
    autorun=settings.value("AUTORUN").toBool();
    interval=settings.value("INTERVAL").toInt();
    if(interval==0)    interval=600000;
    SMTPHost=settings.value("SMTPSERVER").toString();
    UserName=settings.value("USER").toString();
    Dest=settings.value("DESTMAIL").toString();
    Password=settings.value("Password").toString();
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readWelcome(QTcpSocket & socket)
{
    QString welcome;
    if (socket.waitForReadyRead(-1) == true)
    {
        welcome=socket.readAll();
        ui->textBrowser->append(welcome.trimmed());
    }
}
void MainWindow::smtpCommunication(QTcpSocket & socket)
{
        communication(socket, "helo "+SMTPHost+"\r\n");
        communication(socket, "auth login\r\n");//账户登录
        communication(socket, UserName.toLocal8Bit().toBase64()+"\r\n");
        communication(socket, Password.toLocal8Bit().toBase64()+"\r\n");
        communication(socket, "mail from: <"+UserName+">\r\n");
        communication(socket, "rcpt to: <"+Dest+">\r\n");
        communication(socket, "data\r\n");
        communication(socket, "From: "+UserName+"\r\nTo: "+Dest+"\r\n"
                              "Subject: "+Subject+"\r\n\r\n"
                              +Content+
                              "\r\n.\r\n");
        communication(socket, "quit\r\n");

        ui->textBrowser->append("send email ok.");
}

void MainWindow::timerEvent()
{    
    reply = manager->get(request);
    timeCount++;
}
void MainWindow::replyFinished(QNetworkReply *reply)
{
    CurrentInfo = QHostInfo::fromName(QHostInfo::localHostName());
    Content=CurrentInfo.localHostName()+"\r\n";
    Content+="网卡IP：\r\n";
    QHostAddress address;    
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach (address, list)
    {
        Content.append(address.toString()+"\r\n");
    }//获取本地网卡地址

    ip.clear();
    ip.append(reply->readAll());
    if(ip.contains("您的IP:"))
    {
        ip=ip.mid(ip.indexOf("您的IP:"),50);
        for(int i=ip.length()-1;i>=0;i--)
        {
            if(ip.at(i).isNumber()||ip.at(i)=='.') continue;
            ip.remove(i,1);
        }//从返回的网页里提取外网IP
    }
    else
    {
        ip="公网Ip查找失败！";
    }
    if(CurrentInfo.addresses()==EmailedInfo.addresses()&&oldip==ip&&timeCount<(24*3600*1000/interval))    return;
    timeCount=0;
    oldip=ip;
    Content.append("公网IP："+ip);
    socket.connectToHost(SMTPHost,25);
    if (socket.waitForConnected(2000))
    {
        ui->textBrowser->append("smtp server connected success.");
        readWelcome(socket);
        smtpCommunication(socket);
        socket.close();
    }
    else
        ui->textBrowser->append("connection failed.");
    EmailedInfo=CurrentInfo;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if (ui->pushButtonStart->text()=="启动")
    {
        SMTPHost=ui->lineEditSMTP->text();
        UserName=ui->lineEditUserName->text();
        Password=ui->lineEditPassword->text();
        Dest=ui->lineEditDestination->text();
        writeSettings();
        timer.setInterval(interval);
        timer.start();
        ui->pushButtonStart->setText("停止");
        ui->statusBar->showMessage("程序运行中");
        this->timerEvent();
    }
    else
    {
        timer.stop();
        ui->pushButtonStart->setText("启动");
        ui->statusBar->showMessage("程序未运行");
    }

}

void MainWindow::communication(QTcpSocket & socket, QString msg)
{
    if (socket.write(msg.toLocal8Bit()) == -1)
        ui->textBrowser->append( "@@@@@@@@@@@@@@ socket.write failed");
    socket.flush();
    if (socket.waitForReadyRead(-1) == true)
    {
        ui->textBrowser->append(socket.readAll().trimmed());
    }
}



