#include <QApplication>
#include <QTextCodec>
#include <checkandemail.h>
#include <setting.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Setting settings;
    settings.readSettings();
    CheckAndEmail mainProcess(&settings);
    if(settings.gui)
        mainProcess.runWithUi();
    else
        mainProcess.run();
    return a.exec();
}
