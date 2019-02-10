#ifndef GENERATED_H
#define GENERATED_H

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

#endif // GENERATED_H
