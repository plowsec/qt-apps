#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void result(QNetworkReply *reply);
    void getLinks();
    void showLabels();
private:
    QTextEdit *text;
    QTextEdit *textTag;
    QLabel *label;
    QLineEdit *line;
    QPushButton *boutonOK;
    QHBoxLayout *layoutH;
    QHBoxLayout *layoutText;
    QVBoxLayout *layoutV;
    QVBoxLayout *layoutBox;
    QRadioButton *boxes[10];
    QLabel *labels[10];
    QGroupBox *groupBox;

};

#endif // MAINWINDOW_H
