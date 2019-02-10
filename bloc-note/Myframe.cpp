#include "Myframe.h"

MyFrame::MyFrame(QWidget *parent) : QMainWindow(parent)

{
    buildMenu();
    buildHorloge();
    setAiguilles();

    setFixedSize(480,260);


    isPath=false;
    alarme = new QSound(getPath());
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()),this,SLOT(updateHorloge()));

    label = new QLabel("<b>Heure du système</b>",this);
    label->setGeometry(250,30,150,20);

    time = new QTimeEdit(QTime::currentTime(),this);
    time->setGeometry(250,60,150,20);
    time->setDisabled(true);

    label2 = new QLabel("Heure de l'alarme",this);
    label2->setGeometry(250,100,150,20);

    timeAlarme = new QTimeEdit(this);
    timeAlarme->setGeometry(250,130,150,20);

    bouton = new QPushButton("Stopper l'alarme",this);
    bouton->setGeometry(250,170,150,20);
    connect(bouton, SIGNAL(clicked()),alarme,SLOT(stop()));

    boutonQuitter = new QPushButton("Quitter", this);
    boutonQuitter->setGeometry(250,210,150,20);
    connect(boutonQuitter, SIGNAL(clicked()),this,SLOT(close()));

    setWindowTitle("Horloge");
    setWindowIcon(QIcon("icone.png"));

}

void MyFrame::buildMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuAction = menuBar()->addMenu("&Réglages");


    actionQuitter = menuFichier->addAction("Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()),this, SLOT(close()));

    actionSon = menuAction->addAction("Son...");
    connect(actionSon,SIGNAL(triggered()),this,SLOT(setSong()));


}

void MyFrame::buildHorloge()
{
    scene = new QGraphicsScene;
    scene->setSceneRect(-100,-100,200,200);

    QPen penTroteuse(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penGrandeAiguille(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penPetiteAiguille(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QPen pen(Qt::red, 5);
    QBrush brush(Qt::red);
    point = scene->addEllipse(-5,-5,10,10, pen, brush);

    aiguilleTroteuse = scene->addLine(0,0,0,-85,penTroteuse);
    petiteAiguille = scene->addLine(0,0,0,-30,penPetiteAiguille);
    grandeAiguille = scene->addLine(0,0,0,-60,penGrandeAiguille);

    fond = scene->addPixmap(QPixmap("horloge.png"));
    fond->setZValue(1);
    fond->setPos(-100,-100);

    aiguilleTroteuse->setZValue(2);
    petiteAiguille->setZValue(3);
    grandeAiguille->setZValue(4);
    point->setZValue(5);
    QGraphicsView *vue = new QGraphicsView(scene, this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setStyleSheet("background-color: #FFFFFF");
    vue->setGeometry(10,30, 210, 210);

}

void MyFrame::updateHorloge()
{
    time->setTime(QTime::currentTime());
    clearAiguilles();
    setAiguilles();
    isTime();
}

void MyFrame::setAiguilles()
{
    int heures = QTime::currentTime().hour();
    int minutes = QTime::currentTime().minute();
    int secondes = QTime::currentTime().second();
    petiteAiguille->rotate((0.0083333333 * secondes)+(0.5 * minutes) + (30 * heures));
    grandeAiguille->rotate((0.1*secondes)+(6*minutes));
    aiguilleTroteuse->rotate(secondes*6);
}
void MyFrame::clearAiguilles()
{
    petiteAiguille->resetTransform();
    grandeAiguille->resetTransform();
    aiguilleTroteuse->resetTransform();
}
void MyFrame::setSong()
{
    QString son = QFileDialog::getOpenFileName(this,"Choisissez un son...", QDir::homePath(),"Fichiers Audio (*.mp3 *.wav)");
    setPath(son);
    isPath = true;
    alarme = new QSound(son);
}
QString MyFrame::getPath()
{
    QString chemin;

    if(isPath)
    {
        chemin = path;
        return chemin;
    }
    else
    {
        chemin = "win1.wav";
        return chemin;
    }
}
void MyFrame::setPath(QString cheminFichier)
{
    path = cheminFichier;
}

void MyFrame::isTime()
{
    if(time->text()==timeAlarme->text())
    {
        alarme->setLoops(-1);
        alarme->play();
    }
}
