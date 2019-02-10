#include "editeur.h"
#include "view.h"

Editeur::Editeur()
{
    buildInterface();
    buildEcran();
}
void Editeur::buildInterface()
{
    setWindowTitle("Sokoban Editor");
    setWindowIcon(QIcon("icone.png"));
    setFixedSize(390,440);

    tool = addToolBar("Fichier");
    menuFichier = menuBar()->addMenu("&Fichier");
    actionEnregistrer = menuFichier->addAction("Enregistrer");
    actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionEnregistrer,SIGNAL(triggered()),this,SLOT(save()));

    caisse = new QAction(QIcon("caisse.jpg"),"Caisse",this);
    caisse->setCheckable(true);
    connect(caisse,SIGNAL(triggered()),this,SLOT(changeEtatCaisse()));

    caisseOk = new QAction(QIcon("caisse_ok.jpg"),"Caisse OK",this);
    caisseOk->setCheckable(true);
    connect(caisseOk,SIGNAL(triggered()),this,SLOT(changeEtatCaisseOk()));

    wall = new QAction(QIcon("wall.png"),"Mur",this);
    wall->setCheckable(true);
    connect(wall,SIGNAL(triggered()),this,SLOT(changeEtatWall()));

    sand = new QAction(QIcon("sand.png"),"Fond",this);
    sand->setCheckable(true);
    sand->setChecked(true);
    connect(sand,SIGNAL(triggered()),this,SLOT(changeEtatSand()));

    mario = new QAction(QIcon("explorer_bas.png"),"Personnage",this);
    mario->setCheckable(true);
    connect(mario,SIGNAL(triggered()),this,SLOT(changeEtatMario()));

    objectif = new QAction(QIcon("objectif.png"),"Objectif",this);
    objectif->setCheckable(true);
    connect(objectif,SIGNAL(triggered()),this,SLOT(changeEtatObjectif()));

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
    vue->setStr("caisse.jpg");

}
void Editeur::changeEtatCaisseOk()
{
    caisse->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr("caisse_ok.jpg");
}
void Editeur::changeEtatWall()
{
    caisseOk->setChecked(false);
    caisse->setChecked(false);
    sand->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr("wall.png");
}
void Editeur::changeEtatSand()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    caisse->setChecked(false);
    mario->setChecked(false);
    objectif->setChecked(false);
    vue->setStr("sand.png");
}
void Editeur::changeEtatMario()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    caisse->setChecked(false);
    objectif->setChecked(false);
    vue->setStr("explorer_bas.png");
}
void Editeur::changeEtatObjectif()
{
    caisseOk->setChecked(false);
    wall->setChecked(false);
    sand->setChecked(false);
    caisse->setChecked(false);
    vue->setStr("objectif.png");
}

void Editeur::save()
{
    QMessageBox::information(this,"erreur",vue->getMap());
    QFile fichier("niveaux_créés.lvl");
    fichier.open( QIODevice::ReadWrite | QIODevice::Text);

   QString contenu = fichier.readAll();

    QTextStream flux(&fichier);
    flux << contenu + "\n";
    flux << vue->getMap();
    fichier.close();
}
