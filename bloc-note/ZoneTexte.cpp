#include "ZoneTexte.h"


ZoneTexte::ZoneTexte() : QTextEdit()
{
    emplacement = "";
}

void ZoneTexte::setTitre(QString titre)
{
    this->setWindowTitle(titre);
}

void ZoneTexte::enregistrer()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Save File",
                                "untitled.txt", "Fichiers textes (*.txt);; Tous les fichiers (*.*)");
    ZoneTexte::setEmplacement(fileName);
    QFileInfo nomFile(fileName);
    this->setWindowTitle(nomFile.fileName());
    QFile file(fileName);
       file.open(QIODevice::WriteOnly);
       QTextStream out(&file);
       out << this->toHtml();
       file.close();
}

void ZoneTexte::saveAlreadyExist(QString nomFichier)
{
    QFile file(nomFichier);
    if(file.open(QIODevice::WriteOnly))
    {
       QTextStream out(&file);
       out << this->toHtml();
       file.close();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'enregistrer le fichier");
       return;
    }
}

QString ZoneTexte::getEmplacement()
{
    return emplacement;
}

void ZoneTexte::setEmplacement(QString chemin)
{
    emplacement = chemin;
}

void ZoneTexte::imprimerTexte()
{
    QPrinter printer;
    QTextDocument doc;
    QString TE = this->toHtml();
    doc.setHtml(TE);

     QPrintDialog *dialog = new QPrintDialog(&printer, this);
     dialog->setWindowTitle(tr("Print Document"));

     if (this->textCursor().hasSelection())
         dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);

     if (dialog->exec() == QDialog::Accepted)
         doc.print(&printer);
         return;
}
