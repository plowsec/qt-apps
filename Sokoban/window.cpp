#include "window.h"
#include "editeur.h"
#include "options.h"

Window::Window()
{
    setGraphs();
    buildMenu();
    buildInterface();
    setFixedSize(396,425);
    setWindowTitle("Sokoban");
    setWindowIcon(QIcon("icone.png"));



}
void Window::buildMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    menuEdition = menuBar()->addMenu("&Outils");
    actionEditor = menuEdition->addAction("&Créer un niveau...");
    connect(actionEditor, SIGNAL(triggered()),this,SLOT(execEditor()));

    actionOptions = menuEdition->addAction("Réglages...");
    connect(actionOptions,SIGNAL(triggered()),this,SLOT(execOptions()));

    menuTriche = menuBar()->addMenu("&Triche");

    actionRecommencer = menuTriche->addAction("&Recommencer");
    actionRecommencer->setShortcut(QKeySequence("Ctrl+R"));
    connect(actionRecommencer, SIGNAL(triggered()),this,SLOT(recommencer()));

    actionNiveauSuivant = menuTriche->addAction("Niveau suivant");
    connect(actionNiveauSuivant, SIGNAL(triggered()),this,SLOT(chargerNiveauSuivant()));

    actionNiveauPrecedent = menuTriche->addAction("Niveau précédent");
    connect(actionNiveauPrecedent, SIGNAL(triggered()),this,SLOT(chargerNiveauPrecedent()));

    menuTriche->addSeparator();
    actionAnnuler = menuTriche->addAction("Annuler le coup");
    connect(actionAnnuler,SIGNAL(triggered()),this,SLOT(annuler()));

    menuAide = menuBar()->addMenu("?");
    actionAide = menuAide->addAction("Aide");
    connect(actionAide,SIGNAL(triggered()),this,SLOT(aide()));
    barre = statusBar();
}
void Window::buildInterface()
{
    scene = new QGraphicsScene;
    chargerNiveau(getLvl());
//    keyPressEvent(event);
    QGraphicsView *vue = new QGraphicsView(scene, this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setGeometry(5,20,386,386);
}
void Window::keyPressEvent(QKeyEvent *event)
{

    switch(event->key())
    {
        //gauche
    case Qt::Key_A:
        if(chaine.split(" ")[7] == "A")
            deplacerJoueur(-1,0);
        break;
    case Qt::Key_Q:
        if(chaine.split(" ")[7] == "Q")
            deplacerJoueur(-1,0);
        break;
    case Qt::Key_Left:
        deplacerJoueur(-1,0);
        break;
    case Qt::Key_4:
        if(chaine.split(" ")[7] == "4")
            deplacerJoueur(-1,0);
        break;
        //droite
    case Qt::Key_D:
        if(chaine.split(" ")[8] == "D")
            deplacerJoueur(1,0);
        break;
    case Qt::Key_Right:
        deplacerJoueur(1,0);
        break;
    case Qt::Key_6:
        if(chaine.split(" ")[8] == "6")
            deplacerJoueur(1,0);
        break;
        //haut
    case Qt::Key_W:
        if(chaine.split(" ")[9] == "W")
            deplacerJoueur(0,-1);
        break;
    case Qt::Key_Up:
        deplacerJoueur(0,-1);
        break;
    case Qt::Key_8:
        if(chaine.split(" ")[9] == "8")
            deplacerJoueur(0,-1);
        break;
    case Qt::Key_Z:
        if(chaine.split(" ")[9] == "Z")
            deplacerJoueur(0,-1);
        break;
        //bas
    case Qt::Key_S:
        if(chaine.split(" ")[10] == "S")
            deplacerJoueur(0,1);
        break;
    case Qt::Key_Down:
        deplacerJoueur(0,1);
        break;
    case Qt::Key_2:
        if(chaine.split(" ")[10] == "2")
            deplacerJoueur(0,1);
        break;
    case Qt::Key_Escape:
        qApp->quit();
        break;
    }
}
void Window::deplacerJoueur(int X, int Y)
{
    int x = getPosX()/32;
    int y = getPosY()/32;
    int obj=0;

    if(map[x+X][y+Y].toLatin1() == '1')
        return;
    if(Y>0)
    {
        if((getPosY()+32)>386)
           return;
    }
    else if(Y<0)
    {
        if((getPosY()-32)<0)
           return;
    }
    else if(X<0)
    {
        if((getPosX()-32)<0)
           return;
    }
    else if(X>0)
    {
        if((getPosX()+32)>=384)
           return;
    }
    if((map[x+X][y+Y].toLatin1() == '2' || map[x+X][y+Y].toLatin1() == '5') && (map[x+2*X][y+2*Y].toLatin1() == '1' || map[x+X*2][y+Y*2].toLatin1() == '2' || map[x+2*X][y+Y*2].toLatin1() == '5'))
        return;
    if(map[x+X][y+Y].toLatin1() == '3')
    {
        setOldPosXY(x+X,y+Y);
    }
    scene->removeItem(carte[getPosX()/32][getPosY()/32]);
    scene->removeItem(carte[(getPosX()/32)+X][(getPosY()/32)+Y]);

    if((getOldPosX() == x && getOldPosY() == y) || map[x][y]=='3')
    {
        carte[getPosX()/32][getPosY()/32] = scene->addPixmap(QPixmap(objectif));
        carte[getPosX()/32][getPosY()/32]->setPos(getPosX(),getPosY());
    }
    else
    {
        carte[getPosX()/32][getPosY()/32] = scene->addPixmap(QPixmap(fond));
        carte[getPosX()/32][getPosY()/32]->setPos(getPosX(),getPosY());
    }

    for(int q=0;q<12;q++)
    {
        for (int w=0;w<12;w++)
        {
            if(map[q][w] == '4')
                mapSauvegarde[q][w] = '0';
            else
                mapSauvegarde[q][w] = map[q][w];
        }
    }
    mapSauvegarde[x][y] = '4';
    if(map[x+X][y+Y].toLatin1() == '2' || map[x+X][y+Y].toLatin1() == '5') //déplacement des caisses
    {
        if (map[x+2*X][y+2*Y].toLatin1() == '3') //objectif
        {
            map[x+2*X][y+2*Y] = '5';
            carte[getPosX()/32+2*X][(getPosY()/32)+2*Y] = scene->addPixmap(QPixmap(caisse_ok));
            carte[getPosX()/32+2*X][(getPosY()/32)+2*Y]->setPos(getPosX()+(2*X*32),getPosY()+(2*Y*32));
        }
        else
        {
            map[x+2*X][y+2*Y] = '2';
            carte[getPosX()/32+2*X][(getPosY()/32)+2*Y] = scene->addPixmap(QPixmap(caisse));
            carte[getPosX()/32+2*X][(getPosY()/32)+2*Y]->setPos(getPosX()+(2*X*32),getPosY()+(2*Y*32));
        }

        if (map[x+X][y+Y].toLatin1() == '5') //caisse_ok
        {
            map[x+X][y+Y] = '3'; //objectif
            setOldPosXY(x+X,y+Y);
            carte[getPosX()/32+X][(getPosY()/32)+Y] = scene->addPixmap(QPixmap(objectif));
            carte[getPosX()/32+X][(getPosY()/32)+Y]->setPos(getPosX()+(X*32),getPosY()+(Y*32));

        }
        else
        {
            map[x+X][y+Y] = '0';
            carte[getPosX()/32+X][(getPosY()/32)+Y] = scene->addPixmap(QPixmap(fond));
            carte[getPosX()/32+X][(getPosY()/32)+Y]->setPos(getPosX()+(X*32),getPosY()+(Y*32));
        }
    }
    carte[getPosX()/32+X][(getPosY()/32)+Y] = scene->addPixmap(QPixmap(personnage));
    carte[getPosX()/32+X][(getPosY()/32)+Y]->setPos(getPosX()+(X*32),getPosY()+(Y*32));

    setRelativePosXY(X*32,Y*32);
    nombreCoups++;

    for(int h=0;h<12;h++)
    {
        for (int z=0;z<12;z++)
        {
            if(map[h][z].toLatin1()=='3')
            {
                obj++;
            }
        }
    }
    if(obj==0)
    {
        actionAnnuler->setEnabled(false);
        QMessageBox::information(this, "Félicitations !", "Niveau terminé !\nScore : "+QString::number(nombreCoups) + " coups");
        setNiveau(getLvl()+1);
        chargerNiveau(getLvl());
    }
    else
        actionAnnuler->setEnabled(true);
    return;
}
void Window::setPosXY(int x, int y)
{
    posX = x;
    posY = y;

}
void Window::setRelativePosXY(int x, int y)
{
    posX += x;
    posY += y;
}

int Window::getPosX()
{
    return posX;
}
int Window::getPosY()
{
    return posY;
}
int Window::getOldPosX()
{
    return oldPosX;
}
int Window::getOldPosY()
{
    return oldPosY;
}
void Window::setOldPosXY(int x, int y)
{
    oldPosX = x;
    oldPosY = y;
}
void Window::setNiveau(int c)
{
    QFile fichier("config/lvl.lvl");
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream flux(&fichier);
    flux << c;

    fichier.close();
}
int Window::getLvl()
{
    QString ch;
    QFile fichier("config/lvl.lvl");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ch = fichier.readLine();
        fichier.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier .lvl.");
        return false;
    }
    return ch.toInt();
}
void Window::chargerNiveau(int ch)
{
    QString str;
    QString bigStr;
    QFile file(niveau);
    nombreCoups = 0;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        bigStr = file.readAll();
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier de niveau(1)."+niveau);
        return;
    }
    if(getLvl() >= compterNiveaux())
    {
        ch = 1;
        setNiveau(1);
        QMessageBox::information(this, "Congratulations !", "Vous avez terminé tous les niveaux !");
    }

    if(getLvl() == (compterNiveaux()-1))
        actionNiveauSuivant->setEnabled(false);
    else if(getLvl() <= 1)
    {
        actionNiveauPrecedent->setEnabled(false);
        actionNiveauSuivant->setEnabled(true);
    }
    else
    {
        actionNiveauPrecedent->setEnabled(true);
        actionNiveauSuivant->setEnabled(true);
    }

    str = bigStr.split("\n")[ch-1];

    for(int a = 0 ; a <= 12 ; a++)
    {
        for(int b = 0 ; b <= 12 ; b++)
        {
            map[a][b] = str[(a*12)+b];
        }
    }
    for(int i = 0 ; i < 384 ; i+=32 )
    {
        for(int j = 0 ; j < 384 ; j+=32)
        {
            switch( map[(j/32)][(i/32)].toLatin1())
            {
            case '0':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(fond));
                carte[j/32][i/32] ->setPos(j,i);
                break;
            case '1':
                carte[j/32][i/32] =  scene->addPixmap(QPixmap(mur));
                carte[j/32][i/32]->setPos(j,i);
                break;
            case '2':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(caisse));
                carte[j/32][i/32]->setPos(j,i);
                break;
            case '3':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(objectif));
                carte[j/32][i/32]->setPos(j,i);
                setOldPosXY(j/32,i/32);
                break;
            case '4':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(personnage));
                carte[j/32][i/32]->setPos(j,i);
                setPosXY(j,i);
                break;
            case '5':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(caisse_ok));
                carte[j/32][i/32]->setPos(j,i);
                break;
            }
        }
    }
    if(ch!=1)
        barre->showMessage(QString::number(ch)+"ème niveau");
    else
        barre->showMessage("Premier Niveau !");
    actionAnnuler->setEnabled(false);
}
void Window::execEditor()
{
    Editeur *ed = new Editeur(this);
    ed->show();
}

void Window::recommencer()
{
    chargerNiveau(getLvl());
}
int Window::compterNiveaux()
{
    QString bigStr;
    int g;
    QFile file(niveau);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        bigStr = file.readAll();
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier de niveau.");
        return false;
    }

    g =  bigStr.split("\n").length();
    return g;
}
void Window::chargerNiveauSuivant()
{
    setNiveau(getLvl()+1);
    chargerNiveau(getLvl());
}
void Window::chargerNiveauPrecedent()
{
    setNiveau(getLvl()-1);
    chargerNiveau(getLvl());
}
void Window::execOptions()
{
    Options *op = new Options(this);
    op->exec();
}
void Window::aide()
{
    QMessageBox::information(this,"Aide",
    "Sokoban v1.1\nBy Virza\n\nSokoban est un jeu traditionnel japonais.\n\nRègles du jeu (extrait de Wikipedia) :\n\nLe joueur doit ranger des caisses sur des cases cibles.\nIl peut se déplacer dans les quatre directions, et pousser (mais pas tirer) une seule caisse à la fois.\nUne fois toutes les caisses rangées (c'est parfois un vrai casse-tête), le niveau est réussi et le joueur passe au niveau suivant, plus difficile en général. \nL'idéal est de réussir avec le moins de coups possibles (déplacements et poussées). ");
}
void Window::setGraphs()
{
    QFile fichier(QApplication::applicationDirPath()+"/config.cfg");
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
        if (fichier.exists()){
                QMessageBox::critical(this,"Erreur","Yeaaaaaaaaah");
        }
        else{
            QMessageBox::critical(this,"Erreur","Fichier .cfg existe pas"+fichier.fileName());

        }

        QMessageBox::critical(this,"Erreur","Fichier .cfg indisponible"+QApplication::applicationDirPath());
    }
}
void Window::annuler()
{
    for(int i = 0 ; i < 384 ; i+=32 )
    {
        for(int j = 0 ; j < 384 ; j+=32)
        {
            switch( mapSauvegarde[(j/32)][(i/32)].toLatin1())
            {
            case '0':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(fond));
                carte[j/32][i/32] ->setPos(j,i);
                map[j/32][i/32] = '0';
                break;
            case '1':
                carte[j/32][i/32] =  scene->addPixmap(QPixmap(mur));
                carte[j/32][i/32]->setPos(j,i);
                break;
            case '2':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(caisse));
                map[j/32][i/32] = '2';
                carte[j/32][i/32]->setPos(j,i);
                break;
            case '3':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(objectif));
                carte[j/32][i/32]->setPos(j,i);
                map[j/32][i/32] = '3';
                setOldPosXY(j/32,i/32);
                break;
            case '4':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(personnage));
                carte[j/32][i/32]->setPos(j,i);
                setPosXY(j,i);
                break;
            case '5':
                carte[j/32][i/32] = scene->addPixmap(QPixmap(caisse_ok));
                carte[j/32][i/32]->setPos(j,i);
                map[j/32][i/32] = '5';
                break;
            }
        }
    }
    actionAnnuler->setEnabled(false);
}

