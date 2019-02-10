#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <iostream>
#include <QUrlQuery>
#include <windows.h>

#define BASE_WIDTH 200
#define BASE_HEIGHT 70
#define CONTROLS_MODE_HEIGHT 150
#define EDIT_MODE_HEIGHT 130
#define ANIMATION_DURATION 600
#define UPDATE_INTERVAL 15000
#define X_COORD_OFFSET 200
#define Y_COORD_OFFSET 200

class FenPrincipale : public QWidget
{
    Q_OBJECT

    public:
    FenPrincipale();
    QString sendRequest();
    int getNumberOfPlayers(QString HTTPresponse);
    void intelligence(int nbPlayers);
    int updateStatus();
    int saveToFile(QString path, QString payload);
    int readDATFile(QString path);
    void sayHello();
    void initURL();
    void initBasePath();
    void launchOnStartUp();
    bool isFirstLaunch();
    void firstLaunch();

    int timerId;
    int x;
    int y;

    protected:
    void timerEvent(QTimerEvent *event);

    public slots:
    void toggleGroupBoxVisibility();
    void toggleEditModeVisibility();
    void toggleFocus();
    void minimizeWindow();
    void onRightClicked();
    void editURL();

    private slots:
    void mousePressEvent(QMouseEvent *e);

    signals:
    void rightClicked();

    private:
    QLabel *label;
    QPushButton *quitter;
    QPushButton *focus;
    QPushButton *minimize;
    QPushButton *edit;
    QCheckBox *checkBox;
    QGroupBox *groupBox;

    QLineEdit *url;
    QPushButton *buttonURL;
    QGroupBox *editGroupBox;

    bool isOnTop;
    QString path;
    QString appPath;

};

#endif
