# Email-Ip
Detect local ip and email.Implemented in Qt. The email of sina.cn has been tested. 

This project aims to detect the ip changes. If any ip address has changed, it will send an email to notice you.

This project was created by Qt Creator. 
Your Qt version is advised more than 5.4.

After using Qt make it, you should copy the config.ini to the executable file path. Then edit it to finish your configuration.

In this file, there are some options you can set.
AUTORUN is only avaliable for gui mode. If it is true, it will auto start to detect.
INTERVAL determines how often to check the ip. Initial value is 60000 milliseconds.
SMTPSERVER , USER and Password is the information you used to send email. I suggest that use a new registed email for no encryption in this file.
DESTMAIL is the email you want to recieve the info.
IpInfoURL is the website which tells the global ip address of you computer.
PickIpFrom is where we start to search the ip address. So you can use any words before the ip address. Closer is better. Chinese words are encoded, so we can add it in GUI mode.
IPPattern is  a regular expression of ip addresses. This usually needn't to change.
RunWithUi determines to show UI or not.

After setting this file, it will work.

