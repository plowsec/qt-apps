#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
        Q_OBJECT

        public:
                MainWindow();
        public slots:
                void nouveauDocument();
                void ouvrirDoc();
                void enregistrerSous();
                void saveFile();
                void print();
                void choisirPolice();
                void changeBackGroundColor();
                void boxPoliceEnCours(const QFont police);
                void taillePoliceEnCours(const int taille);
                // Slots de Texte.
               void annulerAction();
               void couperSelection();
               void copierSelection();
               void collerSelection();
               void modeGras();
               void modeItalique();
               void modeSoulignge();
               void execProgr();
               void execProgrSecond();
               void execProgrTer();
               void execAbout();
        private:
                QMdiArea *zoneCentrale;
                QMenu *menuFichier;
                QMenu *menuEdition;
                QMenu *menuFormat;
                QMenu *menuAffichage;
                QMenu *menuLangage;
                QMenu *menuAide;
                QAction *actionNouveau;
                QAction *actionOuvrir;
                QAction *actionEnregistrer;
                QAction *actionEnregistrerSous;
                QAction *actionImprimer;
                QAction *actionQuitter;
                QToolBar *toolBarFichier;
                QFontComboBox *boxPolice;
                QSpinBox *taillePolice;
                QStatusBar *barreEtat;
                QAction *annuler;
                QAction *couper;
                QAction *copier;
                QAction *coller;
                QAction *gras;
                QAction *italique;
                QAction *souligne;
                QAction *actionChoixPolice;
                QAction *actionChoixCouleurFond;
                QAction *actionOpenProgr;
                QAction *actionOpenProgrSecond;
                QAction *actionOpenProgrTer;
                QAction *actionOpenAbout;
};

#endif // MAINWINDOW_H
