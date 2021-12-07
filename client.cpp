#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QVector>
#include<qcustomplot.h>


Client::Client()
{
idc=0;
nom=" ";
prenom=" ";
adresse=" ";
nbticket=0;
age=0;
}

Client::Client(int idc,QString nom,QString prenom,QString adresse,int nbticket,int age)
{this->idc=idc ;this->nom=nom;this->prenom=prenom;this->adresse=adresse;this->nbticket=nbticket;this->age=age;}
int Client::getidc(){return idc ;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client:: getadresse(){return adresse;}
int Client::getnbticket(){return nbticket ;}
int Client::getage(){return age ;}

void Client::setidc(int idc){this->idc=idc;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setadresse(QString adresse){this->adresse=adresse;}
void Client::setnbticket(int nbticket){this->nbticket=nbticket;}
void Client::setage(int age){this->age=age;}

bool Client::ajouter()
{
                  QString idc_string=QString::number(idc);
                       QSqlQuery query;

                             query.prepare("INSERT INTO CLIENT (idc, nom, prenom,adresse,nbticket,age) "
                                           "VALUES (:idc, :nom, :prenom, :adresse,:nbticket,:age)");
                             query.bindValue(":idc", idc_string);
                             query.bindValue(":nom", nom);
                             query.bindValue(":prenom", prenom);
                             query.bindValue(":adresse", adresse);
                             query.bindValue(":nbticket",nbticket);
                             query.bindValue(":age",age);
                            return query.exec();
}


bool Client::supprimer(int idc)
{
    QSqlQuery query;

          query.prepare("Delete from client where idc=:idc");
          query.bindValue(":idc", idc);

         return query.exec();
}



QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM client ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbticket"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("age"));
    return model ;
}

bool Client::modifier(int idc)
{  QSqlQuery query ;
QString idc_string =QString::number(idc);
query.prepare("Update  client set nom=:nom ,prenom=:prenom, adresse=:adresse ,nbticket=:nbticket,age=:age where idc=:idc ");
query.bindValue(":idc",idc_string );
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":adresse",adresse);
query.bindValue(":nbticket",nbticket);
query.bindValue(":age",age);

return    query.exec();
}



QSqlQueryModel* Client::trierclient()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from client order by idc,nom,nbticket,age");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("idc"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("nbticket"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("age"));


   return model;

}




QSqlQueryModel* Client::rechercherclient(QString nom)
{
QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from client where NOM like '%"+nom+"%' or IDC like '%"+nom+"%' or NBTICKET like '%"+nom+"%'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("idc"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("nbticket"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("age"));


   return model;
}




void Client::statistique(QVector<double>* ticks,QVector<QString> *labels)

{

    QSqlQuery q;

    int i=0;

    q.exec("select age from CLIENT");

    while (q.next())

    {

        QString identifiant = q.value(0).toString();

        i++;

        *ticks<<i;

        *labels <<identifiant;

    }

}
