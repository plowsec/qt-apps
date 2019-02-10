#include "Generated.h"
#include <QtGui>

Gen::Gen(QString code, QWidget *parent) : QDialog(parent)
{
    text = new QTextEdit;
    text->setPlainText(code);
    text->setFont(QFont("Courrier"));
    text->setReadOnly(true);
    text->setLineWrapMode(QTextEdit::NoWrap);
    close = new QPushButton("Fermer");

    layoutGen = new QVBoxLayout;
    layoutGen->addWidget(text);
    layoutGen->addWidget(close);
    resize(350, 450);
    setLayout(layoutGen);

    connect(close, SIGNAL(clicked()), this, SLOT(accept()));
}
