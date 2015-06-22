#include "setting.h"

Setting::Setting()
{
    autorun=false;
    subject="QT EMAIL";
    checkIpUrl="http://ip.chinaz.com/";
    readSettings();
    pattern="((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)";//ip RegExp


}

Setting::~Setting()
{

}

void Setting::writeSettings()
{
    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("CONFIG");
    settings.setValue("AUTORUN",autorun);//自动运行
    settings.setValue("INTERVAL",interval);//定时查询间隔
    settings.setValue("SMTPSERVER",smtpHost);//SMTP服务器地址 仅测试了sina网邮箱
    settings.setValue("USER",userName);//用户名  XX@sina.cn
    settings.setValue("DESTMAIL",dest);//发送的目标邮箱
    settings.setValue("Password",password);//邮箱密码
    settings.setValue("IpInfoURL",checkIpUrl);//查询外网IP的网址
    settings.setValue("PickIpFrom",pickIpFrom);//提取IP的位置
    settings.setValue("RunWithUi",gui);//提取IP的位置
    settings.setValue("IPPattern",pattern);//IP的正则匹配式
    settings.endGroup();
}

void Setting::readSettings()
{
    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("CONFIG");
    autorun=settings.value("AUTORUN").toBool();
    interval=settings.value("INTERVAL").toInt();
    if(interval==0)    interval=600000;
    smtpHost=settings.value("SMTPSERVER").toString();
    userName=settings.value("USER").toString();
    dest=settings.value("DESTMAIL").toString();
    password=settings.value("Password").toString();
    checkIpUrl=settings.value("IpInfoURL").toString();
    pickIpFrom=settings.value("PickIpFrom").toString();
    gui=settings.value("RunWithUi").toBool();
    pattern=settings.value("IPPattern").toString();
    settings.endGroup();
}
