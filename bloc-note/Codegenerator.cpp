#include "Codegenerator.h"
#include "Generated.h"

CodeGenerator::CodeGenerator()
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
    quitter = new QPushButton("Fermer");
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

    connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    connect(generer, SIGNAL(clicked()), this, SLOT(code()));
}

void CodeGenerator::code()
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
        code+="#ifndef "+nom->text().toUpper()+"_H\n";
        code+="#define "+nom->text().toUpper()+"_H\n\n";
    }

    code+="#include <QtGui>\n\nclass "+nom->text();

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
        code+="             "+nom->text();
        if(!classeMere->text().isEmpty())
        {
                code+="(QWidget *parent)\n";
        }
        else
        code+="();\n";
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

    code+="\n\n===============================\n\n";
    code+="#include \""+nom->text()+".h\"\n\n"+nom->text()+"::"+nom->text();
    if(!classeMere->text().isEmpty())
    {
        code+="(QWidget *parent) : "+classeMere->text()+"(parent)\n";
    }

    else
    {
        code+="()\n";
    }

    code+="{\n\n}";
    code+="\n\n===============================\n\n";
    code+="#include <QApplication>\n#include <QtGui>\n#include \""+nom->text()+".h\"\n\n";
    code+="int main(int argc, char *argv[])\n{\n     QApplication app(argc, argv);\n\n     ";
    code+=nom->text()+" fenetre;\n     fenetre.show();\n\n     return app.exec();\n\n}";

    Gen *newWindow = new Gen(code, this);
    newWindow->exec();
}
