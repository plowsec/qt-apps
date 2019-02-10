#ifndef MAIN_H
#define MAIN_H

#include <QtGui>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
public slots:
    void traiter();
    void formater();
    void compter();

private:
    QTextEdit* tex;
    QTextEdit *tex2;
    QPushButton* button;
    QVBoxLayout *layout;

    QHBoxLayout *layoutRadio;
    QRadioButton *radioDonnes;
    QRadioButton *radioCompter;
    QGroupBox* groupRadio;
};
#endif // MAIN_H
