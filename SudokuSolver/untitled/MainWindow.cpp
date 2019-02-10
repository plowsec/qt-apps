#include "MainWindow.h"

MainWindow::MainWindow()
{
    setFixedSize(480,280);
    setWindowIcon(QIcon("icone.png"));
    int l=0;
    for (int i=0;i<9;i++)
   {
        int k=0;
        if(i%3==0)
            l+=4;
        for (int j=0;j<9;j++)
        {
            grille[i][j]=new QLineEdit(this);
            if(j%3==0)
                k+=4; //d�calage toutes les 3 cases
            grille[i][j]->setGeometry(25*j+10+k,(25)*i+10+l,25,25);
        }
    }
    boutonSolve = new QPushButton("R�soudre",this);
    boutonSolve->setGeometry(260,10,100,25);

    boutonFill = new QPushButton("Remplir (Sudoku)",this);
    boutonFill->setGeometry(260,40,100,25);

    boutonFillLettres = new QPushButton("Remplir (Wordoku)",this);
    boutonFillLettres->setGeometry(370,40,100,25);

    boutonScan = new QPushButton("Reset",this);
    boutonScan->setGeometry(370,10,100,25);

    box = new QCheckBox("Afficher les op�rations",this);
    box->setGeometry(260,70,200,25);

    label = new QLabel("Solution :",this);
    label->setGeometry(260,110,50,25);

    symbols = new QLineEdit(this);
    symbols->setGeometry(320,110,150,25);

    debug = new QTextEdit(this);
    debug->setGeometry(260,160,210,87);

    connect(boutonScan,SIGNAL(clicked()),this,SLOT(reset1()));

    connect(boutonSolve,SIGNAL(clicked()),this,SLOT(solve()));
    connect(boutonFill,SIGNAL(clicked()),this,SLOT(remplir()));
    connect(boutonFillLettres,SIGNAL(clicked()),this,SLOT(remplirLettres()));

}
void MainWindow::reset1()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            grille[i][j]->setText("");
        }
    }
    debug->setText("");
    symbols->setText("");
}
void MainWindow::remplir()
{
    int grilleTest1[9][9] =
        {
            {9,0,0,1,0,0,0,0,5},
            {0,0,5,0,9,0,2,0,1},
            {8,0,0,0,4,0,0,0,0},
            {0,0,0,0,8,0,0,0,0},
            {0,0,0,7,0,0,0,0,0},
            {0,0,0,0,2,6,0,0,9},
            {2,0,0,3,0,0,0,0,6},
            {0,0,0,2,0,0,9,0,0},
            {0,0,1,9,0,4,5,7,0}
        };
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(grilleTest1[i][j]!=0)
                grille[i][j]->setText(QString::number(grilleTest1[i][j]));
            else
                grille[i][j]->setText("");
        }
    }
}
void MainWindow::remplirLettres()
{
    QString grilleTestLettres[9][9] =
        {
        {"N","","","","","O","V","","R"},
        {"","","I","","","L","N","",""},
        {"O","","","V","I","","U","E",""},
        {"C","R","","","V","","O","L",""},
        {"","","","R","","C","","","V"},
        {"","","","","","","","R",""},
        {"","","","","","","","","O"},
        {"L","I","","U","","","R","","N"},
        {"","","","","C","V","","","I"},
        };
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(grilleTestLettres[i][j]!="")
                grille[i][j]->setText(grilleTestLettres[i][j]);
            else
                grille[i][j]->setText("");
        }
    }
}
void MainWindow::addText(QString str)
{
    debug->setText(debug->toPlainText()+str+"\n");
}
QString MainWindow::listSymbols()
{
    QString liste="0";
    for (int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(liste.contains(grille[i][j]->text()))
                continue;
            liste.append(grille[i][j]->text());
        }
    }
    //symbols->setText(liste.right(9));
    if(liste.length()<9)
        liste="";
    return liste;
}
bool MainWindow::freeRow(int grilleTest[9][9],int n, int ligne)
{
    for(int i=0;i<9;i++)
        if (grilleTest[ligne][i]==n)
            return false;
    return true;
}
bool MainWindow::freeColumn(int grilleTest[9][9],int n, int colonne)
{
    for(int i=0;i<9;i++)
        if(grilleTest[i][colonne]==n)
            return false;
    return true;
}
bool MainWindow::freeBlock(int grilleTest[9][9],int n, int ligne, int colonne)
{
    int coinLeft = colonne-(colonne%3);
    int coinUp = ligne-(ligne%3);
    for (int i = coinUp ; i < coinUp+3 ; i++)
        for(int j = coinLeft ; j < coinLeft+3 ; j++)
            if(grilleTest[i][j]==n)
                return false;
    return true;
}
bool MainWindow::Free(int grilleTest[9][9],int n, int i, int j)
{
    if(freeRow(grilleTest,n,i) && freeColumn(grilleTest,n, j) && freeBlock(grilleTest,n,i,j))
        return true;
    return false;
}
bool MainWindow::isValid(int grilleTest[9][9],int position)
{
    number+=1;
    if(position==9*9)
    {
        if(box->isChecked())
            report+="Pfiou...fini!\n";
        return true;
    }
    int i = position/9, j = position%9;
    if(grilleTest[i][j]!=0)
    {
        if(box->isChecked())
            report+="Case "+QString::number(position)+" d�j� faite :o\n";
        return isValid(grilleTest,position+1);
    }
    for(int n=1;n<=9;n++)
    {
        if(Free(grilleTest,n,i,j))
        {
            grilleTest[i][j]=n;
            if(box->isChecked())
                report+="J\'essaie "+QString::number(n)+" pour la case "+QString::number(position)+"...\n";
            if(isValid(grilleTest,position+1))
                return true;
        }
    }
    grilleTest[i][j]=0;
    if(box->isChecked())
        report+="Zut je dois revenir en arri�re! :(\n";
    return false;
}
void MainWindow::solve()
{
    QString lettres ="";
    lettres=listSymbols();
    number=0;
    report="";
    int grilleTest[9][9] =
        {
            {9,0,0,1,0,0,0,0,5},
            {0,0,5,0,9,0,2,0,1},
            {8,0,0,0,4,0,0,0,0},
            {0,0,0,0,8,0,0,0,0},
            {0,0,0,7,0,0,0,0,0},
            {0,0,0,0,2,6,0,0,9},
            {2,0,0,3,0,0,0,0,6},
            {0,0,0,2,0,0,9,0,0},
            {0,0,1,9,0,4,5,7,0}
        };
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if((grille[i][j]->text()!="") && (lettres.length()>1))
            {
                grilleTest[i][j]=lettres.indexOf(grille[i][j]->text());
            }
            else
                grilleTest[i][j]=0;
        }
    }
    addText("R�solution...");
    isValid(grilleTest,0);
    addText("...termin�e!");
    for(int m=0;m<9;m++)
    {
        for(int n=0;n<9;n++)
        {
            if(m==5)
                symbols->setText(symbols->text()+lettres[grilleTest[m][n]]);
            if(lettres.length()==1)
                grille[m][n]->setText(grilleTest[m][n]+"");
//            addText(grilleTest[m][n]+"");
            else
                grille[m][n]->setText(lettres[grilleTest[m][n]]+"");
        }
    }
    addText("Nombre d'�x�cutions de l'algorithme : "+QString::number(number)+"\n"+report);
    addText(QString::number(lettres.length()));

}

