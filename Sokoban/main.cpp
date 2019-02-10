
#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window fenetre;
    fenetre.show();

    return app.exec();
}


