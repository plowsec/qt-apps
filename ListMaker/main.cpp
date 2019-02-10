
#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
        QApplication *app = new QApplication(argc, argv);

        Window *fenetre = new Window;
        fenetre->show();

        return app->exec();
}
