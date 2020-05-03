#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(1100,700);
    w.setWindowTitle("Path finding algorithms");
    w.show();

    return a.exec();
}
