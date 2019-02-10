#include "options.h"


Options::Options(QWidget *parent) : QDialog(parent)
{
    setGraphs();
    buildInterface();
    setWindowTitle("Sokoban - Réglages");
}
void Options::buildInterface()
{
    layout = new QVBoxLayout;
    setLayout(layout);

    labelNiveau = new QLabel("Choisir un fichier de niveaux");
    lineNiveau = new QLineEdit(niveau);
    boutonFichier = new QPushButton("Parcourir");
    connect(boutonFichier, SIGNAL(clicked()),this,SLOT(setNiveaux()));
    layoutNiveau = new QHBoxLayout;
    layoutNiveau->addWidget(labelNiveau);
    layoutNiveau->addWidget(lineNiveau);
    layoutNiveau->addWidget(boutonFichier);

    groupNiveau = new QGroupBox("Fichier de niveaux");
    groupNiveau->setToolTip("Changer de fichier de niveaux de jeu vous permet de jouer et de créer vos propres niveaux, laissant l'aventure originale intacte.\n\nImportant : l'éditeur de niveaux emploiera ce nouveau fichier");
    groupNiveau->setLayout(layoutNiveau);

    labelPersonnage = new QLabel("Sprite Personnage");
    boutonPersonnage = new QPushButton("Parcourir");
    connect(boutonPersonnage, SIGNAL(clicked()),this,SLOT(setImagePersonnage()));
    linePersonnage = new QLineEdit(personnage);
    layoutPersonnage = new QHBoxLayout;
    layoutPersonnage->addWidget(labelPersonnage);
    layoutPersonnage->addWidget(linePersonnage);
    layoutPersonnage->addWidget(boutonPersonnage);

    labelFond = new QLabel("Sprite Fond");
    lineFond = new QLineEdit(fond);
    boutonFond = new QPushButton("Parcourir");
    connect(boutonFond, SIGNAL(clicked()),this,SLOT(setImageFond()));
    layoutFond = new QHBoxLayout;
    layoutFond->addWidget(labelFond);
    layoutFond->addWidget(lineFond);
    layoutFond->addWidget(boutonFond);

    labelWall = new QLabel("Sprite Mur");
    lineWall = new QLineEdit(mur);
    boutonWall = new QPushButton("Parcourir");
    connect(boutonWall, SIGNAL(clicked()),this,SLOT(setImageMur()));
    layoutWall = new QHBoxLayout;
    layoutWall->addWidget(labelWall);
    layoutWall->addWidget(lineWall);
    layoutWall->addWidget(boutonWall);

    labelObjectif = new QLabel("Sprite Objectif");
    lineObjectif = new QLineEdit(objectif);
    boutonObjectif = new QPushButton("Parcourir");
    connect(boutonObjectif, SIGNAL(clicked()),this,SLOT(setImageObjectif()));
    layoutObjectif = new QHBoxLayout;
    layoutObjectif->addWidget(labelObjectif);
    layoutObjectif->addWidget(lineObjectif);
    layoutObjectif->addWidget(boutonObjectif);

    labelCaisse = new QLabel("Sprite Caisse");
    lineCaisse = new QLineEdit(caisse);
    boutonCaisse = new QPushButton("Parcourir");
    connect(boutonCaisse, SIGNAL(clicked()),this,SLOT(setImageCaisse()));
    layoutCaisse = new QHBoxLayout;
    layoutCaisse->addWidget(labelCaisse);
    layoutCaisse->addWidget(lineCaisse);
    layoutCaisse->addWidget(boutonCaisse);

    labelCaisseOk = new QLabel("Sprite Caisse Rouge");
    lineCaisseOk = new QLineEdit(caisse_ok);
    boutonCaisseOk = new QPushButton("Parcourir");
    connect(boutonCaisseOk, SIGNAL(clicked()),this,SLOT(setImageCaisseOk()));

    layoutCaisseOk = new QHBoxLayout;
    layoutCaisseOk->addWidget(labelCaisseOk);
    layoutCaisseOk->addWidget(lineCaisseOk);
    layoutCaisseOk->addWidget(boutonCaisseOk);

    layoutSprites = new QVBoxLayout;
    layoutSprites->addLayout(layoutPersonnage);
    layoutSprites->addLayout(layoutFond);
    layoutSprites->addLayout(layoutWall);
    layoutSprites->addLayout(layoutObjectif);
    layoutSprites->addLayout(layoutCaisse);
    layoutSprites->addLayout(layoutCaisseOk);
    boxSprites = new QGroupBox("Changer les images de jeu");
    boxSprites->setLayout(layoutSprites);
    boxSprites->setToolTip("Lassé par le graphisme ?\nJouez avec vos propres sprites (images de jeu)");

    labelGauche = new QLabel("Gauche : ");
    comboGauche = new QComboBox;
    comboGauche->addItem("A");
    comboGauche->addItem("4");
    comboGauche->addItem("Q");

    labelDroite = new QLabel("Droite : ");
    comboDroite = new QComboBox;
    comboDroite->addItem("D");
    comboDroite->addItem("6");

    labelHaut = new QLabel("Haut : ");
    comboHaut = new QComboBox;
    comboHaut->addItem("W");
    comboHaut->addItem("8");
    comboHaut->addItem("Z");

    labelBas = new QLabel("Bas : ");
    comboBas = new QComboBox;
    comboBas->addItem("S");
    comboBas->addItem("2");

    layoutCombo = new QHBoxLayout;
    layoutCombo->addWidget(labelGauche);
    layoutCombo->addWidget(comboGauche);
    layoutCombo->addWidget(labelDroite);
    layoutCombo->addWidget(comboDroite);
    layoutCombo->addWidget(labelHaut);
    layoutCombo->addWidget(comboHaut);
    layoutCombo->addWidget(labelBas);
    layoutCombo->addWidget(comboBas);
    groupCombo = new QGroupBox("Configuration des touches");
    groupCombo->setLayout(layoutCombo);

    boutonCancel = new QPushButton("Annuler");
    connect(boutonCancel,SIGNAL(clicked()),this,SLOT(close()));
    boutonValider = new QPushButton("Valider");
    connect(boutonValider, SIGNAL(clicked()), this, SLOT(check()));
    defaultButton = new QPushButton("Par défaut");
    connect(defaultButton, SIGNAL(clicked()),this,SLOT(reglagesDefaut()));

    layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(boutonValider);
    layoutBoutons->addWidget(defaultButton);
    layoutBoutons->addWidget(boutonCancel);
    layout->addWidget(groupNiveau);
    layout->addWidget(boxSprites);
    layout->addWidget(groupCombo);
    layout->addLayout(layoutBoutons);
}
void Options::check()
{
    QString listFile;
    listFile = lineNiveau->text() + " ";
    listFile += linePersonnage->text() + " ";
    listFile += lineFond->text() + " ";
    listFile += lineWall->text() + " ";
    listFile += lineObjectif->text() + " ";
    listFile += lineCaisse->text() + " ";
    listFile += lineCaisseOk->text() + " ";
    listFile += comboGauche->currentText() + " ";
    listFile += comboDroite->currentText() + " ";
    listFile += comboHaut->currentText() + " ";
    listFile += comboBas->currentText() + " ";

    QFile fichier(QApplication::applicationDirPath()+"/config/config.cfg");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream flux(&fichier);
        flux << listFile;
        fichier.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }
    QMessageBox::information(this,"Information","Les changements seront pris en compte au prochain lancement de l'application.");
    this->close();
}
void Options::setNiveaux()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir un fichier de niveaux...","config","Fichiers de niveaux (*.lvl);; Tous les fichiers (*.*)");
    lineNiveau->setText(chemin);
}
void Options::setImagePersonnage()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    linePersonnage->setText(chemin);
}
void Options::setImageObjectif()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    lineObjectif->setText(chemin);
}
void Options::setImageFond()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    lineFond->setText(chemin);
}
void Options::setImageMur()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    lineWall->setText(chemin);
}
void Options::setImageCaisse()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    lineCaisse->setText(chemin);
}
void Options::setImageCaisseOk()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Choisir une image","images","Images (*.jpg *.png *.gif);; Tous les fichiers (*.*)");
    lineCaisseOk->setText(chemin);
}
void Options::reglagesDefaut()
{
    linePersonnage->setText("images/explorer_bas.png");
    lineObjectif->setText("images/objectif.png");
    lineFond->setText("images/sand.png");
    lineWall->setText("images/wall.png");
    lineCaisse->setText("images/caisse.png");
    lineCaisseOk->setText("images/caisse_ok.png");
    lineNiveau->setText("config/niveaux.lvl");
    comboGauche->setCurrentIndex(0);
    comboDroite->setCurrentIndex(0);
    comboHaut->setCurrentIndex(0);
    comboBas->setCurrentIndex(0);
}
void Options::setGraphs()
{
    QString chaine;
    QFile fichier("config/config.cfg");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        chaine = fichier.readLine();
        niveau = chaine.split(" ")[0];
        personnage = chaine.split(" ")[1];
        fond = chaine.split(" ")[2];
        mur = chaine.split(" ")[3];
        objectif = chaine.split(" ")[4];
        caisse = chaine.split(" ")[5];
        caisse_ok = chaine.split(" ")[6];
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Fichier .cfg indisponible");
    }
}

