#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtNetwork>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void buildMenu();
    void buildInterface();
    void tryDownload();
    void chargementTermine(bool);
    void chargement(QNetworkReply *rep);
private:
    QMenu *menuFichier;
    QAction *actionQuitter;
    QGroupBox *groupeInterface;
    QPushButton *boutonTelecharger;
    QLineEdit *lineAdresse;
    QHBoxLayout *layoutPrincipale;
    QHttp *http;
    QLabel *label;
    QFile *page;
    QNetworkAccessManager * manager;
};

#endif // MAINWINDOW_H
