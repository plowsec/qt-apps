#include "MainWindow.h"
MainWindow::MainWindow()
{
    buildInterface();
}
void MainWindow::buildInterface()
{
    n = 0;
    ch = "";
    setMinimumSize(600,270);
    setWindowTitle("Dactylo");
    setWindowIcon(QIcon("accueil.png"));
    menuFichier = menuBar()->addMenu("&Fichier");
    actionNouveau = menuFichier->addAction("Exercice");
    actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
    connect(actionNouveau, SIGNAL(triggered()),this,SLOT(build()));

    actionQuitter = menuFichier->addAction("Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    text = new QLineEdit(this);
    text1 = new QLineEdit(this);
    text2 = new QLineEdit(this);
    text3 = new QTextEdit(this);
    QFont serifFont("Times", 10, QFont::Bold);

    text->setDisabled(true);
    text1->setReadOnly(true);
    text2->setDisabled(true);
    text->setGeometry(10,30,500,25);
    text1->setGeometry(10,55,500,25);
    text2->setGeometry(10,80,500,25);
    text3->setGeometry(10,135,500,80);
    text3->setDisabled(true);
    text->setFont(serifFont);
    text1->setFont(serifFont);
    text2->setFont(serifFont);
    text3->installEventFilter(this);

    boutonCommencer = new QPushButton("Commencer",this);
    boutonCommencer->setDisabled(true);
    boutonCommencer->setGeometry(10,230,80,30);

}
void MainWindow::build()
{
    QString chemin;
    chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", chemin, "Fichiers textes (*.txt)");
    QString fichierTexte = transformText(chemin).split("\n");
    text->setText(fichierTexte[0]);
    text1->setText(fichierTexte[1]);
    text2->setText(fichierTexte[2]);
    text3->setDisabled(false);
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(text1->text().isEmpty())
        return false;
    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
        if(c && c->key() == Qt::Key_Shift)
        {
            return false;
        }
        else
        {
            QString str = text3->toPlainText();
            if(str.length()==text1->text().length())
            {
                QMessageBox::information(this,"info","Ligne terminée!");
                return false;
            }
            if(text1->text()[n] == str[n])
            {
                n++;
                ch = text1->text().left(n);
            }
            else
            {
                text3->undo();
                QTextCursor textCursor = text3->textCursor();
                text3->setPlainText(ch);
                text3->setTextCursor(textCursor);
            }
        }
    }
    return false;
}
QString MainWindow::transformText(QString chemin)
{
    QString fichierTexte = "";
    QFile file(chemin);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString txt = file.readAll();
        QString txt2 = txt.replace("\n"," ");
        while(!txt2.isEmpty())
        {
            if(txt2.length() >= 100)
            {
                QString str = txt2.left(txt2.left(100).lastIndexOf(" "));
                txt2.remove(0,str.length());
                fichierTexte += str.trimmed()+"\n";
            }
            else
            {
                QString qw = txt2;
                txt2.remove(0,txt2.length());
                fichierTexte += qw.trimmed();
                QMessageBox::information(this,"e","fini!!!"+qw);
            }
        }
        return fichierTexte;
    }
}
