#include "Mainwindow.h"

MainWindow::MainWindow()
{
    buildMenu();
    buildHorloge();

    setFixedSize(480,260);

    equation = new QLineEdit(this);
    equation->setGeometry(250,130,150,20);

    bouton = new QPushButton("Dessiner le graphique",this);
    bouton->setGeometry(250,170,150,20);
    connect(bouton,SIGNAL(clicked()),this,SLOT(dessiner()));

    boutonQuitter = new QPushButton("Quitter", this);
    boutonQuitter->setGeometry(250,210,150,20);
    connect(boutonQuitter, SIGNAL(clicked()),qApp,SLOT(quit()));

    setWindowTitle("GraphMaker");
    setWindowIcon(QIcon("icone.png"));
}

void MainWindow::buildMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuAction = menuBar()->addMenu("&Réglages");
    menuAbout = menuBar()->addMenu("?");

    actionQuitter = menuFichier->addAction("Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()),qApp, SLOT(quit()));

    actionAbout = menuAbout->addAction("Aide");
}

void MainWindow::buildHorloge()
{
    scene = new QGraphicsScene;
    scene->setSceneRect(-100,-100,200,200);

    QPen pen(Qt::red, 5);
    QPen pe(Qt::black,1);
    QBrush brush(Qt::red);
//    point = scene->addEllipse(-5,-5,10,10, pen, brush);
//    point->setZValue(4);
    line1 = scene->addLine(0,200,0,-200,pe);
    line2 = scene->addLine(-200,0,200,0,pe);



    QGraphicsView *vue = new QGraphicsView(scene, this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setStyleSheet("background-color: #FFFFFF");
    vue->setGeometry(10,30, 210, 210);
}
void MainWindow::dessiner()
{
    QRegExp rx("[a-z]");
    QString eq = equation->text();

    QString eqq = eq.split(rx)[0];
    double coefficient = eqq.toDouble();
    QPen pe(Qt::black,1);

    for(int i = -200 ; i < 200 ; i++)
    {
        //2x
        if(coefficient*i < 200 && coefficient*i > -200)
        {
            double z = -1*coefficient*i;
            scene->addEllipse(i,z,1,1,pe);
        }
    }
}
