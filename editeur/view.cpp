#include "view.h"
#include <QMouseEvent>
#include <QtGui>
View::View(QWidget *parent) : QGraphicsView(parent)
{
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
                str = "sand.png";
            carte[X][Y] = scene->addPixmap(QPixmap(str));
            carte[X][Y]->setPos(X*32,Y*32);
            if(str=="sand.png")
                map[X][Y]='0';
            else if(str == "wall.png")
                map[X][Y]='1';
            else if(str == "caisse.jpg")
                map[X][Y]='2';
            else if(str == "objectif.png")
                map[X][Y]='3';
            else if(str == "explorer_bas.png")
                map[X][Y]='4';
            else if(str == "caisse_ok.jpg")
                map[X][Y]='5';
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
                str = "sand.png";
            carte[X][Y] = scene->addPixmap(QPixmap(str));
            carte[X][Y]->setPos(X*32,Y*32);
            if(str=="sand.png")
                map[X][Y]='0';
            else if(str == "wall.png")
                map[X][Y]='1';
            else if(str == "caisse.jpg")
                map[X][Y]='2';
            else if(str == "objectif.png")
                map[X][Y]='3';
            else if(str == "explorer_bas.png")
                map[X][Y]='4';
            else if(str == "caisse_ok.jpg")
                map[X][Y]='5';
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
