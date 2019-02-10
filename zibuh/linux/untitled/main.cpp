#include <QApplication>
#include "FenPrincipale.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.show();

    fenetre.updateStatus();

    app.setApplicationName("Zibuh");

    return app.exec();
}
