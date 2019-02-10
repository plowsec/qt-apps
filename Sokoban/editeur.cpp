#include "editeur.h"
#include "view.h"

Editeur::Editeur(QWidget *parent): QMainWindow(parent)
{
    setGraphs();
    buildInterface();
    buildEcran();
}
void Editeur::buildInterface()
{
    setWindowTitle("Sokoban Editor");
    setWindowIcon(QIcon("icone.png"));
    setFixedSize(390,465);

    barreEtat = statusBar();

    tool = addToolBar("Fichier");
    menuFichier = menuBar()->addMenu("&Fichier");
    actionEnregistrer = menuFichier->addAction("Enregistrer");
    actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionEnregistrer,SIGNAL(triggered()),this,SLOT(save()));

    menuAide = menuBar()->addMenu("&?");
    actionAide = menuAide->addAction("Aide");
    connect(actionAide,SIGNAL(triggered()),this,SLOT(aide()));


    caisse = new QAction(QIcon(Caisse),"Caisse",this);
    caisse->setCheckable(true);
    connect(caisse,SIGNAL(triggered()),this,SLOT(changeEtatCaisse()));
    caisse->setStatusTip("Caisse");

    caisseOk = new QAction(QIcon(Caisse_ok),"Caisse OK",this);
    caisseOk->setCheckable(true);
    connect(caisseOk,SIGNAL(triggered()),this,SLOT(changeEtatCaisseOk()));
    caisseOk->setStatusTip("Caisse rouge");

    wall = new QAction(QIcon(Mur),"Mur",this);
    wall->setCheckable(true);
    connect(wall,SIGNAL(triggered()),this,SLOT(changeEtatWall()));
    wall->setStatusTip("Mur");

    sand = new QAction(QIcon(Fond),"Fond",this);
    sand->setCheckable(true);
    sand->setChecked(true);
    connect(sand,SIGNAL(triggered()),this,SLOT(changeEtatSand()));
    sand->setStatusTip("Fond");

    mario = new QAction(QIcon(Personnage),"Personnage",this);
    mario->setCheckable(true);
    connect(mario,SIGNAL(triggered()),this,SLOT(changeEtatMario()));
    mario->setStatusTip("Personnage");

    objectif = new QAction(QIcon(Objectif),"Objectif",this);
    objectif->setCheckable(true);
    connect(objectif,SIGNAL(triggered()),this,SLOT(changeEtatObjectif()));
    objectif->setStatusTip("Objectif");

    tool->addAction(caisse);
    tool->addAction(caisseOk);
    tool->addAction(wall);
    tool->addAction(sand);
    tool->addAction(mario);
    tool->addAction(objectif);

}
void Editeur::buildEcran()
{
    vue = new View(this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setGeometry(0,54,388,390);
    vue->setSceneRect(0,0,386,386);
    vue->setMouseTracking(true);
    vue->show();
}

void Editeur::changeEtatCaisse()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr(Caisse);

}
void Editeur::changeEtatCaisseOk()
{
    caisse->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr(Caisse_ok);
}
void Editeur::changeEtatWall()
{
    caisseOk->setChecked(false);
    caisse->setChecked(false);
    sand->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr(Mur);
}
void Editeur::changeEtatSand()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    caisse->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr(Fond);
}
void Editeur::changeEtatMario()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    caisse->setChecked(false);
    objectif->setChecked(false);
    vue->setStr(Personnage);
}
void Editeur::changeEtatObjectif()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    caisse->setChecked(false);
    vue->setStr(Objectif);
}

void Editeur::save()
{
    int rep = QMessageBox::question(this, "Ajouter ce niveau?", "Ce tableau sera ajouté à la suite des niveaux de base.\nAjouter ce niveau?", QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes)
    {
        QFile fichier(Niveau);
        fichier.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
        QTextStream flux(&fichier);
        flux << "\n" + vue->getMap();
        fichier.close();
        QMessageBox::information(this,"Information","Niveau enregistré avec succès.");
        barreEtat->showMessage("Niveau enregistré et ajouté");
    }
}
void Editeur::aide()
{
    QMessageBox::information(this,"Aide","Utilisez cette interface pour créer votre propre niveau Sokoban.\nCliquez sur une image pour la sélectionner, puis à l'endroit où vous souhaitez la placer.");
}
void Editeur::setGraphs()
{
    QString chaine;
    QFile fichier("config/config.cfg");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        chaine = fichier.readLine();
        Niveau = chaine.split(" ")[0];
        Personnage = chaine.split(" ")[1];
        Fond = chaine.split(" ")[2];
        Mur = chaine.split(" ")[3];
        Objectif = chaine.split(" ")[4];
        Caisse = chaine.split(" ")[5];
        Caisse_ok = chaine.split(" ")[6];
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Fichier .cfg indisponible");
    }
}

