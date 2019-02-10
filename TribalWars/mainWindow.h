#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include "District.h"
#include "Joueur.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void mousePressEvent(QMouseEvent *me);
public slots:
    void setValeur2(int i);
private slots:
    void jouer();
    void quitter();
private:
QTextEdit *text;
QGraphicsScene *scene;
QGraphicsItem *fond;
QImage *image;
QColor *a;
QColor *b;
int count;
QString names[32];
int QG[6];
District *zones[32];
Joueur *joueurs[5];

QLabel *labels[32];
QPushButton *boutonJouer;
QPushButton *boutonQuitter;
int continuer;
int valeur2;
int leftCliked;


};

#endif // MAINWINDOW_H
