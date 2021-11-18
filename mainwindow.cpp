#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trajet.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp->afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pb_ajouter_clicked()
{
    int code=ui->lineEdit_code->text().toInt();
    int depart=ui->lineEdit_depart->text().toInt();
    int id=ui->lineEdit_id->text().toInt();
    int redandance=ui->lineEdit_redandance->text().toInt();
    QString terminus=ui->comboBox_3->currentText();
    QDate date=ui->dateEdit->date();




    trajet t(id,depart,redandance,terminus,code,date);


        bool test1=t.ajouter();
        //id=ui->tableView->selectionBehavior();
       // bool test2=S.supprimer(id);
       // bool test2=S.supprimer(ui->tableView->selectionBehavior());
        if (test1) //si requete executée ==>QMessageBox::information
        {
            ui->tableView->setModel(t.afficher());
            QMessageBox::information(nullptr, QObject::tr("ajout"),
                        QObject::tr("ajout avec succes .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("ajout"),
                        QObject::tr("insert failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_supprimer_clicked()
{




    //int id =ui->lineEdit_2->text().toInt ;
      int id=ui->lineEdit_2->text().toInt();
    bool test =Etmp->supprimer(id);
    if (test)
    {     ui->tableView->setModel(Etmp->afficher());
       QMessageBox::information(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("suppression avec succes .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

                 }
                 else
                     QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("delete failed.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_modifier_clicked()
{
    trajet T ;
     int id=ui->lineEdit_id_2->text().toInt();
   int code=ui->lineEdit_code_2->text().toInt();
   int depart=ui->lineEdit_dep->text().toInt();
   int red=ui->lineEdit_red->text().toInt();
    QString ter =ui->comboBox_2->currentText();
    QDate dat=ui->dateEdit_2->date();
    trajet T1(id,depart,red,ter,code,dat);
    //bool test= S.modifier(id,nom,prenom,fonction,date_naissance);
     bool test;
     test= T1.modifier( id , depart, red, ter,code,dat);
    if (test)
        //[☺]
       {
        ui->tableView->setModel(T1.afficher());
        QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                      QObject::tr("MODIFICATION avec succes .\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);

        }
                      else
                          QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                                      QObject::tr("UPDATE failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_tableView_activated(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();

    QSqlQuery qry ;



     qry.prepare("SELECT code, depart , id , redandance , terminus, date_t FROM trajet");
    if (qry.exec())
    {


       QMessageBox::information(nullptr, QObject::tr("select"),
                    QObject::tr("selection avec succes .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                    QObject::tr("select failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_pushButton_clicked()
{
    int choix=0;
    if(ui->comboBox->currentText()=="par ID")
    {
        choix=1;
    }
    else if(ui->comboBox->currentText()=="par code")
    {
        choix=2;
    }
    else
    {
        choix=3;
    }
    ui->tableView->setModel(Etmp->trier(choix));
}

void MainWindow::on_pushButton_2_clicked()
{
    int choix=0,i,d,r,c;
    QString t;
    QDate dat;
    if(ui->comboBox->currentText()=="par ID")
    {
        i=ui->lineEdit_id_2->text().toInt();
        choix=1;
    }
    else if(ui->comboBox->currentText()=="par code")
    {
        c=ui->lineEdit_code_2->text().toInt();
        choix=2;
    }
    else
    {
       t=ui->comboBox_2->currentText();
        choix=3;
    }
    trajet tr(i,d,r,t,c,dat);
    ui->tableView->setModel(tr.rechercher(choix));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
        Etmp->statistiques(ui->widget_2);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool test=Etmp->export_msg();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Succés"), QObject::tr("Export effectué\n""Click Ok to exit."), QMessageBox::Ok);
    }
    else QMessageBox::warning(nullptr, QObject::tr("Erreur"),QObject::tr("Export non effectué. \n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_4_clicked()
{
    if (Etmp->plan()>0)
    {
        QString notif=QString::number(Etmp->plan())+" trajets planifiés pour ce jour.\n""Click Ok to exit.";
        QMessageBox::information(nullptr, QObject::tr("Plan"),notif, QMessageBox::Ok);
    }
    else QMessageBox::information(nullptr, QObject::tr("Plan"),"pas de trajets planifiés pour ce jour.\n""Click Ok to exit.", QMessageBox::Ok);
}
