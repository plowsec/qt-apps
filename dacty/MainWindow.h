#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
   MainWindow();
public slots:
   void buildInterface();
   void build();
   bool eventFilter(QObject *obj, QEvent *event);
   QString transformText(QString chemin);
private :
   QMdiArea *zoneCentrale;
   QMenu *menuFichier;
   QAction *actionNouveau;
   QAction *actionQuitter;
   QLineEdit *text;
   QLineEdit *text1;
   QLineEdit *text2;
   QTextEdit *text3;
   QPushButton *boutonCommencer;
   QLineEdit *textt;
   int n;
   QString ch;
};

#endif // MAINWINDOW_H
