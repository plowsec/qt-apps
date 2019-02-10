#ifndef GEN_H
#define GEN_H

#include <QtGui>

class Gen : public QDialog
{
public:
    Gen(QString code, QWidget *parent);

private:
    QTextEdit *text;
    QPushButton *close;
    QVBoxLayout *layoutGen;
};

#endif // GEN_H
