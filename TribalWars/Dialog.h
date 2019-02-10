#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "District.h"
#include <QtGui>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(District *Origine,QWidget *parent);
public slots:
    int recup();
    void quitter();
    
private:
    QComboBox *comboList;
    QPushButton *close;
    QVBoxLayout *layout;
    QLabel *label;
    int valeur;
    
};

#endif // DIALOG_H
