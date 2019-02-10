#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>

class Dialog : public QDialog
{
public:
    Dialog(QWidget *parent);

private:
    QPushButton *close;
    QTextEdit *text;

};

#endif // DIALOG_H
