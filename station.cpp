#include "station.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Station::Station()
{
nom="";adresse="";dimension=0;ligne=0;
}

Station::Station(QString nom,QString adresse,int dimension,int ligne)
{this->nom=nom;this->adresse=adresse;this->dimension=dimension;this->ligne=ligne;}
QString Station::getnom(){return nom;}
QString Station::getadresse(){return adresse;}
int Station::getdimension(){return dimension;}
int Station::getligne(){return ligne;}
void Station::setnom(QString nom){this->nom=nom;}
void Station::setadresse(QString adresse){this->adresse=adresse;}
void Station::setdimension(int dimension){this->dimension=dimension;}
void Station::setligne(int ligne){this->ligne=ligne;}

bool Station::ajouter()
{
    QSqlQuery query;
    QString dimension_string=QString::number(dimension);
    QString ligne_string=QString::number(ligne);
          query.prepare("INSERT INTO AJOUTER (nom, adresse, dimension,ligne) "
                        "VALUES (:id, :forename, :surname, :line)");
          query.bindValue(":id", nom);
          query.bindValue(":forename", adresse);
          query.bindValue(":surname", dimension_string);
          query.bindValue(":line", ligne_string);
          return query.exec();


}
bool Station::supprimer(QString nom)
{
    QSqlQuery query;
    QString dimension_string=QString::number(dimension);
    QString ligne_string=QString::number(ligne);
          query.prepare("Delete from AJOUTER where nom=:nom");
          query.bindValue(":nom", nom);
          return query.exec();




}





QSqlQueryModel* Station::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM AJOUTER");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("dimension"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ligne"));
return model ;
}

bool Station::modifier()
{
    QSqlQuery query;
    QString dimension_string=QString::number(dimension);
    QString ligne_string=QString::number(ligne);
  query.prepare("UPDATE AJOUTER SET   adresse=:adresse,dimension=:dimension,ligne=:ligne WHERE nom=:nom ");
  query.bindValue(":nom",nom);
  query.bindValue(":adresse", adresse);
  query.bindValue(":dimension", dimension_string);
  query.bindValue(":ligne", ligne_string);
     query.exec();


}
