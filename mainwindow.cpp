#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "station.h"
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_dimension->setValidator(new QIntValidator(100, 999, this));
    ui->le_ligne->setValidator(new QIntValidator(100, 999, this));
    ui->tab_station->setModel(S.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString nom=ui->le_nom->text();
    QString adresse=ui->le_adresse->text();
    int dimension=ui->le_dimension->text().toInt();
    int ligne=ui->le_ligne->text().toInt();
    Station S(nom,adresse,dimension,ligne);
    bool test=S.ajouter();
    ui->tab_station->setModel(S.afficher());
       QMessageBox msgBox;
           if(test)
               msgBox.setText("ajout avec succes");
               else
               msgBox.setText(("echec d'ajout"));

               msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
    Station S1; S1.setnom(ui->le_nom_supp->text());
    bool test=S1.supprimer(S1.getnom());
    QMessageBox msgBox;
        if(test)
        {
            msgBox.setText("supprimer avec succes");
            ui->tab_station->setModel(S1.afficher());

        }
        else
            msgBox.setText(("echec de suppression"));

            msgBox.exec();
}




void MainWindow::on_pushButton_clicked()
{
    QString nom=ui->ln_nom->text();
    QString adresse=ui->ln_adresse->text();
    int dimension=ui->ln_dimension->text().toInt();
    int ligne=ui->ln_ligne->text().toInt();
    Station S(nom,adresse,dimension,ligne);
    bool test=S.modifier();

       QMessageBox msgBox;
           if(test)

           {
               msgBox.setText("modification avec succes");
           ui->tab_station->setModel(S.afficher());
           }
           else

               msgBox.setText(("echec de modification"));

               msgBox.exec();
}
