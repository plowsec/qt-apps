#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
MainWindow::MainWindow()
{
    label = new QLabel("Entrez le lien de la vidéo youtube", this);
    line = new QLineEdit(this);
    boutonOK = new QPushButton("OK", this);
    text = new QTextEdit(this);
    textTag = new QTextEdit(this);

    layoutText = new QHBoxLayout();
    layoutText->addWidget(text);
    layoutText->addWidget(textTag);

    layoutH = new QHBoxLayout();
    layoutH->addWidget(line);
    layoutH->addWidget(boutonOK);

    layoutV = new QVBoxLayout();
    layoutV->addWidget(label);
    layoutV->addLayout(layoutH);
    layoutV->addLayout(layoutText);
    setLayout(layoutV);
    setMinimumHeight(600);

    connect(boutonOK, SIGNAL(clicked()), this, SLOT(getLinks()));

}
void MainWindow::getLinks()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    manager->get(QNetworkRequest(QUrl("http://www.youtube.com/watch?v=OuSdU8tbcHY")));
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(result(QNetworkReply *)));
}

void MainWindow::result(QNetworkReply *reply)   {
    QString html = reply->readAll();
    QString t = html.toLatin1();
    QRegExp re("\"url_encoded_fmt_stream_map\": \"([^\"]*)\"", Qt::CaseInsensitive, QRegExp::RegExp2);
    QRegExp urls("itag");
    QRegExp n("http");
    QRegExp m("(itag=\\d{1,3})");
    if (re.indexIn(t) != -1) {
        QString result = re.cap(1);
        foreach (QString line, result.split("\\u0026")) {
            if (urls.indexIn(QUrl::fromPercentEncoding(line.toLatin1())) != -1) {
                QString res = QUrl::fromPercentEncoding(line.toLatin1());
                if(n.indexIn(res) )   {
                    if(res.length()>50) {
                        text->setText(text->toPlainText()+"\n\n\n\n"+res.mid(4));
                        if(m.indexIn(res))  {
                            textTag->setText(textTag->toPlainText()+"\n"+m.cap(1));
                        }
                    }
                }
            }
        }
    }
    showLabels();
}
void MainWindow::showLabels()   {
    groupBox = new QGroupBox("Liste des formats disponibles");
    layoutBox = new QVBoxLayout();
    QStringList b = textTag->toPlainText().split("\n");
    int i =0;
    for(i=0;i<b.length();i++)   {
        if(i==0)
            continue;
        boxes[i] = new QRadioButton(b[i], this);
        layoutBox->addWidget(boxes[i]);
    }
    groupBox->setLayout(layoutBox);
    layoutV->addWidget(groupBox);
}
