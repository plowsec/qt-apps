#include "dialog.h"
#include <QtGui>

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    close = new QPushButton("Fermer");
    connect(close, SIGNAL(clicked()), this, SLOT(accept()));

    text = new QTextEdit(this);
    text->setDisabled(true);
    QString txt = "Notepad v2.1\n\nDéveloppé par Vladimir Meier\nzotan@hotmail.fr";
    text->setPlainText(txt);
    resize(180,70);
    setWindowTitle("A propos...");
}
