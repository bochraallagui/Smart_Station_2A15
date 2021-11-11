#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include <QLineEdit>
#include<QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
   ui->tab_client->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();

Client C(id,nom,prenom,adresse);
bool test=C.ajouter();
    QMessageBox msgBox ;
   if (test)
     { ui->tab_client->setModel(C.afficher());
       msgBox.setText("Ajout avec succes.");

     }
      else

   msgBox.setText("Echec de ajout");
   msgBox.exec();


 }


void MainWindow::on_pb_supprimer_clicked()
{
    Client C1; C1.setid(ui->le_id_supp->text().toInt());
    bool test=C1.supprimer(C1.getid());
    QMessageBox msgBox ;
     if (test)
       { msgBox.setText("supperssion avec succes.");

              ui->tab_client->setModel(C.afficher());
       }

        else

     msgBox.setText("Echec de supperssion");
     msgBox.exec();

}




void MainWindow::on_pb_modifier_clicked()
{
    int id =ui->le_id_modif ->text().toInt();

    QString nom=ui->le_nom_modif->text();
    QString prenom=ui->le_prenom_modif->text();
    QString adresse=ui->le_adresse_modif->text();
    Client C (id,nom,prenom,adresse);

    bool test=C.modifier(id);
    QMessageBox msgBox ;
    if(test)
   {

         ui->tab_client->setModel(C.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier "),
                     QObject::tr("Modification effectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("modifier "),
                     QObject::tr("Modification non effectuée  \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
