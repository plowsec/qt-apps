#include "mainWindow.h"
#include "Joueur.h"
#include "District.h"
#include "QuartierGeneral.h"
#include "Dialog.h"
MainWindow::MainWindow()
{
    setFixedSize(650,350);
    scene = new QGraphicsScene;
    scene->setSceneRect(-150,-150,520,330);

    fond = scene->addPixmap(QPixmap("Map_jeu.png"));
    fond->setPos(-150,-150);
    fond->setZValue(1);
    image = new QImage("Map_color.png");

    boutonJouer = new QPushButton("Jouer",this);
    boutonQuitter = new QPushButton("Quitter",this);
    boutonJouer->setGeometry(540,30,100,25);
    boutonQuitter->setGeometry(540,60,100,25);

    connect(boutonJouer,SIGNAL(clicked()),this,SLOT(jouer()));
    connect(boutonQuitter,SIGNAL(clicked()),this,SLOT(quitter()));
    text = new QTextEdit(this);
    text->setGeometry(540,100,100,200);

    QGraphicsView *vue = new QGraphicsView(scene, this);
    vue->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    vue->setGeometry(0,0, 530, 340);
    count =1;
    QString namesPasBons[32]={"0","#ff0000","#ff7300","#ffba00","#96ff00","#ccff00","#fcff00","#6c00ff",
                              "#d800ff","#ff00fd","#4200ff","#2aff00","#003cff","#00ff96","#00fff0","#007eff",
                              "#00baff","#ff004e","#fcfafa","#ff0072","#ff00c6","#c3c1c2","#a7a7a7","#929292",
                              "#7a7979","#ae00ff","#8a00ff","#4a4848","#5d5a5b","#353333","#232121","#dcdadb"};
    QString coords[32][2]={
                        {"0","0"},{"71","98"},{"229","44"},{"322","21"},{"330","56"},
                        {"385","54"},{"443","65"},{"397","96"},{"361","119"},{"286","125"},
                        {"289","96"},{"272","68"},{"202","133"},{"185","82"},{"115","105"},
                        {"147","147"},{"64","174"},{"132","181"},{"129","241"},{"189","196"},
                        {"231","163"},{"239","207"},{"289","212"},{"316","170"},{"375","178"},
                        {"421","137"},{"465","162"},{"435","218"},{"405","174"},{"303","264"},
                        {"254","257"},{"193","265"}};

    for(int i=0;i<32;i++)
    {
        names[i]=namesPasBons[i];
    }

    int QGs[6]={9,5,13,17,28,30};

    int all_voisins[32][5]=
    {
        {0,0,0,0,0},{2,14,13,16},{1,13,11,3,0},{2,4,5,6,0},{10,11,3,5,7},{3,4,6,7,0},
        {7,5,3,25,0},{5,4,6,8,25},{10,9,7,25,23},{10,8,23,20,12},{9,12,11,4,7},{2,10,14,13,4},
        {9,10,14,15,20},{1,2,11,14,0},{11,15,13,12,1},{16,14,17,19,12},{1,15,17,18,0},
        {15,16,19,18,0},{31,19,17,16,0},{17,20,15,18,21},{19,12,9,21,23},{20,19,31,30,22},
        {21,30,29,23,24},{22,9,6,24,20},{23,22,27,28,25},{24,28,26,7,8},{25,27,28,6,0},
        {29,24,28,26,0},{24,25,26,27,0},{30,22,27,31,0},{31,29,22,21,0},{18,21,30,29,0}
    };
    for(int z=0;z<32;z++)
    {
        zones[z] = new District(z);
        for(int w=0;w<5;w++)
            zones[z]->setVoisins(all_voisins[z][w],w);
    }
    for(int j=0;j<6;j++)
    {
        QG[j]=QGs[j];
        if(j!=0)
        {
            zones[QG[j]]->setJoueur(j);
            zones[QG[j]]->setTroupes(15);
            joueurs[j] = new Joueur("Joueur "+QString::number(j),zones[QG[j]]->getId());
         }
    }
    for(int k=1;k<32;k++)
    {
        labels[k]= new QLabel(this);
        labels[k]->setGeometry(coords[k][0].toInt(),coords[k][1].toInt(),25,25);
        if(zones[k]->getTroupes()>0)
        {
            labels[k]->setStyleSheet("background-image : url(label.png) ; qproperty-alignment: AlignCenter;");
            labels[k]->setText("<font color=\"#FFFFFF\">"+QString::number(zones[k]->getTroupes())+"</font>");
        }
        //text->setText(text->toPlainText()+coords[k][0]+";"+coords[k][1]+"\n");
    }
    leftCliked = 0;
}

void MainWindow::jouer()
{
    continuer = 1;
    while(continuer)
    {

    }

}
void MainWindow::quitter()
{
    continuer =0;
    this->close();

}
void MainWindow::setValeur2(int i)
{
    valeur2=i;
}

void MainWindow::mousePressEvent(QMouseEvent *me)
{
    int index=0;
    int bol=0;

    if(me->button()==Qt::LeftButton)
    {

        text->setText(text->toPlainText()+QString::number(me->pos().x())+";"+QString::number(me->pos().y())+"\n");

        a = new QColor(image->pixel(me->pos()));
        for(int i=0; i<32;i++)
        {
            if(a->name()==names[i])
            {
                index = i;
                leftCliked = i;
                break;
            }
        }
    }
    else if(me->button()==Qt::RightButton && leftCliked!=0)
    {
        int in =0;
        Dialog *dialog = new Dialog(zones[leftCliked],this);
        dialog->exec();
        valeur2 = dialog->recup();
        b = new QColor(image->pixel(me->pos()));
        for(int i=0; i<32;i++)
        {
            if(b->name()==names[i])
            {
                in = i;
                break;
            }
        }
        //debug
        text->setText(text->toPlainText()+"ID Joueur Origine : "+QString::number(zones[leftCliked]->getJoueur())+"\n");
        text->setText(text->toPlainText()+"ID Joueur Destination : "+QString::number(zones[in]->getJoueur())+"\n");

        //fin debug
        zones[leftCliked]->deplacer(valeur2,zones[in]);
        labels[leftCliked]->setText("<font color=\"#FFFFFF\">"+QString::number(zones[leftCliked]->getTroupes())+"</font>");
        labels[in]->setStyleSheet("background-image : url(label.png) ; qproperty-alignment: AlignCenter;");
        labels[in]->setText("<font color=\"#FFFFFF\">"+QString::number(zones[in]->getTroupes())+"</font>");
    }
}
//        for(int j =0;j<6;j++)
//        {
//            if(index==QG[j])
//            {
//                bol=1;
//                break;
//            }
//        }
//        if(bol==1)
//            text->setText(text->toPlainText()+"Quartier Général numéro "+QString::number(index)+"\n");
//        else
//            text->setText(text->toPlainText()+"Zone numéro "+QString::number(index)+"\n");
//        count++;
    //#00ff96 (1) #ccff00 (2) #5d5a5b (3) #232121 (4) #ff004e (5) #fd00fd (centre)


