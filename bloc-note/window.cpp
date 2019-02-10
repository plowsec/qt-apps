#include "window.h"
#include "dialog.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    buildInterface();
    setFixedSize(350,505);
    setWindowTitle("ListMaker");
    setWindowIcon(QIcon("icone.png"));

}

void Window::buildInterface()
{
    champ_path = new QLineEdit(this);
    champ_path->setDisabled(true);

    boutonChoisir = new QPushButton("Parcourir",this);
    connect(boutonChoisir, SIGNAL(clicked()),this,SLOT(choisirDossier()));

    boutonAction = new QPushButton("Générer",this);
    boutonAction->setDisabled(true);
    connect(boutonAction, SIGNAL(clicked()),this,SLOT(extractFile()));

    boutonChanger = new QPushButton("Echanger",this);
    connect(boutonChanger, SIGNAL(clicked()),this,SLOT(rename()));

    layoutPrincipale = new QHBoxLayout;
    layoutPrincipale->addWidget(champ_path);
    layoutPrincipale->addWidget(boutonChoisir);
    layoutPrincipale->addWidget(boutonAction);
    layoutPrincipale->addWidget(boutonChanger);

    groupeInterface = new QGroupBox("Application",this);
    groupeInterface->setLayout(layoutPrincipale);
    groupeInterface->setGeometry(10,170,330,60);

    champText = new QTextEdit(this);
    champText->setGeometry(10,245,330,230);
    champText->setReadOnly(true);

    fermer = new QPushButton("Fermer", this);
    fermer->setGeometry(280,480,60,22);
    connect(fermer, SIGNAL(clicked()),this,SLOT(close()));

    checkbox1 = new QCheckBox("Supprimer l'extension");
    checkbox1->setChecked(true);

    checkbox2 = new QCheckBox("Remplacer \"-\"");
    up = new QRadioButton("Transformer en majuscules");
    low = new QRadioButton("Transformer en minuscules");
    no = new QRadioButton("Aucune modification");

    no->setChecked(true);

    layout1 = new QVBoxLayout;
    layout1->addWidget(checkbox1);
    layout1->addWidget(checkbox2);
    layout1->addWidget(up);
    layout1->addWidget(low);
    layout1->addWidget(no);

    groupeOptions = new QGroupBox("Options",this);
    groupeOptions->setLayout(layout1);
    groupeOptions->setGeometry(10,10,330,150);
}
void Window::choisirDossier()
{
    QString chemin;
    chemin = QFileDialog::getExistingDirectory(this,"Choisissez un dossier");
    champ_path->setText(chemin);
    boutonAction->setDisabled(false);
    setChemin(chemin);


}
void Window::extractFile()
{
    QDir dir(getChemin());
    QString text;
    QString nomFichier;
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0 ; i < list.length() ; i++)
    {
        QFileInfo info = list.at(i);
        if(up->isChecked())
        {
            nomFichier = info.fileName().toUpper();

        }
        else if(low->isChecked())
        {
            nomFichier = info.fileName().toLower();
        }
        else
        {
            nomFichier = info.fileName();
        }
        if(checkbox2->isChecked())
        {
            nomFichier.replace(" - ","-");
        }
        if(!checkbox1->isChecked())
        {
          text+= nomFichier+"\n";
        }

        else
        {
            text+= nomFichier.split(".")[0] + "\n";
        }
    }
    champText->setPlainText(text);
    setText(text);
}
QString Window::getChemin()
{
    return cheminDossier;
}
void Window::setChemin(QString chemin)
{
    cheminDossier = chemin;
}

void Window::setText(QString text)
{
    textFinal = text;
}
QString Window::getText()
{
    return textFinal;
}
void Window::ouvrirAPropos()
{
    Dialog *newWindow = new Dialog(this);
    newWindow->exec();
}
void Window::rename()
{
    QString ch = QFileDialog::getExistingDirectory(this,"Choisissez un dossier");
    QString erreurs = "";
    QDir dir(ch);
    int num = 0;
    int num1 = 0;
    int num2 = 0;
    QFileInfoList list = dir.entryInfoList();
    for(int i = 0 ; i < list.length() ; i++)
    {
        QFileInfo info = list.at(i);
        QString po = ch + "/" + info.fileName();
        QFile fichier(po);
        if(info.fileName().size()>5)
        {
            QString str = fichier.fileName();
            QString str1 = str.mid(fichier.fileName().lastIndexOf("/")+1);
            if(str1.contains(" - "))
            {
                QString actor = str1.split(" - ")[0];
                QString titre = str1.split(" - ")[1].split(".")[0];
                QString essai = str.left(str.size()-str1.size());
                QString str2 = str.mid(fichier.fileName().lastIndexOf("."));
                QRegExp rx("(\\d{4})");
                QString date = titre.mid(titre.lastIndexOf(rx)-1);
                if(str1.contains(rx))
                {
                   QString titre1 = titre.left(titre.size()-date.size());
                   fichier.rename(essai+titre1+" - "+actor+" "+date+str2);
                   num1++;
                }
                else
                {
                    fichier.rename(essai+titre+" - "+actor+str2);
                }
                num++;
            }
            else
            {
                erreurs+=info.fileName()+"\n";
            }
            num2++;
        }
    }

    QMessageBox::information(this,"Opération terminée", QString::number(num) + " fichiers ont été renommés avec succès!\n"+QString::number(num1) + " titres contiennent des dates.\n"+QString::number(num2-num)+" fichiers ont pu échapper à la purge.");
    QMessageBox::information(this,"Liste","Voici les fichiers n'ayant pu être renommés : \n"+erreurs);
}






