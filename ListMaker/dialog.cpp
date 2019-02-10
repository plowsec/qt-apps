#include "dialog.h"
#include <QtGui>

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    close = new QPushButton("Fermer");
    connect(close, SIGNAL(clicked()), this, SLOT(accept()));

    text = new QTextEdit(this);
    text->setDisabled(true);
    QString txt = "16.12.2011\nDéveloppé par Vladimir Meier\nListMaker v1.1";
    text->setPlainText(txt);
    resize(180,50);
}
