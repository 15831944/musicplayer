#include "entry.h"
#include "login.h"
#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setStyle("windows");
    //QApplication::setStyle("windowsxp");
    //QApplication::setStyle("motif");
    //QApplication::setStyle("cde");
    //QApplication::setStyle("macintosh");
    //QApplication::setStyle("plastique");
    MainWindow w;
    login begin;
    QFile file1("button.file");
    file1.open(QIODevice::ReadOnly);
    QDataStream in1(&file1);
    bool au=false;
    bool reme=false;
    in1>>au>>reme;
    file1.close();
    if( au == true && reme == true )
        w.show();
    else
        begin.show();
    return a.exec();
}
