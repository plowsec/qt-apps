#ifndef MAIN_H
#define MAIN_H

#include <QtGui>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
public slots:
    void reroll();
    void compare();
    void getContent();
    void choisirFichier();
    void getConfig();
private:
QGraphicsScene *scene;
QGraphicsItem *image;
QRadioButton *radio1;
QRadioButton *radio2;
QRadioButton *radio3;
QPushButton *jouer;
QLineEdit *line;
QPushButton *ok;
QPushButton *change;
int index;
QLabel *label;
QString formules;
QString img;
QString formulesOLL;
QString formulesPLL;
QString imgOLL;
QString imgPLL;
QString cheminConfig;

};

#endif // MAIN_H
