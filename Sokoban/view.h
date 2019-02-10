#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QtWidgets>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);

public slots:
    void setStr(QString str);
    QString getStr();
    QString getMap();
    void setGraphs();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGraphicsItem *carte[12][12];
    QGraphicsScene *scene;
    QString file;
    QChar map[12][12];

    QString Fond;
    QString Mur;
    QString Personnage;
    QString Caisse;
    QString Caisse_ok;
    QString Objectif;
    QString Niveau;
};

#endif // VIEW_H
