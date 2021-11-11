#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metro.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
 ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->la_matricule->setValidator(new QIntValidator(001,9999999,this));
  ui->nbr_places->setValidator(new QIntValidator(150,300,this));
  ui->le_kilometrage->setValidator(new QIntValidator(0,9999999,this));
  ui->nbr_passagers->setValidator(new QIntValidator(0,300,this));
  ui->tableView->setModel(M.afficher());



}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    int matricule=ui->la_matricule->text().toInt();
    int nbr_places=ui->nbr_places->text().toInt();
    int kilometrage=ui->le_kilometrage->text().toInt();
    int nbr_passagers=ui->nbr_passagers->text().toInt();

    Metro M(matricule,nbr_places,kilometrage,nbr_passagers);
    bool test=M.ajouter();
    QMessageBox msgBox ;
   if (test){
         ui->tableView->setModel(M.afficher());
      msgBox.setText("Ajout avec succes.");
}
   else
{
   msgBox.setText("try again");
   msgBox.exec();
   }
}

void MainWindow::on_pb_supprimer_clicked(){
    int matricule=ui->la_matricule->text().toInt();
            bool test=M.supprimer(matricule);

  QMessageBox msgBox ;
  if (test)
  {
         ui->tableView->setModel(M.afficher());
      QMessageBox :: information (nullptr, QObject ::tr("OK"),
                   QObject ::tr("suppr effectué\n"
                                "click cancel to exit"),
              QMessageBox:: Cancel);

}
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr("try again.\n"
                                       "click cancel to exit."),QMessageBox::Cancel);
  }
}

void MainWindow::on_pb_modifier_clicked()
{
       int matricule=ui->la_matricule->text().toInt();
       int nbr_places=ui->nbr_places->text().toInt();
       int kilometrage=ui->le_kilometrage->text().toInt();
       int nbr_passagers=ui->nbr_passagers->text().toInt();
       Metro M(matricule, nbr_places,kilometrage,nbr_passagers);
       bool test=M.modifier(matricule);

        if (test)
        {
               ui->tableView->setModel(M.afficher());
            QMessageBox :: information (nullptr, QObject ::tr("OK"),
                         QObject ::tr("modifier effectué\n"
                                      "click cancel to exit"),
                    QMessageBox:: Cancel);

      }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
        }
}


void MainWindow::on_pb_trier_matricule_clicked()
{
 ui->tableView->setModel(M.trimatricule());
}


void MainWindow::on_pb_trier_nbrplaces_clicked()
{
 ui->tableView->setModel(M.triplaces());
}



void MainWindow::on_pb_trier_kilometrage_clicked()
{
 ui->tableView->setModel(M.trikilometrage());
}
