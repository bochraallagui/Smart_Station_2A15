#include "station.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Station::Station()
{
nom="";region="";adresse="";capacite=0;
}

Station::Station(QString nom,QString region,QString adresse,int capacite)
{this->nom=nom;this->region=region;this->adresse=adresse;this->capacite=capacite;}
QString Station::getnom(){return nom;}
QString Station::getregion(){return region;}
QString Station::getadresse(){return adresse;}
int Station::getcapacite(){return capacite;}
void Station::setnom(QString nom){this->nom=nom;}
void Station::setregion(QString region){this->region=region;}
void Station::setadresse(QString adresse){this->adresse=adresse;}
void Station::setcapacite(int capacite){this->capacite=capacite;}

bool Station::ajouter()
{
    QSqlQuery query;
    QString capacite_string=QString::number(capacite);
          query.prepare("INSERT INTO STATION (nom,region,adresse,capacite) "
                        "VALUES (:id, :forename, :surname, :capacite)");
          query.bindValue(":id", nom);
          query.bindValue(":forename", region);
          query.bindValue(":surname", adresse);
          query.bindValue(":capacite", capacite_string);
           query.exec();


}
bool Station::supprimer(QString nom)
{
    QSqlQuery query;
    QString capacite_string=QString::number(capacite);
          query.prepare("Delete from STATION where nom=:nom");
          query.bindValue(":nom", nom);
          return query.exec();




}





QSqlQueryModel* Station::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM STATION");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));
return model ;
}

bool Station::modifier()
{
    QSqlQuery query;
    QString capacite_string=QString::number(capacite);
  query.prepare("UPDATE TAB_STATION SET   region=:region,adresse=:adresse,capacite=:capacite WHERE nom=:nom ");
  query.bindValue(":nom",nom);
  query.bindValue(":region", region);
  query.bindValue(":adresse", adresse);
  query.bindValue(":capacite", capacite_string);
     query.exec();


}

QSqlQueryModel* Station::rechercher_capacite(int capacite)
{
    QSqlQuery * q = new  QSqlQuery ();
    QString id_string=QString::number(capacite);
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from STATION where capacite=:capacite");
                     q->bindValue(":capacite",id_string );
                     q->exec();

         model->setQuery(*q);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));


        return model;
 }
QSqlQueryModel* Station::rechercher_nom(QString nom)
{
    QSqlQuery * q = new  QSqlQuery ();

                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from STATION where nom=:nom");
                     q->bindValue(":nom",nom );
                     q->exec();

         model->setQuery(*q);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));



        return model;

}
QSqlQueryModel* Station::rechercher_region(QString region)
{
    QSqlQuery * q = new  QSqlQuery ();

                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from STATION where region=:region");
                     q->bindValue(":region",region );
                     q->exec();

         model->setQuery(*q);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));



        return model;

}
QSqlQueryModel * Station::rechercher_regionnom(QString region, QString nom)
{
    QSqlQuery *qry= new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->prepare("select * from STATION where prenom=:prenom and nom=:nom");
    qry->bindValue(":region",region);
    qry->bindValue(":nom",nom);
    qry->exec();

       model->setQuery(*qry);
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

        return model;


}
QSqlQueryModel * Station::rechercher_nomcapacite(QString nom, int capacite)
{
    QSqlQuery *qry= new QSqlQuery();
    QString id_string=QString::number(capacite);
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->prepare("select * from STATION where nom=:nom and capacite=:capacite");
    qry->bindValue(":nom",nom);
    qry->bindValue(":capacite",id_string);
    qry->exec();

       model->setQuery(*qry);
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

        return model;


}
QSqlQueryModel * Station::rechercher_regioncapacite(QString region, int capacite)
{
    QSqlQuery *qry= new QSqlQuery();
    QString id_string=QString::number(capacite);
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->prepare("select * from STATION where idC=:idC and prenom=:prenom");
    qry->bindValue(":region",region);
    qry->bindValue(":prenom",id_string);
    qry->exec();

       model->setQuery(*qry);
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

        return model;


}
QSqlQueryModel * Station::rechercher_nomregioncapacite(QString nom,QString region, int capacite)
{
    QSqlQuery *qry= new QSqlQuery();
    QString id_string=QString::number(capacite);
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->prepare("select * from STATION where nom=:nom and region=:region and capacite=:capacite");
    qry->bindValue(":nom",nom);
    qry->bindValue(":region",region);
    qry->bindValue(":region",id_string );
    qry->exec();

       model->setQuery(*qry);
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

        return model;


}
QSqlQueryModel* Station::triparCapacite()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM STATION order by Capacite ASC");
                 q->exec();
                 model->setQuery(*q);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));
                 return model;


}
QSqlQueryModel* Station::triparCapaciteD()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM STATION order by Capacite DESC");
                 q->exec();
                 model->setQuery(*q);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));
                 return model;


}
QSqlQueryModel* Station::triparnom()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM STATION order by nom ASC");
                 q->exec();
                 model->setQuery(*q);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));
                 return model;


}
QSqlQueryModel* Station::triparnomD()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM STATION order by nom DESC");
                 q->exec();
                 model->setQuery(*q);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("region"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));
                 return model;


}


void Station::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select NOM from STATION");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();///********///
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
