#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent);
private slots:
    void buildInterface();
    void choisirDossier();
    void extractFile();
    QString getChemin();
    void setChemin(QString chemin);
    void rename();

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
    QCheckBox *checkbox2;
    QRadioButton *up;
    QRadioButton *low;
    QRadioButton *no;
    QPushButton *fermer;
    QPushButton *boutonChanger;


};

#endif // WINDOW_H
