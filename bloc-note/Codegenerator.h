#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <QtGui>

class CodeGenerator : public QWidget
{
    Q_OBJECT

public:
    CodeGenerator();
public slots:
    void code();
private:
    QFormLayout *formLayout;
    QGroupBox *groupeHeader;
    QGroupBox *groupeOptions;
    QGroupBox *groupeCommentaires;

    QLineEdit *nom;
    QLineEdit *classeMere;

    QVBoxLayout *boxOptions;
    QCheckBox *checkbox1;
    QCheckBox *checkbox2;
    QCheckBox *checkbox3;

    QFormLayout *formLayout2;
    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *role;

    QHBoxLayout *boxBoutons;
    QPushButton *generer;
    QPushButton *quitter;

    QVBoxLayout *layoutPrincipale;

};

#endif // CODEGENERATOR_H
