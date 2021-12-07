#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include <QLineEdit>
#include<QIntValidator>
#include <QMessageBox>
#include <QSqlQuery>
#include <qcustomplot.h>
#include "smtp.h"
#include "exportexcelobject.h"
#include "personnel.h"
#include <QtDebug>
#include "station.h"
#include "trajet.h"
#include "qrcode.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trajet.h"
#include "qrcode.h"
#include <QtSvg/QSvgRenderer>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include<QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QAbstractSocket>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include<QIntValidator>
#include<QRegularExpression>
#include <QPainter>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSystemTrayIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <string>
#include <vector>
#include<QDirModel>
#include <qrcode.h>
#include <string>
#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include "qrcode.h"
#include "connection.h"


using qrcodegen::QrCode;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



               Connection c;
               bool test=c.createconnect();
               if(test)
               {
                   QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("connection successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

                   ui->la_matricule->setValidator(new QIntValidator(001,9999999,this));
                   ui->nbr_places->setValidator(new QIntValidator(150,300,this));
                   ui->le_kilometrage->setValidator(new QIntValidator(0,9999999,this));
                   ui->nbr_passagers->setValidator(new QIntValidator(0,300,this));
                   ui->tableView->setModel(M.afficher());
                   QSqlQueryModel *modell=new QSqlQueryModel();
                              modell->setQuery("select NOM from PERSONNEL order by NOM");
                      ui->comboBox->setModel(modell);
                      ui->le_capacite->setValidator(new QIntValidator(100, 9999999, this));
                              ui->tab_station->setModel(S.afficher());


                   ui->tableView_2->setModel(Etmp->afficher());
                   QSqlQuery query("SELECT nom FROM station");
                           while (query.next())
                               {
                                 QString nsch=query.value(0).toString();
                                 ui->comboBox_3->addItem(nsch);
                                 ui->comboBox_3->setEditText(nsch);
                                 ui->comboBox_4->addItem(nsch);
                                 ui->comboBox_4->setEditText(nsch);
                                 ui->comboBox_5->addItem(nsch);
                                 ui->comboBox_5->setEditText(nsch);
                                 ui->comboBox_6->addItem(nsch);
                                 ui->comboBox_6->setEditText(nsch);
                               }


           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                               QObject::tr("connection failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    int idc=ui->le_idc->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    int nbticket=ui->le_nbticket->text().toInt();
    int age=ui->le_age->text().toInt();

Client C(idc,nom,prenom,adresse,nbticket,age);
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
    Client C1;
    C1.setidc(ui->le_idc_supp->text().toInt());
               bool test=C1.supprimer(C1.getidc());

     QMessageBox msgBox ;
    if (test)
    {   msgBox.setText("supperssion avec succes.");
     ui->tab_client->setModel(C.afficher());


      } else

    msgBox.setText("Echec de supperssion");

    msgBox.exec();
}





void MainWindow::on_pb_modifier_clicked()
{
    int idc =ui->le_idc->text().toInt();

    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    int nbticket=ui->le_nbticket->text().toInt();
    int age=ui->le_age->text().toInt();

    Client C (idc,nom,prenom,adresse,nbticket,age);

    bool test=C.modifier(idc);
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







void MainWindow::on_pb_trierclient_clicked()
{
      ui->tab_client->setModel(C.trierclient());
}



void MainWindow::on_pb_rechercherclient_clicked()
{
    QString nom=ui->le_recherche->text() ;
          if (nom=="")
          {
              QMessageBox :: information (this,tr("Empty Filed"),
                      tr ("Please enter a Name."));
              return ;

          }
          else { ui->tab_client->setModel(C.rechercherclient(nom));}


}










void MainWindow::on_tabWidget_currentChanged(int index)
{

                     QLinearGradient gradient(0, 0, 0, 400);
                     gradient.setColorAt(0, QColor(90, 90, 90));
                     gradient.setColorAt(0.38, QColor(0, 140, 140));
                     gradient.setColorAt(1, QColor(0, 140, 140));
                     ui->plot->setBackground(QBrush(gradient));

                     QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                     amande->setAntialiased(false);
                     amande->setStackingGap(1);
                      //couleurs
                     amande->setName("jour rest");
                     amande->setPen(QPen(QColor(20, 100, 100).lighter(130)));
                     amande->setBrush(QColor(20, 100, 100));

                      //axe des abscisses
                     QVector<double> ticks;
                     QVector<QString> labels;
                     C.statistique(&ticks,&labels);

                     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                     textTicker->addTicks(ticks, labels);
                     ui->plot->xAxis->setTicker(textTicker);
                     ui->plot->xAxis->setTickLabelRotation(60);
                     ui->plot->xAxis->setSubTicks(false);
                     ui->plot->xAxis->setTickLength(0, 4);
                     ui->plot->xAxis->setRange(0, 8);
                     ui->plot->xAxis->setBasePen(QPen(Qt::white));
                     ui->plot->xAxis->setTickPen(QPen(Qt::white));
                     ui->plot->xAxis->grid()->setVisible(true);
                     ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                     ui->plot->xAxis->setTickLabelColor(Qt::white);
                     ui->plot->xAxis->setLabelColor(Qt::white);

                     // axe des ordonnées
                     ui->plot->yAxis->setRange(0,50);
                     ui->plot->yAxis->setPadding(5);
                     ui->plot->yAxis->setLabel("Statistiques");
                     ui->plot->yAxis->setBasePen(QPen(Qt::white));
                     ui->plot->yAxis->setTickPen(QPen(Qt::white));
                     ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                     ui->plot->yAxis->grid()->setSubGridVisible(true);
                     ui->plot->yAxis->setTickLabelColor(Qt::white);
                     ui->plot->yAxis->setLabelColor(Qt::white);
                     ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                     ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                     // ajout des données  (statistiques de la quantité)//

                     QVector<double> PlaceData;
                     QSqlQuery q1("select NBTICKET from CLIENT");
                     while (q1.next()) {
                                   int  nbr_fautee = q1.value(0).toInt();
                                   PlaceData<< nbr_fautee;
                                     }
                     amande->setData(ticks, PlaceData);

                     ui->plot->legend->setVisible(true);
                     ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                     ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                     ui->plot->legend->setBorderPen(Qt::NoPen);
                     QFont legendFont = font();
                     legendFont.setPointSize(5);
                     ui->plot->legend->setFont(legendFont);
                     ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pb_send_clicked()
{
    Smtp* smtp = new Smtp("mejrighada77@gmail.com", "ghadaa7790315138", "smtp.gmail.com", 465);
     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
     QString m=ui->lineEdit->text();
     smtp->sendMail("mejrighada77@gmail.com",m, "Smart Station, Nouvelle carte de fidelite!","Bienvenue! Vous-etes UN CLIENT fidele!");}







void MainWindow::on_pb_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
            QString sheetName="test";
    ExportExcelObject obj(fileName, sheetName, ui->tab_client);
    obj.addField(0, tr("IDC"), "int");
    obj.addField(1, tr("NOM"), "char(20)");
    obj.addField(2, tr("PRENOM"), "char(20)");
    obj.addField(3, tr("ADRESSE"), "char(20)");
    obj.addField(4, tr("NBTICKET"), "int");
    obj.addField(5, tr("AGE"), "int");

    int retVal = obj.export2Excel();
    if(retVal > 0)
    {//done
    }
    else{

    }
}

void MainWindow:: on_pb_ajouter_2_clicked()
{
    int id=ui->le_id->text().toInt();
    int heures=ui->le_heures->text().toInt();
    int heuresmaximale=ui->le_heures_max->text().toInt();
    int salaire=ui->le_salaire->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString type=ui->le_type->text();

    Personnel P(id,salaire,heures,heuresmaximale,nom,prenom,type);
    bool test=P.ajouter();
    QMessageBox msgBox ;
   if (test)
    {  msgBox.setText("Ajout avec succes.");
       ui->tab_personnel->setModel(P.afficher()); }


      else

   msgBox.setText("Echec de ajout");
   msgBox.exec();



    }


void MainWindow::on_pb_supprimer_2_clicked()
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

void MainWindow::on_pb_modifier_2_clicked()
{
    int id =ui->le_id->text().toInt();
    int heures=ui->le_heures->text().toInt();
    int heuresmaximale=ui->le_heures_max->text().toInt();
    int salaire=ui->le_salaire->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString type=ui->le_type->text();

    Personnel P (id,salaire,heures,heuresmaximale,nom,prenom,type);
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


void MainWindow::on_pb_rechercher_clicked()

{
    QString nom=ui->le_nom_rech->text() ;
       if (nom=="")
       {
           QMessageBox :: information (this,tr("Empty Filed"),
                   tr ("Please enter a Name."));
           return ;

       }
       else { ui->tab_personnel->setModel(P.rechercher(nom));}
 }


void MainWindow::on_pb_tri_nom_clicked()
{
     ui->tab_personnel->setModel(P.trinom());
}



void MainWindow::on_tabWidget_currentChanged_2(int index)
{
    // background //
                     QLinearGradient gradient(0, 0, 0, 400);
                     gradient.setColorAt(0, QColor(90, 90, 90));
                     gradient.setColorAt(0.38, QColor(60, 255, 255));
                     gradient.setColorAt(1, QColor(60, 255, 255));
                     ui->plot_2->setBackground(QBrush(gradient));

                     QCPBars *amande = new QCPBars(ui->plot_2->xAxis, ui->plot_2->yAxis);
                     amande->setAntialiased(false);
                     amande->setStackingGap(1);
                      //couleurs
                     amande->setName("jour rest");
                     amande->setPen(QPen(QColor(0, 200, 200).lighter(130)));
                     amande->setBrush(QColor(0, 200, 200));

                      //axe des abscisses
                     QVector<double> ticks;
                     QVector<QString> labels;
                     P.statistique(&ticks,&labels);

                     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                     textTicker->addTicks(ticks, labels);
                     ui->plot_2->xAxis->setTicker(textTicker);
                     ui->plot_2->xAxis->setTickLabelRotation(60);
                     ui->plot_2->xAxis->setSubTicks(false);
                     ui->plot_2->xAxis->setTickLength(0, 4);
                     ui->plot_2->xAxis->setRange(0, 8);
                     ui->plot_2->xAxis->setBasePen(QPen(Qt::white));
                     ui->plot_2->xAxis->setTickPen(QPen(Qt::white));
                     ui->plot_2->xAxis->grid()->setVisible(true);
                     ui->plot_2->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                     ui->plot_2->xAxis->setTickLabelColor(Qt::white);
                     ui->plot_2->xAxis->setLabelColor(Qt::white);

                     // axe des ordonnées
                     ui->plot_2->yAxis->setRange(0,1000);
                     ui->plot_2->yAxis->setPadding(5);
                     ui->plot_2->yAxis->setLabel("Statistiques");
                     ui->plot_2->yAxis->setBasePen(QPen(Qt::white));
                     ui->plot_2->yAxis->setTickPen(QPen(Qt::white));
                     ui->plot_2->yAxis->setSubTickPen(QPen(Qt::white));
                     ui->plot_2->yAxis->grid()->setSubGridVisible(true);
                     ui->plot_2->yAxis->setTickLabelColor(Qt::white);
                     ui->plot_2->yAxis->setLabelColor(Qt::white);
                     ui->plot_2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                     ui->plot_2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                     // ajout des données  (statistiques de la quantité)//

                     QVector<double> PlaceData;
                     QSqlQuery q1("select SALAIRE from PERSONNEL");
                     while (q1.next()) {
                                   int  nbr_fautee = q1.value(0).toInt();
                                   PlaceData<< nbr_fautee;
                                     }
                     amande->setData(ticks, PlaceData);

                     ui->plot_2->legend->setVisible(true);
                     ui->plot_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                     ui->plot_2->legend->setBrush(QColor(255, 255, 255, 100));
                     ui->plot_2->legend->setBorderPen(Qt::NoPen);
                     QFont legendFont = font();
                     legendFont.setPointSize(5);
                     ui->plot_2->legend->setFont(legendFont);
                     ui->plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


void MainWindow::on_pushButton_clicked()
{
    int heures;
    QString title,description;
            QSqlQuery query;


       QSqlQuery q1("SELECT HEURES FROM PERSONNEL");
       while (q1.next())
       {
       heures = q1.value(0).toInt();
       if(heures>10){
           title="horaire du travaille";
           description="vous avez depaser les 10 heures";
       popup->showPopup(title,description);
       }
       }


}


void MainWindow::on_chatBtn_clicked()
{
    chat = new ChatMainWindow();
    chat->show();
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

void MainWindow::on_pb_modifier_3_clicked()
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
                  "click cancel to exit."),
  QMessageBox::Cancel);
     }
}

void MainWindow::on_pb_supprimer_3_clicked()
{
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
                      "click cancel to exit."),
      QMessageBox::Cancel);
  }
}

void MainWindow::on_pb_trier_matricule_clicked()
{
   ui->tableView->setModel(M.trimetro());
}


void MainWindow::on_pb_rechercher_2_clicked()
{
    int matricule=ui->la_matricule->text().toInt();
       if (matricule==NULL)
 {
           QMessageBox::information(this, tr("Empty Field"),
               tr("Please enter a Number."));
           return;
 } else
  {
  ui->tableView->setModel(M.recherchemetro(matricule));
  }
}


void MainWindow::on_tabWidget_3_currentChanged(int index)
{
    // background //
                  QLinearGradient gradient(0, 0, 0, 400);
                  gradient.setColorAt(0, QColor(90, 90, 90));
                  gradient.setColorAt(0.38, QColor(0, 220, 220));
                  gradient.setColorAt(1, QColor(0, 220, 220));
                  ui->plot->setBackground(QBrush(gradient));

                  QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                  amande->setAntialiased(false);
                  amande->setStackingGap(1);
   //couleurs
                  amande->setName("kilometrage");
                  amande->setPen(QPen(QColor(180, 170, 255).lighter(130)));
                  amande->setBrush(QColor(180, 170, 255));

  //axe des abscisses
                  QVector<double> ticks;
                  QVector<QString> labels;
                  M.statistique(&ticks,&labels);

                  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                  textTicker->addTicks(ticks, labels);
                  ui->plot->xAxis->setTicker(textTicker);
                  ui->plot->xAxis->setTickLabelRotation(60);
                  ui->plot->xAxis->setSubTicks(false);
                  ui->plot->xAxis->setTickLength(0, 4);
                  ui->plot->xAxis->setRange(0, 8);
                  ui->plot->xAxis->setBasePen(QPen(Qt::white));
                  ui->plot->xAxis->setTickPen(QPen(Qt::white));
                  ui->plot->xAxis->grid()->setVisible(true);
                  ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                  ui->plot->xAxis->setTickLabelColor(Qt::white);
                  ui->plot->xAxis->setLabelColor(Qt::white);

  // axe des ordonnées
                  ui->plot->yAxis->setRange(0,15000);
                  ui->plot->yAxis->setPadding(5);
                  ui->plot->yAxis->setLabel("Statistiques");
                  ui->plot->yAxis->setBasePen(QPen(Qt::white));
                  ui->plot->yAxis->setTickPen(QPen(Qt::white));
                  ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                  ui->plot->yAxis->grid()->setSubGridVisible(true);
                  ui->plot->yAxis->setTickLabelColor(Qt::white);
                  ui->plot->yAxis->setLabelColor(Qt::white);
                  ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                  ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // ajout des données  (statistiques de la quantité)//

                  QVector<double> PlaceData;
                  QSqlQuery q1("select KILOMETRAGE from METRO");
                  while (q1.next()) {
                                int  nbr_fautee = q1.value(0).toInt();
                                PlaceData<< nbr_fautee;
                                  }
                  amande->setData(ticks, PlaceData);

                  ui->plot->legend->setVisible(true);
                  ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                  ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                  ui->plot->legend->setBorderPen(Qt::NoPen);
                  QFont legendFont = font();
                  legendFont.setPointSize(5);
                  ui->plot->legend->setFont(legendFont);
                  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pb_pdf_2_clicked()
{
    QSqlDatabase db;
                   QTableView table_menu;
                   QSqlQueryModel * Modal=new  QSqlQueryModel();
                   QSqlQuery qry;
                    qry.prepare("SELECT * FROM METRO ");
                    qry.exec();
                    Modal->setQuery(qry);
                    table_menu.setModel(Modal);
                    db.close();
                    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = table_menu.model()->rowCount();
                    const int columnCount =  table_menu.model()->columnCount();
                    const QString strTitle ="Document";
 out <<  "<html>\n"
 "<img src='C:/Users/lenovo/Downloads/SEMESTRE 1/PROJET C++/sncf.jpg' height='120' width='120'/>"
 "<head>\n"
 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
  <<  QString("<title>%1</title>\n").arg(strTitle)
  <<  "</head>\n"
   "<body bgcolor=#ffffff link=#5000A0>\n"
  << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES METROS")
  <<"<br>"

 <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
  out << "<thead><tr bgcolor=#f0f0f0>";
  for (int column = 0; column < columnCount; column++)
   if (!table_menu.isColumnHidden(column))
  out << QString("<th>%1</th>").arg(table_menu.model()->headerData(column, Qt::Horizontal).toString());
  out << "</tr></thead>\n";

  for (int row = 0; row < rowCount; row++) {
  out << "<tr>";
  for (int column = 0; column < columnCount; column++) {
  if (!table_menu.isColumnHidden(column)) {
    QString data = table_menu.model()->data(table_menu.model()->index(row, column)).toString().simplified();
  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
   }
   }
  out << "</tr>\n";
   }
  out <<  "</table>\n"
   "<br><br>"
     <<"<br>"
   <<"<table border=1 cellspacing=0 cellpadding=2>\n";
   out << "<thead><tr bgcolor=#f0f0f0>";
   out <<  "</table>\n"
   "</body>\n"
   "</html>\n";

     QTextDocument *document = new QTextDocument();
   document->setHtml(strStream);
     QPrinter printer;
     QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
       if (dialog->exec() == QDialog::Accepted)
       {
        document->print(&printer);
     }
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName("/tmp/metro.pdf");
      printer.setPageMargins(QMarginsF(15, 15, 15, 15));
     delete document;
}


void MainWindow::on_AFFECTER_clicked()
{
    int matricule=ui->la_matricule->text().toInt();
    QString nomid=ui->comboBox->currentText();
    int id_personnel;
    qInfo() << nomid;
    QSqlQuery q;
    q.exec("select ID from PERSONNEL where NOM ='"+nomid+"'");
        while(q.next())
  {
  id_personnel = q.value(0).toInt();
   qInfo() << id_personnel;
  }

bool test=M.affecter(matricule,id_personnel);
if (test)
 {
   ui->tableView->setModel(M.afficher());
QMessageBox :: information (nullptr, QObject ::tr("OK"),
    QObject ::tr("Affectation effectué\n"
                 "click cancel to exit"),
 QMessageBox:: Cancel);
  }
else
 {
 QMessageBox::critical(nullptr,QObject::tr("not ok"),
     QObject::tr("try again.\n"
                 "click cancel to exit."),
 QMessageBox::Cancel);
}
}






void MainWindow::on_pb_ajouter_station_clicked()
{
    QString nom=ui->comboBox_nom->currentText();
        QString region=ui->le_region->text();
        QString adresse=ui->le_adresse->text();
        int capacite=ui->le_capacite->text().toInt();
        Station S(nom,region,adresse,capacite);
        bool test=S.ajouter();
        ui->tab_station->setModel(S.afficher());
           QMessageBox msgBox;
               if(test)
                   msgBox.setText("ajout avec succes");
                   else
                   msgBox.setText(("echec d'ajout"));

                   msgBox.exec();
}

void MainWindow::on_pb_modifier_station_clicked()
{
    QString nom=ui->comboBox_nom_2->currentText();
        QString region=ui->ln_region->text();
        QString adresse=ui->ln_adresse->text();
        int capacite=ui->ln_capacite->text().toInt();
        Station S(nom,region,adresse,capacite);
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

void MainWindow::on_pb_supprimer_station_clicked()
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

void MainWindow::on_pb_recherche_clicked()
{
    if(ui->checkBox_nom->isChecked()){
            QString nom=ui->lr_rechercher_nom->text();
            QSqlQueryModel* test=S.rechercher_nom(nom);
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("recherche avec succes");
                    ui->tab_station->setModel(S.rechercher_nom(nom));
                }
                    else
                    msgBox.setText(("station introuvable"));

                    msgBox.exec();
            }
            else if(ui->checkBox_region->isChecked())
            {
               QString region=ui->lr_rechercher_region->text();
               QSqlQueryModel* test2=S.rechercher_region(region);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_region(region));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
            else if(ui->checkBox_capacite->isChecked())
            {
               int capacite=ui->lr_rechercher_capacite->text().toInt();
               QSqlQueryModel* test2=S.rechercher_capacite(capacite);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_capacite(capacite));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
            else if((ui->checkBox_region->isChecked())&&(ui->checkBox_nom->isChecked()))
            {
                QString nom=ui->lr_rechercher_nom->text();
               QString region=ui->lr_rechercher_region->text();
               QSqlQueryModel* test2=S.rechercher_regionnom(nom, region);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_regionnom(nom, region));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
            else if((ui->checkBox_capacite->isChecked())&&(ui->checkBox_nom->isChecked()))
            {
                QString nom=ui->lr_rechercher_nom->text();
               int capacite=ui->lr_rechercher_capacite->text().toInt();
               QSqlQueryModel* test2=S.rechercher_nomcapacite(nom, capacite);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_nomcapacite(nom, capacite));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
            else if((ui->checkBox_capacite->isChecked())&&(ui->checkBox_region->isChecked()))
            {
                QString region=ui->lr_rechercher_region->text();
               int capacite=ui->lr_rechercher_capacite->text().toInt();
               QSqlQueryModel* test2=S.rechercher_regioncapacite(region, capacite);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_regioncapacite(region, capacite));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
            else if((ui->checkBox_capacite->isChecked())&&(ui->checkBox_region->isChecked())&&(ui->checkBox_nom->isChecked()))
            {
                QString nom=ui->lr_rechercher_nom->text();
                QString region=ui->lr_rechercher_region->text();
               int capacite=ui->lr_rechercher_capacite->text().toInt();
               QSqlQueryModel* test2=S.rechercher_nomregioncapacite(nom,region,capacite);
               QMessageBox msgBox;
                   if(test2){
                       msgBox.setText("recherche avec succes");
                       ui->tab_station->setModel(S.rechercher_nomregioncapacite(nom,region,capacite));
                   }
                       else
                       msgBox.setText(("station introuvable"));

                       msgBox.exec();
            }
}

void MainWindow::on_pb_tri_station_clicked()
{
    {
           QString choix=ui->comboBox->currentText();
           if(choix=="tri par capacite croissante"){
           QSqlQueryModel* test=S.triparCapacite();
           QMessageBox msgBox;
               if(test){
                   msgBox.setText("tri avec succes");
                   ui->tab_station->setModel(S.triparCapacite());
               }
                   else
                   msgBox.setText(("echec"));

                   msgBox.exec();
           }
           else if(choix=="tri par capacite decroissante")
           {
               QSqlQueryModel* test=S.triparCapaciteD();
               QMessageBox msgBox;
                   if(test){
                       msgBox.setText("tri avec succes");
                       ui->tab_station->setModel(S.triparCapaciteD());
                   }
                       else
                       msgBox.setText(("echec"));

                       msgBox.exec();
           }
           else if(choix=="tri par nom croissant")
           {
               QSqlQueryModel* test=S.triparnom();
               QMessageBox msgBox;
                   if(test){
                       msgBox.setText("tri avec succes");
                       ui->tab_station->setModel(S.triparnom());
                   }
                       else
                       msgBox.setText(("echec"));

                       msgBox.exec();
           }
           else if(choix=="tri par nom decroissant")
           {
               QSqlQueryModel* test=S.triparnomD();
               QMessageBox msgBox;
                   if(test){
                       msgBox.setText("tri avec succes");
                       ui->tab_station->setModel(S.triparnomD());
                   }
                       else
                       msgBox.setText(("echec"));

                       msgBox.exec();
           }
   }

}




void MainWindow::on_pb_ajouter_trajet_clicked()
{
    int code=ui->lineEdit_code->text().toInt();
    QString depart=ui->comboBox_4->currentText();
    int id=ui->lineEdit_id->text().toInt();
    int redandance=ui->lineEdit_redandance->text().toInt();
    QString terminus=ui->comboBox_3->currentText();
    QDate date=ui->dateEdit->date();


if (terminus==depart)
{
    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                QObject::tr("Le depart ne peut pas etre le meme que l'arrivée.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
{

    trajet t(id,depart,redandance,terminus,code,date);


        bool test1=t.ajouter();
        //id=ui->tableView->selectionBehavior();
       // bool test2=S.supprimer(id);
       // bool test2=S.supprimer(ui->tableView->selectionBehavior());
        if (test1) //si requete executée ==>QMessageBox::information
        {
            ui->tableView_2->setModel(t.afficher());
            QMessageBox::information(nullptr, QObject::tr("ajout"),
                        QObject::tr("ajout avec succes .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("ajout"),
                        QObject::tr("insert failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
}
void MainWindow::on_supprimer_clicked()
{




    //int id =ui->lineEdit_2->text().toInt ;
      int id=ui->lineEdit_2->text().toInt();
    bool test =Etmp->supprimer(id);
    if (test)
    {     ui->tableView_2->setModel(Etmp->afficher());
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
   QString depart=ui->comboBox_6->currentText();
   int red=ui->lineEdit_red->text().toInt();
    QString ter =ui->comboBox_5->currentText();
    QDate dat=ui->dateEdit_2->date();
    if (ter==depart)
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Le depart ne peut pas etre le meme que l'arrivée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
    trajet T1(id,depart,red,ter,code,dat);
    //bool test= S.modifier(id,nom,prenom,fonction,date_naissance);
     bool test;
     test= T1.modifier( id , depart, red, ter,code,dat);
    if (test)
        //[☺]
       {
        ui->tableView_2->setModel(T1.afficher());
        QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                      QObject::tr("MODIFICATION avec succes .\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);

        }
                      else
                          QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                                      QObject::tr("UPDATE failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{

    QString val=ui->tableView_2->model()->data(index).toString();

    QSqlQuery qry ;



     qry.prepare("SELECT prix, depart , id , duree , terminus, date_t FROM trajet");
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



void MainWindow::on_pushButton_trier_trajet_clicked()
{
    int choix=0;
    if(ui->comboBox_2->currentText()=="par ID")
    {
        choix=1;
    }
    else if(ui->comboBox_2->currentText()=="par prix")
    {
        choix=2;
    }
    else
    {
        choix=3;
    }
    ui->tableView_2->setModel(Etmp->trier(choix));
}

void MainWindow::on_pushButton_rechercher_trajet_clicked()
{
    int choix=0,i,r,c;
    QString t,d;
    QDate dat;
    if(ui->comboBox_2->currentText()=="par ID")
    {
        i=ui->lineEdit_id_2->text().toInt();
        choix=1;
    }
    else if(ui->comboBox_2->currentText()=="par prix")
    {
        c=ui->lineEdit_code_2->text().toInt();
        choix=2;
    }
    else
    {
       r=ui->lineEdit_red->text().toInt();
        choix=3;
    }
    trajet tr(i,d,r,t,c,dat);
    ui->tableView_2->setModel(tr.rechercher(choix));
}

void MainWindow::on_tabWidget_5_currentChanged(int index)
{
        Etmp->statistiques(ui->widget_4);
}

void MainWindow::on_pushButton_exporter_trajet_clicked()
{
    bool test=Etmp->export_txt();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Succés"), QObject::tr("Export effectué\n""Click Ok to exit."), QMessageBox::Ok);
    }
    else QMessageBox::warning(nullptr, QObject::tr("Erreur"),QObject::tr("Export non effectué. \n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_qrcode_trajet_clicked()
{
    trajet P;
            if(ui->tableView_2->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("Veuillez Choisir un trajet du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {




                           P.setid(ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0)).toInt());
                           P.setdepart(ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),1)).toString());
                           P.setduree(ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),2)).toInt());
                           P.setterminus(ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),3)).toString());
                           P.setprix(ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4)).toInt());
                          // P.setdate(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toDate());







                 QString  rawQr = "ID:%1 DEPART:%2 DUREE:%3 TERMINUS:%4 PRIX:%5  " ;
                    rawQr = rawQr.arg(P.getid()).arg(P.getdepart()).arg(P.getduree()).arg(P.getterminus()).arg(P.getprix());
                    QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);



                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(140, 140) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->label_qrcode->setPixmap(pix);

            }
}
