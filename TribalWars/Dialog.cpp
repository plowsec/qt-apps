#include "Dialog.h"

Dialog::Dialog(District *Origine, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Troupes");
    int troupes = Origine->getTroupes();
    comboList = new QComboBox();
    for(int i=1;i<troupes;i++)
    {
        comboList->addItem(QString::number(i));
    }
    label = new QLabel("Combien voulez-vous en déplacer?");
    close = new QPushButton("Valider");
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboList);
    layout->addWidget(close);
    setLayout(layout);
    connect(close,SIGNAL(clicked()),this,SLOT(quitter()));

}

void Dialog::quitter()
{
    recup();
    close->setDisabled(true);
}
int Dialog::recup()
{
    valeur = comboList->currentText().toInt();
    return valeur;
}
