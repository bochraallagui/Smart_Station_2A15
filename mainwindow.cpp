#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metro.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QIntValidator>
#include <QPrinter>


MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
 ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QSqlQueryModel *modelll=new QSqlQueryModel();
             modelll->setQuery("select MATRICULE from METRO order by matricule");
     ui->comboBoxMet->setModel(modelll);
  ui->la_matricule->setValidator(new QIntValidator(001,9999999,this));
  ui->nbr_places->setValidator(new QIntValidator(150,300,this));
  ui->le_kilometrage->setValidator(new QIntValidator(0,9999999,this));
  ui->nbr_passagers->setValidator(new QIntValidator(0,300,this));
  ui->tableView->setModel(M.afficher());
  QSqlQueryModel *modell=new QSqlQueryModel();
             modell->setQuery("select NOM from PERSONNEL order by NOM");
     ui->comboBox->setModel(modell);
     int ret=a.connect_arduino();
           switch (ret) {
           case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
               break;
           case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
               break;
           case(-1):qDebug()<<"arduino is not available";
           }
     QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



}

MainWindow::~MainWindow()
{
   delete ui;
}
void MainWindow::update_label()
{
data=a.read_from_arduino();
qDebug()<<data;
if (data == "1")
  {

M.incr(ui->comboBoxMet->currentText().toInt());
if(M.nbplaces(ui->comboBoxMet->currentText().toInt()))
{a.write_to_arduino("2");
    QMessageBox::critical(nullptr, QObject::tr("ALERT"),
                QObject::tr("METRO COMPLET.\n"
                            "Click Cancel to exit."), QMessageBox::Ok);

}
}
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
 ui->tableView->setModel(M.trimetro());
}


void MainWindow::on_pb_rechercher_clicked()
{
    int matricule=ui->la_matricule->text().toInt();

       if (matricule==NULL) {

           QMessageBox::information(this, tr("Empty Field"),

               tr("Please enter a Number."));

           return;

       } else {

       ui->tableView->setModel(M.recherchemetro(matricule));

       }

}




void MainWindow::on_tabWidget_currentChanged(int index)
{
    // background //
                  QLinearGradient gradient(0, 0, 0, 400);
                  gradient.setColorAt(0, QColor(90, 90, 90));
                  gradient.setColorAt(0.38, QColor(171, 120, 86));
                  gradient.setColorAt(1, QColor(171, 120, 86));
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
                    if (dialog->exec() == QDialog::Accepted) {

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

            while(q.next()){


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

                                "click cancel to exit."),QMessageBox::Cancel);

            }
}




