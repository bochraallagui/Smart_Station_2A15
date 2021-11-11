#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include <QtDebug>
#include <QMessageBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->le_id->setValidator(new QIntValidator(0,9999999,this));
   ui->tab_personnel->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    int heures=ui->le_heures->text().toInt();
    int salaire=ui->le_salaire->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString type=ui->le_type->text();
    QString experience=ui->le_experience->text();
    Personnel P(id,salaire,heures,nom,prenom,type,experience);
    bool test=P.ajouter();
    QMessageBox msgBox ;
   if (test)
    {  msgBox.setText("Ajout avec succes.");
       ui->tab_personnel->setModel(P.afficher()); }


      else

   msgBox.setText("Echec de ajout");
   msgBox.exec();



    }


void MainWindow::on_pb_supprimer_clicked()
{
    Personnel P1; P1.setid(ui->le_id_supp->text().toInt());
            bool test=P1.supprimer(P1.getid());

  QMessageBox msgBox ;
 if (test)
 {   msgBox.setText("supperssion avec succes.");
  ui->tab_personnel->setModel(P.afficher());


   } else

 msgBox.setText("Echec de supperssion");

 msgBox.exec();
    }

void MainWindow::on_pb_modifier_clicked()
{
    int id =ui->le_id_modif ->text().toInt();
    int heures=ui->le_heures_modif->text().toInt();
    int salaire=ui->le_salaire_modif->text().toInt();
    QString nom=ui->le_nom_modif->text();
    QString prenom=ui->le_prenom_modif->text();
    QString type=ui->le_type_modif->text();
    QString experience=ui->le_experience_modif->text();
    Personnel P (id,salaire,heures,nom,prenom,type,experience);
    bool test=P.modifier(id);
    QMessageBox msgBox ;
    if(test)
   {

         ui->tab_personnel->setModel(P.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier "),
                     QObject::tr("Modification effectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("modifier "),
                     QObject::tr("Modification non effectuée  \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }


