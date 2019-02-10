#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
private slots:
    void reset1();
    void addText(QString str);
    void remplir();
    void remplirLettres();
    QString listSymbols();
//    bool crypter(QString lettres);
    void solve();
    bool freeRow(int grilleTest[9][9], int n,int ligne);
    bool freeColumn(int grilleTest[9][9], int n, int colonne);
    bool freeBlock(int grilleTest[9][9] ,int n, int i, int j);
    bool Free(int grilleTest[9][9], int n, int i, int j);
    bool isValid(int grilleTest[9][9],int position);
private:
    QLineEdit *grille[9][9];
    QPushButton *boutonSolve;
    QPushButton *boutonScan;
    QLineEdit *symbols;
    QTextEdit *debug;
    QPushButton *boutonFill;
    QPushButton *boutonFillLettres;
    QLabel *label;
    int number;
    QString report;
    QCheckBox *box;


};

#endif // MAINWINDOW_H
