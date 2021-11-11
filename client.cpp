#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
Client::Client()
{
id=0;
nom=" ";
prenom=" ";
adresse=" ";
}
Client::Client(int id,QString nom,QString prenom,QString adresse)
{this->id=id ;this->nom=nom;this->prenom=prenom;this->adresse=adresse;}
int Client::getid(){return id ;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client:: getadresse(){return adresse;}
void Client::setid(int id){this->id=id;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setadresse(QString adresse){this->adresse=adresse;}
bool Client::ajouter()
{
                  QString id_string=QString::number(id);
                       QSqlQuery query;

                             query.prepare("INSERT INTO client (id, nom, prenom,adresse) "
                                           "VALUES (:id, :nom, :prenom, :adresse)");
                             query.bindValue(0, id_string);
                             query.bindValue(1, nom);
                             query.bindValue(2, prenom);
                             query.bindValue(3, adresse);
                            return query.exec();
}


bool Client::supprimer(int id)
{
    QSqlQuery query;

          query.prepare("Delete from client where id=:id");
          query.bindValue(0, id);

         return query.exec();
}



QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM client ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    return model ;
}

bool Client::modifier(int id)
{  QSqlQuery query ;
QString id_string =QString::number(id);
query.prepare("Update  client set nom=:nom ,prenom=:prenom, adresse=:adresse where id=:id ");
query.bindValue(":id",id_string );
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":adresse",adresse);

return    query.exec();
}
