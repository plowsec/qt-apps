
#include <QApplication>
#include <QtGui>
#include "editeur.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Editeur fenetre;
    fenetre.show();

    return app.exec();
}


