#include "trajet.h"
#include<QString>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

trajet::trajet()
{
code=0; depart=0; id=0; redandance=0; terminus="";
}


trajet::trajet(int id,int depart,int redandance,QString terminus,int code, QDate date_t)
{this->code=code;this->depart=depart;this->id=id;this->redandance=redandance;this->terminus=terminus;this->date_t=date_t;}


int trajet:: getcode(){return code;}
int trajet:: getdepart(){return depart;}
int trajet:: getid(){return id;}
int trajet::getredandance(){return redandance;}
QString trajet::getterminus(){return terminus;}
QDate trajet::getdate(){return date_t;}



void trajet:: setcode(int code){this->code=code;}
void trajet:: setdepart(int depart){this->depart=depart;}
void trajet:: setid(int id){this->id=id;}
void trajet::setredandance(int redandance){this->redandance=redandance;}
void trajet::setterminus(QString terminus){this->terminus=terminus;}
void trajet::setdate(QDate date_t){this->date_t=date_t;}

bool trajet::ajouter()
{
    QSqlQuery query;
    QString res =QString::number(id);

    QString depart_string =QString::number(depart);
    QString code_string=QString::number(code);
    QString redandance_string =QString::number(redandance);
    query.prepare("insert into TRAJET(ID , DEPART , REDANDANCE , TERMINUS, CODE, DATE_T) values(:id , :depart , :redandance ,:terminus ,:code,:date)");

    query.bindValue(":id",res);
    query.bindValue(":depart",depart_string);
    query.bindValue(":code",code_string);
    query.bindValue(":terminus",terminus);
    query.bindValue(":redandance",redandance_string);
    query.bindValue(":date",date_t);
    return query.exec();//exec() envoie la requete pour l'executer


}
QSqlQueryModel *trajet::afficher ()
{
   QSqlQueryModel * model =new QSqlQueryModel();

    //model->setQuery("select * form trajet");
   model->setQuery("SELECT id, depart , redandance , terminus , code, date_t FROM trajet");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("depart"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("code"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("terminus"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("redandance"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("date"));
    return model ;

}
bool trajet::supprimer(int ID)
{
QSqlQuery query ;
QString res=QString::number(ID);
query.prepare("Delete from trajet where ID= :id");
query.bindValue(":id",res);
return query.exec();
}
bool trajet:: modifier(int i ,int d,int r,QString t,int c,QDate dat)
 {
     QSqlQuery query ;
     QString id_string = QString::number(i);
     query.prepare("update trajet set depart=:depart,code=:code,redandance=:redandance,terminus=:terminus,date_t=:date where id=:id");
     query.bindValue(":id",id_string);
     query.bindValue(":depart",d);
     query.bindValue(":code",c);
     query.bindValue(":redandance",r);
     query.bindValue(":terminus",t);
     query.bindValue(":date",dat);
     return query.exec();
}

QSqlQueryModel * trajet::trier(int choix)
{
    QSqlQueryModel * model=afficher();
    QString query;
    QString ch;

        switch (choix)
        {
            case 1:
            {
              ch="id";
              break;
            }
            case 2:
            {
              ch="code";
              break;
            }
            case 3:
            {
              ch="redandance";
              break;
            }
            default:
              break;
        }

 query="SELECT * FROM trajet ORDER BY "+ch+" DESC";
    model->setQuery(query);
    return model;
}

QSqlQueryModel * trajet::rechercher(int choix)
{
    QSqlQueryModel * model=afficher();
    QString res,ch;
    switch (choix)
    {
        case 1:
        {
          ch="id";
          res= QString::number(id);
          break;
        }
        case 2:
        {
          ch="code";
          res=QString::number(code);
          break;
        }
        case 3:
        {
          ch="terminus";
          res="'"+terminus+"'";
          break;
        }
        default:
          break;
    }
    QString query="SELECT * FROM trajet WHERE "+ch+"="+res;
    model->setQuery(query);
    return model;
}

void trajet::statistiques(QWidget * w)
{
    int nb1 = 0,nb2=0,nb3=0;
        QSqlQuery query("SELECT COUNT(*) FROM trajet WHERE terminus='Tunis'");
        while(query.next())
        {
            nb1 = query.value(0).toInt();
        }
        QSqlQuery query2("SELECT COUNT(*) FROM trajet WHERE terminus='Sfax'");
        while(query2.next())
        {
           nb2= query2.value(0).toInt();
        }
        QSqlQuery query3("SELECT COUNT(*) FROM trajet WHERE terminus='Bizerte'");
        while(query2.next())
        {
           nb3= query3.value(0).toInt();
        }

    QPieSeries *series = new QPieSeries();
    series->append("Tunis",nb1);
    series->append("Sfax",nb2);
    series->append("Bizerte",nb3);
    series->setHoleSize(0.8);
    series->setPieSize(1.0);
    QPieSlice * T = series->slices().at(0);
    QPieSlice * S = series->slices().at(1);
    QPieSlice * B = series->slices().at(2);
    T->setLabelVisible(true);
    S->setLabelVisible(true);
    B->setLabelVisible(true);
    T->setBrush(QColor::fromRgb(255, 0, 0));
    S->setBrush(QColor::fromRgb(0, 255, 0));
    B->setBrush(QColor::fromRgb(0, 0, 255));
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Terminus");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView * chartview = new QChartView(chart);
    chartview->resize(w->width(),w->height());
    chartview->setParent(w);
}

bool trajet::export_msg()
{
    bool test=false;
    QSqlQueryModel * model=afficher();
    QString textData;
    int rows = model->rowCount();
    int columns = model->columnCount();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
                textData += model->data(model->index(i,j)).toString();
                textData += " || " ;
        }
        textData += "\n";
    }
    QFile txtFile("msg.txt");
    if(txtFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        test=true;
        QTextStream out(&txtFile);
        out << "depart------code------id-----terminus------redandance-----date\n";
        out << textData;
        txtFile.close();
    }
    return test;
}

int trajet::plan()
{
    int i=0;
    QSqlQuery query("SELECT date_t FROM trajet");
    while (query.next())
    {
        QDate date=query.value(0).toDate();
        if (date==QDate::currentDate())
        {
            i++;
        }

    }
    return i;
}
