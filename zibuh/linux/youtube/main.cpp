#include <QApplication>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow fen;
    fen.show();
    return app.exec();
}
