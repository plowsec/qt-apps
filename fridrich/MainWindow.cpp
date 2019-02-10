#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("Memorizator");
    setWindowIcon(QIcon("img/icone.png"));
    index=1;
    formulesOLL="";
    formulesPLL="";
    imgOLL="";
    imgPLL="";
    formules="";
    img="";
    getConfig();
    getContent();
    scene = new QGraphicsScene;
    scene->setSceneRect(-150,-150,70,70);
    QString ch = "img/51.png";
    image = scene->addPixmap(QPixmap(ch));
    image->setPos(-150,-150);
    QGraphicsView *vue = new QGraphicsView(scene, this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setGeometry(100,20, 100,100);
    radio1 = new QRadioButton("OLL",this);
    radio1->setGeometry(10,10,100,20);
    radio1->setChecked(true);
    radio2 = new QRadioButton("PLL",this);
    radio2->setGeometry(10,40,100,20);
    radio3 = new QRadioButton("Both",this);
    radio3->setGeometry(10,70,100,20);
    jouer = new QPushButton("Reroll",this);
    jouer->setGeometry(10,140,80,25);
    connect(jouer,SIGNAL(clicked()),this,SLOT(reroll()));
    line = new QLineEdit(this);
    line->setGeometry(100,140,100,25);
    line->setFocus();
    ok = new QPushButton("OK",this);
    ok->setGeometry(205,140,25,20);
    connect(ok, SIGNAL(clicked()), this, SLOT(compare()));
    label = new QLabel(this);
    label->setGeometry(100,170,130,50);
    change = new QPushButton("Parcourir...",this);
    change->setGeometry(10,100,80,25);
    connect(change, SIGNAL(clicked()),this, SLOT(choisirFichier()));
}
void MainWindow::getConfig()
{
    QFile file("config.cfg");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cheminConfig=file.readLine();

    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichigdgfgfer config.");
        return;
    }
}

void MainWindow::choisirFichier()
{
    QString chemin;
    chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", chemin, "Fichiers CFG (*.cfg);; Tous les fichiers (*.*)");
    QFile file("config.cfg");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream flux(&file);
    flux << chemin;

    file.close();
    cheminConfig=chemin;
    formulesOLL="";
    formulesPLL="";
    imgOLL="";
    imgPLL="";
    formules="";
    img="";
    getContent();
    line->setFocus();

}

void MainWindow::getContent()
{
    //QString chemin;
    //chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", chemin, "Fichiers CFG (*.cfg);; Tous les fichiers (*.*)");
    QFile file(cheminConfig);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString chaineOLL =file.readLine().replace("\n","");
        for(int i=0;i<chaineOLL.split("#").length();i++)
        {
            formulesOLL+=chaineOLL.split("#")[i].split("@")[0]+"%";
            imgOLL+="img/"+chaineOLL.split("#")[i].split("@")[1]+"%";
        }

        QString chainePLL = file.readLine().replace("\n","");;
        for(int i=0;i<chainePLL.split("#").length();i++)
        {
            formulesPLL+=chainePLL.split("#")[i].split("@")[0]+"%";
            imgPLL+="img/"+chainePLL.split("#")[i].split("@")[1]+"%";
        }
        formules=formulesOLL+formulesPLL;
        img = imgOLL+imgPLL;
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }
}

void MainWindow::compare()
{
    if(formules.split("%")[index]==line->text())
    {
        label->setText("<font color=\"green\"><b>Correct !</b></font>");
        ok->setEnabled(false);
    }
    else if(index==3 and line->text()=="FRU'R'U'RUR'F'RUR'U'R'FRF'")
    {
        label->setText("<font color=\"green\"><b>Correct !</b></font>");
        ok->setEnabled(false);
    }
    else
    {
        label->setText("<font color=\"red\"><b>Incorrect ! Rép: </b><br/>"+formules.split("%")[index]+"</font>");
    }
    line->setFocus();
}

void MainWindow::reroll()
{
    index = 0;
    ok->setEnabled(true);
    label->setText("");
    line->setText("");
    if(radio1->isChecked())
    {
        index = qrand()%(imgOLL.split("%").length()-1);//-1 à cause de qrand, -1 à cause que la string finit par %
        scene->removeItem(image);
        image = scene->addPixmap(QPixmap(imgOLL.split("%")[index]));
        image->setPos(-150,-150);
        //line->setText(QString::number(index)+" "+imgOLL.split("%")[index]);
    }
    else if(radio2->isChecked())
    {
       index = qrand()%(imgPLL.split("%").length()-2)+imgOLL.split("%").length();
       scene->removeItem(image);
       image = scene->addPixmap(QPixmap(img.split("%")[index]));
       image->setPos(-150,-150);
    }
    else
    {
        index = qrand()%(imgOLL.split("%").length()+imgPLL.split("%").length()-2);
        scene->removeItem(image);
        image = scene->addPixmap(QPixmap(img.split("%")[index]));
        image->setPos(-150,-150);
        //line->setText(QString::number(index)+" "+img.split("%")[index]);

    }
    line->setFocus();
}
