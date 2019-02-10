#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{

    isOnTop = true;
    initURL();
    initBasePath();

    //not neeeded on linux
    /*if(isFirstLaunch()==true)
        firstLaunch();*/

    label = new QLabel("Initializing...");

    quitter = new QPushButton("&Quitter");
    focus = new QPushButton("&Focus");
    minimize = new QPushButton("&Minimize");
    edit = new QPushButton("&Edit");


    url = new QLineEdit;
    buttonURL = new QPushButton("&OK");

    QHBoxLayout *boutonsLayoutTop = new QHBoxLayout;
    QHBoxLayout *boutonsLayoutBot = new QHBoxLayout;
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    QHBoxLayout *editLayout = new QHBoxLayout;

    boutonsLayoutTop->addWidget(focus);
    boutonsLayoutTop->addWidget(minimize);
    boutonsLayoutBot->addWidget(edit);
    boutonsLayoutBot->addWidget(quitter);

    groupBoxLayout->addLayout(boutonsLayoutTop);
    groupBoxLayout->addLayout(boutonsLayoutBot);

    editLayout->addWidget(url);
    editLayout->addWidget(buttonURL);

    checkBox = new QCheckBox("Show controls");

    connect(checkBox, SIGNAL(toggled(bool)),this, SLOT(toggleGroupBoxVisibility()));

    groupBox = new QGroupBox("Controls");
    groupBox->setLayout(groupBoxLayout);
    groupBox->setVisible(false);

    editGroupBox = new QGroupBox("Edit URL");
    editGroupBox->setLayout(editLayout);
    editGroupBox->setVisible(false);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(label);
    layoutPrincipal->addWidget(checkBox);
    layoutPrincipal->addWidget(groupBox);
    layoutPrincipal->addWidget(editGroupBox);

    setLayout(layoutPrincipal);

    setWindowTitle("zibuh");

    setFixedSize(BASE_WIDTH, BASE_HEIGHT);

    //removes Title bar and buttons (close, minimize, maximize) from window,
    setWindowFlags(Qt::CustomizeWindowHint);

    //removes borders from window and force the window to be always on top
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    connect(focus, SIGNAL(clicked(bool)), this, SLOT(toggleFocus()));
    connect(minimize, SIGNAL(clicked(bool)), this, SLOT(minimizeWindow()));
    connect(edit, SIGNAL(clicked(bool)), this, SLOT(toggleEditModeVisibility()));
    connect(buttonURL, SIGNAL(clicked(bool)), this, SLOT(editURL()));
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(onRightClicked()));

    //get coordinates of client screen
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();

    x = clientRect.bottomRight().x() - X_COORD_OFFSET;
    y = clientRect.bottomRight().y() - Y_COORD_OFFSET;

    //move the window to the bottom right corner of the client desktop
    move(x, y);

    int timerId = startTimer(UPDATE_INTERVAL);
}

void FenPrincipale::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
}
void FenPrincipale::onRightClicked()
{
    qDebug() << "User right clicked me";
    minimizeWindow();
}

void FenPrincipale::toggleGroupBoxVisibility()
{
    if(checkBox->isChecked())   {
        groupBox->setVisible(true);
        setFixedSize(BASE_WIDTH,CONTROLS_MODE_HEIGHT);
    }
    else    {
        groupBox->setVisible(false);
        setFixedSize(BASE_WIDTH,BASE_HEIGHT);
    }
}

void FenPrincipale::toggleEditModeVisibility()
{
    if(editGroupBox->isVisible())   {
        editGroupBox->setVisible(false);
        setFixedSize(BASE_WIDTH, BASE_HEIGHT);
        checkBox->setEnabled(true);
        checkBox->setChecked(false);
    }
    else    {
        groupBox->setVisible(false);
        editGroupBox->setVisible(true);
        setFixedSize(BASE_WIDTH, EDIT_MODE_HEIGHT);
        checkBox->setEnabled(false);
    }
}

void FenPrincipale::minimizeWindow()
{
    //showMinimized();

    //linux only : dirty patch of qt bug
   // showNormal();

    setWindowState(Qt::WindowMinimized);
}

void FenPrincipale::toggleFocus()
{
    Qt::WindowFlags flags = this->windowFlags();

    if(isOnTop == true) {
        setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | (flags ^ Qt::WindowStaysOnTopHint));
        isOnTop = false;
        this->show();
        qDebug() << "Im not on top";
    }
    else    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        isOnTop = true;
        this->show();
        qDebug() << "Im on top";
    }
}

void FenPrincipale::initBasePath()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);

    qDebug() << path;

    //change made for linux
    appPath = path + "/";

    //before the change :
    //appPath = path.replace("/", "\\") + "\\";
}

bool FenPrincipale::isFirstLaunch()
{
    QFileInfo fichier(appPath + "first_launch.dat");
    if(!fichier.exists())
        return true;
    return false;
}

/*
void FenPrincipale::firstLaunch()
{
    //not needed on linux
    launchOnStartUp();
    saveToFile(appPath + "first_launch.dat", "1");
}*/

void FenPrincipale::sayHello()
{
    qDebug() << "Entering sayHello";

    move(x+X_COORD_OFFSET, y);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    isOnTop = true;
    this->show();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(ANIMATION_DURATION);

    animation->setStartValue(QRect(x+X_COORD_OFFSET, y, BASE_WIDTH, BASE_HEIGHT));
    animation->setEndValue(QRect(x, y, BASE_WIDTH, BASE_HEIGHT));

    animation->start();
}

void FenPrincipale::initURL()
{
    QFile fichier(appPath + "config.cfg");

    if(!fichier.exists())   {
        path = QString("https://www.mtxserv.fr/viewer/game/minecraft/37.187.25.76/27330");
        return;
    }

    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text)) {
        label->setText("Couldn't open .cfg file");
        return;
    }

    QTextStream flux(&fichier);
    path = flux.readLine();

    fichier.close();
    return;
}

void FenPrincipale::editURL()
{
    if(!url->text().isEmpty())  {
        path = url->text();
        saveToFile(appPath + "config.cfg", path);
    }

    toggleEditModeVisibility();

}

/*
void FenPrincipale::launchOnStartUp()
{
    //windows specific
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    //get absolute path of running exe
    QString value = QCoreApplication::applicationFilePath();
    QString apostroph = "\"";

    value.replace("/","\\");
    value = apostroph + value + apostroph;

    //write value to the registry
    settings.setValue("Zibuh", value);
}*/

QString FenPrincipale::sendRequest()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req;
    req.setUrl(QUrl(path));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString HTTPresponse =  QString(reply->readAll());
        delete reply;

        return HTTPresponse;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        label->setText("Failed to fetch data");
        delete reply;

        return "failure";
    }
}
int FenPrincipale::getNumberOfPlayers(QString HTTPresponse) {

    int nbPlayers = 0;
    QStringList splitted = HTTPresponse.split("Joueurs</td>\n");

    if(splitted.size() == 2)    {
        nbPlayers = HTTPresponse.split("Joueurs</td>\n")[1].split("<td>")[1].split("</td>")[0].split("/")[0].toInt();
        return nbPlayers;
    }

    else    {
        label->setText("Pattern 'Joueurs</td>\n' not found");
        return -1;
    }

}

int FenPrincipale::saveToFile(QString path, QString payload)
{
    qDebug() << path;

    QFile fichier(path);

    if(!fichier.open(QIODevice::WriteOnly|QIODevice::Text)) {
        label->setText("Couldn't open .dat file");
        return -1;
    }

    QTextStream flux(&fichier);
    flux << payload;

    fichier.close();

    return 0;
}

int FenPrincipale::readDATFile(QString path)
{
    QFile fichier(path);
    int previousNbPlayers;

    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text)) {
        label->setText("Couldn't open .dat file");
        return -1;
    }

    QTextStream flux(&fichier);
    previousNbPlayers = flux.read(1).toInt();

    fichier.close();
    return previousNbPlayers;
}

void FenPrincipale::intelligence(int nbPlayers)
{
    QString path = appPath + "minecraft-watcher.dat";
    qDebug() << "Path : " << path;
    QFileInfo fichier(path);
    int previousNbPlayer = -1;

    if(!fichier.exists())   {

        if(saveToFile(path, QString::number(nbPlayers)) != 0)    {
            qDebug() << "Save to file failed\n";
            return;
        }
    }

    else    {

        previousNbPlayer = readDATFile(path);
    }

    qDebug() << "Previous : " << previousNbPlayer << "\nNow : " << nbPlayers << "\n";

    if(previousNbPlayer != nbPlayers)   {
        sayHello();
    }

    if(previousNbPlayer < 0 || previousNbPlayer > 2)    {

        switch(nbPlayers)   {

            case 1:
                label->setText("Player 1 joined the game");
                break;
            case 2:
                label->setText("Player 2 joined the game");
                break;
            default:
                label->setText("No one around");
                break;
        }
    }

    if(previousNbPlayer >= 0 && previousNbPlayer <=2)   {

        if(previousNbPlayer <= nbPlayers)    {

            switch(nbPlayers)   {

                case 1:
                    label->setText("Player 1 joined the game");
                    break;
                case 2:
                    label->setText("Player 2 joined the game");
                    break;
                default:
                    label->setText("No one around");
                    break;
            }
        }

        else    {

            label->setText("A player left the game");
        }
    }

    saveToFile(path, QString::number(nbPlayers));
}

QString FenPrincipale::curl()
{
    qDebug() << "cocuou";
    QProcess process;
    process.start("curl "+path);
    process.waitForFinished(-1);
    QByteArray out = process.readAllStandardOutput();
    return QString(out);
}

int FenPrincipale::updateStatus()
{
    int nbPlayers;


    //fetch stats form mtxserv.fr
    //change for linux :
    //QString httpResponse = sendRequest();
    QString httpResponse = curl();

    if(httpResponse == "failure")   {
        qDebug() << "failure";
        return -1;
    }

    //parse the HTTP response
    nbPlayers = getNumberOfPlayers(httpResponse);

    if(nbPlayers < 0)   {
        qDebug() << "nbPlayers bug : " << nbPlayers;
        return -1;
    }

    intelligence(nbPlayers);

    return 0;
}

void FenPrincipale::timerEvent(QTimerEvent *event)
{
    qDebug() << "Update...";
    updateStatus();
}
