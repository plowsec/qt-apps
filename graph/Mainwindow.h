#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void buildMenu();
    void buildHorloge();
    void dessiner();
private:
    QVBoxLayout *layout;
    QLineEdit *equation;
    QPushButton *bouton;
    QMenu *menuFichier;
    QMenu *menuAction;
    QMenu *menuAbout;
    QAction *actionQuitter;
    QAction *actionSon;
    QAction *actionAbout;
    QGraphicsScene *scene;
    QPushButton *boutonQuitter;
    QGraphicsItem *point;
    QGraphicsItem *line1;
    QGraphicsItem *line2;
};

#endif // MAINWINDOW_H
