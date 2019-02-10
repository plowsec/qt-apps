#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QtWidgets>
#include <QtGui>

class Options : public QDialog
{
    Q_OBJECT
public:
    Options(QWidget *parent = 0);
private slots:
    void buildInterface();
    void check();
    void setNiveaux();
    void setImagePersonnage();
    void setImageObjectif();
    void setImageFond();
    void setImageMur();
    void setImageCaisse();
    void setImageCaisseOk();
    void reglagesDefaut();
    void setGraphs();
private:
    QVBoxLayout *layout;
    QHBoxLayout *layoutNiveau;
    QGroupBox *groupNiveau;
    QPushButton *boutonFichier;
    QLabel *labelNiveau;
    QLineEdit *lineNiveau;
    QGroupBox *boxSprites;
    QVBoxLayout *layoutSprites;
    QHBoxLayout *layoutPersonnage;
    QLabel *labelPersonnage;
    QPushButton *boutonPersonnage;
    QLineEdit *linePersonnage;
    QHBoxLayout *layoutFond;
    QLabel *labelFond;
    QPushButton *boutonFond;
    QLineEdit *lineFond;
    QHBoxLayout *layoutWall;
    QLabel *labelWall;
    QPushButton *boutonWall;
    QLineEdit *lineWall;
    QHBoxLayout *layoutObjectif;
    QLabel *labelObjectif;
    QPushButton *boutonObjectif;
    QLineEdit *lineObjectif;
    QHBoxLayout *layoutCaisse;
    QLabel *labelCaisse;
    QPushButton *boutonCaisse;
    QLineEdit *lineCaisse;
    QHBoxLayout *layoutCaisseOk;
    QLabel *labelCaisseOk;
    QPushButton *boutonCaisseOk;
    QLineEdit *lineCaisseOk;
    QPushButton *boutonCancel;
    QPushButton *boutonValider;
    QHBoxLayout *layoutBoutons;
    QPushButton *defaultButton;
    QComboBox *comboGauche;
    QComboBox *comboDroite;
    QComboBox *comboHaut;
    QComboBox *comboBas;
    QLabel *labelGauche;
    QLabel *labelDroite;
    QLabel *labelHaut;
    QLabel *labelBas;
    QHBoxLayout *layoutCombo;
    QGroupBox *groupCombo;


    QString fond;
    QString mur;
    QString personnage;
    QString caisse;
    QString caisse_ok;
    QString objectif;
    QString niveau;

};

#endif // OPTIONS_H
