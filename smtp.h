#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <setting.h>
class Smtp : public QObject
{
    Q_OBJECT
public:
    explicit Smtp(QObject *parent = 0);
    ~Smtp();
    void communicate(Setting *settings, const QString content);
private:
    void communication(QString msg);
    void smtpCommunication(const QString content);
    void readWelcome();


signals:
    void message(QString);

public slots:
private:
    QTcpSocket socket;
    Setting *settings;
};

#endif // SMTP_H
