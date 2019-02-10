#include "view.h"
#include "window.h"
#include <QMouseEvent>
#include <QtGui>
View::View(QWidget *parent) : QGraphicsView(parent)
{
    setGraphs();
    scene = new QGraphicsScene;
    this->setScene(scene);
}
void View::mousePressEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->button()==Qt::LeftButton)
    {
        if(mouseEvent->pos().x() >= 380)
            return;
        else if(mouseEvent->pos().y() >= 380)
            return;
        else
        {
            int x = mouseEvent->pos().x();
            int y = mouseEvent->pos().y();
            int X = x/32;
            int Y = y/32;
            QString str;
            if(getStr().length()>3)
                str = getStr();
            else
                str = Fond;
            carte[X][Y] = scene->addPixmap(QPixmap(str));
            carte[X][Y]->setPos(X*32,Y*32);
            if(str == Fond)
                map[X][Y] = '0';
            else if(str == Mur)
                map[X][Y] = '1';
            else if(str == Caisse)
                map[X][Y] = '2';
            else if(str == Objectif)
                map[X][Y] = '3';
            else if(str == Personnage)
                map[X][Y]  ='4';
            else if(str == Caisse_ok)
                map[X][Y]  ='5';
        }
    }
}
void View::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() & Qt::LeftButton))
    {
        if(mouseEvent->pos().x() >= 380)
            return;
        else if(mouseEvent->pos().y() >= 380)
            return;
        else
        {
            int x = mouseEvent->pos().x();
            int y = mouseEvent->pos().y();
            int X = x/32;
            int Y = y/32;
            QString str;
            if(getStr().length()>3)
                str = getStr();
            else
                str = Fond;
            carte[X][Y] = scene->addPixmap(QPixmap(str));
            carte[X][Y]->setPos(X*32,Y*32);
            if(str == Fond)
                map[X][Y] = '0';
            else if(str == Mur)
                map[X][Y] = '1';
            else if(str == Caisse)
                 map[X][Y] = '2';
            else if(str == Objectif)
                map[X][Y] = '3';
            else if(str == Personnage)
                map[X][Y]  ='4';
            else if(str == Caisse_ok)
                map[X][Y]  ='5';
            QWidget::mouseMoveEvent(mouseEvent);
        }
    }
}
void View::setStr(QString str)
{
    file = str;
}
QString View::getStr()
{
    return file;
}
QString View::getMap()
{
    QString str="";
    for(int i = 0 ; i < 12 ; i++)
    {
        for(int j = 0 ; j < 12 ; j++)
        {
            str+= map[i][j];
        }
    }
    return str;
}
void View::setGraphs()
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

