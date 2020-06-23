#include "mainwindow.h"
#include "papercerberus.h"
#include <QApplication>

//#include "./include/ZipLib/ZipArchive.h"
//#include "./include/ZipLib/ZipFile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaperCerberus* pc = new PaperCerberus();
    MainWindow w(pc);
    w.show();
    return a.exec();
}
