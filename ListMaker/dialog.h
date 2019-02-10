#ifndef GEN_H
#define GEN_H

#include <QtGui>

class Dialog : public QDialog
{
public:
    Dialog(QWidget *parent);

private:
    QPushButton *close;
    QTextEdit *text;

};

#endif // GEN_H
