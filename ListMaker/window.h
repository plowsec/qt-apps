#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
private slots:
    void buildMenu();
    void buildInterface();
    void choisirDossier();
    void extractFile();
    QString getChemin();
    void setChemin(QString chemin);
    void save();
    QString getText();
    void setText(QString text);
    void ouvrirAPropos();
private:
    QLineEdit *champ_path;
    QPushButton *boutonChoisir;
    QPushButton *boutonAction;
    QTextEdit *champText;
    QString cheminDossier;
    QString textFinal;
    QGroupBox *groupeInterface;
    QGroupBox *groupeOptions;
    QVBoxLayout *layout1;
    QHBoxLayout *layoutPrincipale;
    QCheckBox *checkbox1;
    QRadioButton *up;
    QRadioButton *low;
    QRadioButton *no;


};

#endif // WINDOW_H
