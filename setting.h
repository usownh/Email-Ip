#ifndef SETTING_H
#define SETTING_H
#include <QString>

#include <QSettings>

class Setting
{
public:
    Setting();
    ~Setting();
    void writeSettings();
    void readSettings();

    QString smtpHost,userName,password,dest,subject;
    QString checkIpUrl,pickIpFrom;


    QString ip,oldip;
    int interval;
    QSettings settings;
    bool autorun;
    bool gui;
    QString pattern;

};

#endif // SETTING_H
