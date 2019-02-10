#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
private slots:
    void buildMenu();
    void buildHorloge();
    void updateHorloge();
    void setAiguilles();
    void clearAiguilles();
    void setSong();
    void setPath(QString cheminFichier);
    QString getPath();
    void isTime();



private:
    QVBoxLayout *layout;
    QTimeEdit *time;
    QTimeEdit *timeAlarme;
    QLabel *label;
    QLabel *label2;
    QPushButton *bouton;
    QMenu *menuFichier;
    QMenu *menuAction;
    QMenu *menuAbout;
    QAction *actionQuitter;
    QAction *actionSon;
    QAction *actionAbout;
    QGraphicsScene *scene;
    QPushButton *boutonQuitter;
    QGraphicsItem *aiguilleTroteuse;
    QGraphicsItem *petiteAiguille;
    QGraphicsItem *grandeAiguille;
    QGraphicsItem *point;
    QTimer *timer;
    QGraphicsItem *fond;
    QGraphicsItem *chiffre6;
    QGraphicsItem *chiffre9;
    QGraphicsItem *chiffre12;

    QString path;
    bool isPath;
    QSound *alarme;


};

#endif // WINDOW_H
