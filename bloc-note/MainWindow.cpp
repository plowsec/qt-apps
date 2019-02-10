#include "MainWindow.h"
#include "ZoneTexte.h"
#include "window.h"
#include "Codegenerator.h"
#include "Myframe.h"
#include "dialog.h"

MainWindow::MainWindow()
{
    //===BARRES D'ETAT/D'OUTILS===
    barreEtat = statusBar();
    barreEtat->showMessage("Prêt");
    toolBarFichier = addToolBar("Fichier");

    //===ZONE PRINCIPALE===
    zoneCentrale = new QMdiArea;
    zoneCentrale->setViewMode(QMdiArea::TabbedView);
    setCentralWidget(zoneCentrale);

    //===MENU FICHIER===
    menuFichier = menuBar()->addMenu("&Fichier");

    //NOUVEAU
    actionNouveau = menuFichier->addAction("Nouveau");
    actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(nouveauDocument()));

    actionNouveau->setIcon(QIcon("nouveau.png"));
    toolBarFichier->addAction(actionNouveau);

    //OUVRIR
    actionOuvrir = menuFichier->addAction("Ouvrir");
    actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrirDoc()));

    actionOuvrir->setIcon((QIcon("ouvrir.png")));
    toolBarFichier->addAction(actionOuvrir);

    //ENREGISTRER
    actionEnregistrer = menuFichier->addAction("Enregistrer");
    actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(saveFile()));

    actionEnregistrer->setIcon((QIcon("save.png")));
    toolBarFichier->addAction(actionEnregistrer);

    //ENREGISTRER SOUS
    actionEnregistrerSous = menuFichier->addAction("Enregistrer sous...");
    connect(actionEnregistrerSous, SIGNAL(triggered()), this, SLOT(enregistrerSous()));

    //IMPRIMER
    actionImprimer = menuFichier->addAction("Imprimer");
    actionImprimer->setShortcut(QKeySequence("Ctrl+P"));
    connect(actionImprimer, SIGNAL(triggered()), this, SLOT(print()));



    //QUITTER
    actionQuitter = menuFichier->addAction("Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    //===MENU EDITION===
    menuEdition = menuBar()->addMenu("&Edition");
    annuler = new QAction(QIcon("undo.png"), "Annuler", this);
    annuler->setShortcut(QKeySequence::Undo);
    annuler->setStatusTip("Annule la dernière action");
    connect(annuler, SIGNAL(triggered()), this, SLOT(annulerAction()));

    couper = new QAction(QIcon("cut.png"), "Couper", this);
    couper->setShortcut(QKeySequence::Cut);
    couper->setStatusTip("Coupe le texte sélectionné");
    connect(couper, SIGNAL(triggered()), this, SLOT(couperSelection()));

    copier = new QAction(QIcon("copy.png"), "Copier", this);
    copier->setShortcut(QKeySequence::Copy);
    copier->setStatusTip("Copie le texte sélectionné");
    connect(copier, SIGNAL(triggered()), this, SLOT(copierSelection()));

    coller = new QAction(QIcon("paste.png"), "Coller", this);
    coller->setShortcut(QKeySequence::Paste);
    coller->setStatusTip("Colle le texte sélectionné");
    connect(coller, SIGNAL(triggered()), this, SLOT(collerSelection()));


    menuEdition->addAction(annuler);
    menuEdition->addAction(couper);
    menuEdition->addAction(copier);
    menuEdition->addAction(coller);

    //===MENU OUTIL===
    menuLangage = menuBar()->addMenu("&Outils");
    actionOpenProgr = menuLangage->addAction("Listing de fichiers");
    connect(actionOpenProgr, SIGNAL(triggered()), this, SLOT(execProgr()));
    actionOpenProgrSecond = menuLangage->addAction("Générateur de code");
    connect(actionOpenProgrSecond, SIGNAL(triggered()), this, SLOT(execProgrSecond()));

    actionOpenProgrTer = menuLangage->addAction("Horloge");
    connect(actionOpenProgrTer,SIGNAL(triggered()),this,SLOT(execProgrTer()));

    //===MENU FORMAT===
    menuFormat = menuBar()->addMenu("&Format");
    actionChoixPolice = menuFormat->addAction("Police...");
    connect(actionChoixPolice, SIGNAL(triggered()), this, SLOT(choisirPolice()));

    gras = new QAction(QIcon("bold.png"), "Gras", this);
    gras->setShortcut(QKeySequence::Bold);
    gras->setStatusTip("Mode gras");
    gras->setCheckable(true);
    connect(gras, SIGNAL(triggered()), this, SLOT(modeGras()));

    italique = new QAction(QIcon("italic.png"), "Italique", this);
    italique->setShortcut(QKeySequence::Italic);
    italique->setStatusTip("Mode italique");
    italique->setCheckable(true);
    connect(italique, SIGNAL(triggered()), this, SLOT(modeItalique()));

    souligne = new QAction(QIcon("underline.png"), "Souligné", this);
    souligne->setShortcut(QKeySequence::Underline);
    souligne->setStatusTip("Mode souligné");
    souligne->setCheckable(true);
    connect(souligne, SIGNAL(triggered()), this, SLOT(modeSoulignge()));

    menuFormat->addAction(gras);
    menuFormat->addAction(italique);
    menuFormat->addAction(souligne);

    //===MENU AFFICHAGE===
    menuAffichage = menuBar()->addMenu("&Affichage");
    actionChoixCouleurFond = menuAffichage->addAction("Couleur de fond");
    connect(actionChoixCouleurFond, SIGNAL(triggered()), this, SLOT(changeBackGroundColor()));

    //===MENU AIDE===
    menuAide = menuBar()->addMenu("A&ide");
    actionOpenAbout = menuAide->addAction("A propos");
    connect(actionOpenAbout, SIGNAL(triggered()),this,SLOT(execAbout()));

    boxPolice = new QFontComboBox;
    boxPolice->setCurrentFont(QFont("Courier"));

    connect(boxPolice, SIGNAL(currentFontChanged(QFont)), this, SLOT(boxPoliceEnCours(QFont)));
    taillePolice = new QSpinBox;
    taillePolice->setMinimum(1);
    taillePolice->setMaximum(72);
    taillePolice->setValue(10);
    connect(taillePolice, SIGNAL(valueChanged(int)), this, SLOT(taillePoliceEnCours(int)));

    setWindowTitle("Notepad");
    setWindowIcon(QIcon("icone.png"));

    toolBarFichier->addSeparator();
    toolBarFichier->addAction(annuler);
    toolBarFichier->addAction(couper);
    toolBarFichier->addAction(copier);
    toolBarFichier->addAction(coller);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(gras);
    toolBarFichier->addAction(italique);
    toolBarFichier->addAction(souligne);
    toolBarFichier->addSeparator();
    toolBarFichier->addWidget(boxPolice);
    toolBarFichier->addWidget(taillePolice);
}

void MainWindow::nouveauDocument()
{
    ZoneTexte *nouveauDoc = new ZoneTexte;
    zoneCentrale->addSubWindow(nouveauDoc);
    nouveauDoc->show();
    nouveauDoc->setTitre("Nouveau");

    QFile fichier("config.cfg");
    if(!fichier.exists())
        nouveauDoc->setStyleSheet("background-color:#eefff0");
    else
    {
        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            nouveauDoc->setStyleSheet(fichier.readLine());
            fichier.close();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier config.");
            return;
        }
    }
}

void MainWindow::ouvrirDoc()
{
   QString chemin;
   chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", chemin, "Fichiers textes (*.txt);; Tous les fichiers (*.*)");
   QFile file(chemin);

   if(file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       ZoneTexte *ouverture = new ZoneTexte;
       ouverture->setEmplacement(chemin);
       zoneCentrale->addSubWindow(ouverture);
       ouverture->setHtml(file.readAll());
       ouverture->show();
       QFileInfo nomFichier(file);
       zoneCentrale->currentSubWindow()->setWindowTitle(nomFichier.fileName());

       QFile fichier("config.cfg");
       if(!fichier.exists())
          ouverture->setStyleSheet("background-color:#eefff0");
       else
       {
           if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               ouverture->setStyleSheet(fichier.readLine());
               fichier.close();
           }
           else
           {
               QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier config.");
               return;
           }
       }
       file.close();
   }
   else
   {
       QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier.");
       return;
   }
}

void MainWindow::enregistrerSous()
{
     ZoneTexte *save = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
     save->enregistrer();
}

void MainWindow::saveFile()
{
    ZoneTexte *savedFile = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());

    if(savedFile->getEmplacement().isEmpty())
    {
        MainWindow::enregistrerSous();
    }

    else
    {
        QString chemin = savedFile->getEmplacement();
        savedFile->saveAlreadyExist(chemin);
    }
}

void MainWindow::print()
{
     ZoneTexte *print = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
     print->imprimerTexte();
}

void MainWindow::choisirPolice()
{
    bool ok = false;
    ZoneTexte *texte = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    QFont police = QFontDialog::getFont(&ok, texte->font(), this, "Choisissez une police");

    if (ok)
    {
        texte->setFont(police);
        boxPolice->setCurrentFont(police);
        taillePolice->setValue(police.pointSize());
        texte->setFontPointSize(police.pointSize());
    }
}

void MainWindow::changeBackGroundColor()
{
    ZoneTexte *texte = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    QColor couleur = QColorDialog::getColor(Qt::white, this);
    QString color = "background-color: " + couleur.name() + ";";
    texte->setStyleSheet(color);

    QFile fichier("config.cfg");
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream flux(&fichier);
    flux << color;

    fichier.close();
}

void MainWindow::boxPoliceEnCours(const QFont police)
{
    ZoneTexte*font = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    font->setFont(police);
}

void MainWindow::taillePoliceEnCours(const int taille)
{
    ZoneTexte *size = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    size->setFontPointSize(taille);
}

void MainWindow::annulerAction()
{
    ZoneTexte *annuler = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    annuler->undo();
}

void MainWindow::couperSelection()
{
    ZoneTexte *couper = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    couper->cut();
}

void MainWindow::copierSelection()
{
    ZoneTexte *copier = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    copier->copy();
}

void MainWindow::collerSelection()
{
    ZoneTexte *coller = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());
    coller->paste();
}

void MainWindow::modeItalique()
{
    ZoneTexte *italic = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());

    if (italique->isChecked())
        italic->setFontItalic(true);
    else if (!italique->isChecked())
        italic->setFontItalic(false);
}

void MainWindow::modeGras()
{
    ZoneTexte *bold = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());

    if (gras->isChecked())
        bold->setFontWeight(QFont::Bold);
    else if (!gras->isChecked())
        bold->setFontWeight(QFont::Normal);
}

void MainWindow::modeSoulignge()
{
    ZoneTexte *underline = qobject_cast<ZoneTexte *>(zoneCentrale->currentSubWindow()->widget());

    if (souligne->isChecked())
        underline->setFontUnderline(true);
    else if (!souligne->isChecked())
        underline->setFontUnderline(false);
}
void MainWindow::execProgr()
{
    Window *fen = new Window(this);
    fen->show();

}
void MainWindow::execProgrSecond()
{
    CodeGenerator *fen = new CodeGenerator();

    fen->show();

}
void MainWindow::execProgrTer()
{
    MyFrame *fr = new MyFrame(this);
    fr->show();
}
void MainWindow::execAbout()
{
    Dialog *di = new Dialog(this);
    di->exec();
}
