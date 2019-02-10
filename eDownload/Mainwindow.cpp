#include "Mainwindow.h"

MainWindow::MainWindow()
{
    buildInterface();
    buildMenu();

    setFixedSize(396,425);
    setWindowTitle("eDownloader");
}
void MainWindow::buildMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
}
void MainWindow::buildInterface()
{
    boutonTelecharger = new QPushButton("Télécharger");
    connect(boutonTelecharger,SIGNAL(clicked()),this,SLOT(tryDownload()));
    lineAdresse = new QLineEdit("www.siteduzero.com/forum.html");
    label = new QLabel();
    layoutPrincipale = new QHBoxLayout;
    layoutPrincipale->addWidget(lineAdresse);
    layoutPrincipale->addWidget(boutonTelecharger);
    layoutPrincipale->addWidget(label);

    groupeInterface = new QGroupBox("Application",this);
    groupeInterface->setLayout(layoutPrincipale);
    groupeInterface->setGeometry(10,30,330,60);
}
void MainWindow::tryDownload()
{
    QString str = lineAdresse->text();
    if(str.length() < 3)
    {
        QMessageBox::critical(this,"Erreur","Vous devez entrer une adresse valide");
        return;
    }
    else
    {
        QString s = "/"+str.split("/")[1];
        QString v = str.split("/")[0];
//        QHttpRequestHeader httpHeader("GET",s);
//        httpHeader.setValue("Host",QUrl(v).host());
//        http = new QHttp();
//        http->setHost(v);
//        http->request(httpHeader);
//        http->get(s);
//        QMessageBox::information(0, "Erreur", s+" "+v);
//        connect(http, SIGNAL(done(bool)), this, SLOT(chargementTermine(bool)));
//        connect(http,SIGNAL(dataReadProgress(int,int)),this,SLOT(chargement(int,int)));
        manager = new QNetworkAccessManager();
        // L'Url du fihier à télécharger
        QMessageBox::information(0, "lllll",QUrl(str).toString());

        // Demande du download
        manager->get(QNetworkRequest(QUrl(str)));
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(chargement(QNetworkReply *)));
    }
}
void MainWindow::chargementTermine(bool erreur)
{
    if(erreur)
        QMessageBox::information(0, "Erreur", QString::number(http->error()));
    else
    {
        QMessageBox::critical(this,"e",http->readAll());
        //        QString fileName = QFileDialog::getSaveFileName(0, "Sauvegarder",
        //                                    "untitled.txt", "Fichiers textes (*.txt);; Tous les fichiers (*.*)");
        //        QFile file(fileName);
        //        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        //        {
        //           QTextStream out(&file);
        //           out << http->readAll();
        //           file.close();
        //        }
        //        else
        //        {
        //            QMessageBox::critical(this, "Erreur", "Impossible d'enregistrer le fichier");
        //           return;
        //        }

    }
}
void MainWindow::chargement(QNetworkReply *rep)
{
    page = new QFile(".\\truc.txt");
    page->open(QIODevice::WriteOnly);
    page->write(rep->readAll());
    page->close();
    QMessageBox::information(this,"eee",rep->readAll());
}
