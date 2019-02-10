#include "MainWindow.h"
#include "Gen.h"

MainWindow::MainWindow()
{
    groupeHeader = new QGroupBox("Définition de la classe");
    nom = new QLineEdit;
    classeMere = new QLineEdit;

    formLayout = new QFormLayout;
    formLayout->addRow("&Nom : ", nom);
    formLayout->addRow("&Classe mère : ", classeMere);

    groupeHeader->setLayout(formLayout);

    groupeOptions = new QGroupBox("Options");
    boxOptions = new QVBoxLayout;
    checkbox1 = new QCheckBox("Protéger le header contre les inclusions multiples");
    checkbox2 = new QCheckBox("Générer un constructeur par défaut");
    checkbox3 = new QCheckBox("Générer un destructeur");
    checkbox1->setChecked(true);
    checkbox2->setChecked(true);

    boxOptions->addWidget(checkbox1);
    boxOptions->addWidget(checkbox2);
    boxOptions->addWidget(checkbox3);

    groupeOptions->setLayout(boxOptions);

    groupeCommentaires = new QGroupBox("Ajouter des commentaires");
    groupeCommentaires->setCheckable(true);
    groupeCommentaires->setChecked(true);

    auteur = new QLineEdit;
    date = new QDateEdit;
    date->setDate(QDate::currentDate());
    role = new QTextEdit;

    formLayout2 = new QFormLayout;
    formLayout2->addRow("A&uteur : ", auteur);
    formLayout2->addRow("Da&te de création : ", date);
    formLayout2->addRow("Rô&le : ", role);

    groupeCommentaires->setLayout(formLayout2);

    generer = new QPushButton("Générer");
    quitter = new QPushButton("Quitter");
    boxBoutons = new QHBoxLayout;
    boxBoutons->addWidget(generer);
    boxBoutons->addWidget(quitter);
    boxBoutons->setAlignment(Qt::AlignRight);
    layoutPrincipale = new QVBoxLayout;
    layoutPrincipale->addWidget(groupeHeader);
    layoutPrincipale->addWidget(groupeOptions);
    layoutPrincipale->addWidget(groupeCommentaires);
    layoutPrincipale->addLayout(boxBoutons);

    setLayout(layoutPrincipale);
    setWindowTitle("Code Generator");
    setWindowIcon(QIcon("icone.png"));

    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generer, SIGNAL(clicked()), this, SLOT(code()));
}

void MainWindow::code()
{
    QString code;

    if(nom->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un nom de classe");
        return;
    }

    if(groupeCommentaires->isChecked())
    {
        code+="/*\n";
        if(!auteur->text().isEmpty())
        {
            code+="Auteur : " + auteur->text()+"\n";
        }
        code+="Date de création : "+ date->date().toString("dd MMMM yyyy")+"\n";

        if(!role->toPlainText().isEmpty())
        {
            code+="\nRôle de la classe : \n"+role->toPlainText()+"\n";
        }

        code+="*/\n\n";
    }

    if(checkbox1->isChecked())
    {
        code+="#ifndef HEADER_"+nom->text().toUpper()+"\n";
        code+="#def HEADER_"+nom->text().toUpper()+"\n\n";
    }

    code+="class "+nom->text();

    if(!classeMere->text().isEmpty())
    {
        code+=" : public "+classeMere->text()+"\n";
    }

    else
    {
        code+="\n";
    }

    code+="{\n      public:\n";

    if(checkbox2->isChecked())
    {
        code+="             "+nom->text()+"();\n";
    }

    if(checkbox3->isChecked())
    {
        code+="             ~"+nom->text()+"();\n\n";
    }

    code+="     protected:\n\n";
    code+="     private:\n\n";
    code+="};\n";

    if(checkbox1->isChecked())
    {
        code+="#endif";
    }

    Gen *newWindow = new Gen(code, this);
    newWindow->exec();
}
