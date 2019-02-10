#include "window.h"
#include "dialog.h"

Window::Window()
{
    buildMenu();
    buildInterface();
    setFixedSize(350,605);
    setWindowTitle("ListMaker");
    setWindowIcon(QIcon("icone.png"));

}
void Window::buildMenu()
{
    QMenu *menuFichier = menuBar()->addMenu("Fichier");
    QAction *actionQuitter = menuFichier->addAction("Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *actionSave = menuFichier->addAction("Sauvegarder");
    actionSave->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionSave, SIGNAL(triggered()),this, SLOT(save()));

    QMenu *menuAide = menuBar()->addMenu("?");
    QAction *actionApropos = menuAide->addAction("A propos");
    connect(actionApropos, SIGNAL(triggered()), this, SLOT(ouvrirAPropos()));
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

    layoutPrincipale = new QHBoxLayout;
    layoutPrincipale->addWidget(champ_path);
    layoutPrincipale->addWidget(boutonChoisir);
    layoutPrincipale->addWidget(boutonAction);

    groupeInterface = new QGroupBox("Application",this);
    groupeInterface->setLayout(layoutPrincipale);
    groupeInterface->setGeometry(10,190,330,60);

    champText = new QTextEdit(this);
    champText->setGeometry(10,265,330,330);
    champText->setReadOnly(true);

    checkbox1 = new QCheckBox("Supprimer l'extension");
    checkbox1->setChecked(true);

    up = new QRadioButton("Transformer en majuscules");
    low = new QRadioButton("Transformer en minuscules");
    no = new QRadioButton("Aucune modification");

    no->setChecked(true);

    layout1 = new QVBoxLayout;
    layout1->addWidget(checkbox1);
    layout1->addWidget(up);
    layout1->addWidget(low);
    layout1->addWidget(no);

    groupeOptions = new QGroupBox("Options",this);
    groupeOptions->setLayout(layout1);
    groupeOptions->setGeometry(10,30,330,150);
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
void Window::save()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Sauvegarder",
                                "untitled.txt", "Fichiers textes (*.txt);; Tous les fichiers (*.*)");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
       QTextStream out(&file);
       out << getText();
       file.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'enregistrer le fichier");
       return;
    }
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
