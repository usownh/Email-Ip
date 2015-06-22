#include "smtp.h"

Smtp::Smtp(QObject *parent) : QObject(parent)
{

}

Smtp::~Smtp()
{

}
void Smtp::communicate(Setting *settings, const QString content)
{
    this->settings=settings;
    socket.connectToHost(settings->smtpHost,25);
    if (socket.waitForConnected(2000))
    {
        emit message("smtp server connected success.");
        this->readWelcome();
        this->smtpCommunication(content);
        socket.close();
    }
    else
        emit message("connection failed.");
}

void Smtp::readWelcome()
{
    QString welcome;
    if (socket.waitForReadyRead(-1) == true)
    {
        welcome=socket.readAll();
        emit message(welcome.trimmed());
    }
}
void Smtp::smtpCommunication(const QString content)
{
        communication("helo "+settings->smtpHost+"\r\n");
        communication("auth login\r\n");//账户登录
        communication(settings->userName.toLocal8Bit().toBase64()+"\r\n");
        communication(settings->password.toLocal8Bit().toBase64()+"\r\n");
        communication("mail from: <"+settings->userName+">\r\n");
        communication("rcpt to: <"+settings->dest+">\r\n");
        communication("data\r\n");
        communication("From: "+settings->userName+"\r\nTo: "+settings->dest+"\r\n"
                              "Subject: "+settings->subject+"\r\n\r\n"
                              +content+"\r\n.\r\n");
        communication("quit\r\n");
        emit message("send email ok.");
}

void Smtp::communication(QString msg)
{
    if (socket.write(msg.toLocal8Bit()) == -1)
        emit message( "@@@@@@@@@@@@@@ socket.write failed");
    socket.flush();
    if (socket.waitForReadyRead(-1) == true)
    {
        emit message(socket.readAll().trimmed());
    }
}
