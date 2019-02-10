
//#include <QtGui>
#include "MainWindow.h"
#include <QtWidgets/QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.show();

    return app.exec();
}
