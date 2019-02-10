#include "mainWindow.h"

MainWindow::MainWindow()
{
    setWindowIcon(QIcon("icone.png"));
    tex=new QTextEdit();
    tex2=new QTextEdit();
    button=new QPushButton("Ok");
    layout = new QVBoxLayout;

    groupRadio = new QGroupBox("Opération à effectuer",this);
    radioDonnes= new QRadioButton("Format de données");
    radioCompter = new QRadioButton("Compter des caractères");
    radioDonnes->setChecked(true);
    layoutRadio= new QHBoxLayout;
    layoutRadio->addWidget(radioDonnes);
    layoutRadio->addWidget(radioCompter);
    groupRadio->setLayout(layoutRadio);

    layout->addWidget(groupRadio);
    layout->addWidget(tex);
    layout->addWidget(button);
    layout->addWidget(tex2);
    setLayout(layout);
    connect(button, SIGNAL(clicked()),this,SLOT(traiter()));
}
void MainWindow::traiter()
{
    if (radioDonnes->isChecked())
        formater();
    else
        compter();
}
void MainWindow::compter()
{
    QString txt;
    txt=tex->toPlainText();
    int compteur=0;
    int i;
    for (i=0;i<txt.length();i++)
    {
        if(txt[i]!=' ')
        {
            compteur++;
        }
    }
    tex2->setPlainText(QString::number(compteur));
}

void MainWindow::formater()
{
    QString donnees;
    donnees=tex->toPlainText();
    tex2->setPlainText(donnees.replace("\n",", "));
}
