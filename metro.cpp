#include "metro.h"

metro::metro(int matricule  , int nbr_passagers , int nbr_places , int kilometrage  )
{

         this->matricule=matricule;
         this->nbr_places=nbr_places;
         this->nbr_passagers=nbr_passagers;
         this->kilometrage=kilometrage;


}


bool metro ::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into place(matricules,nbr_passagers,nbr_places,kilometrage)""values(:matricule,:nbr_passagers,:nbr_places,:kilometrage)");
    //
    query.bindValue(":matricule",matricule);
    query.bindValue(":nbr_passagers",nbr_passagers);
    query.bindValue(":nbr_places",nbr_places);
    query.bindValue(":kilometrage",kilometrage);


    return query.exec();
}


QSqlQueryModel * metro :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("selet * from place");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_passagers"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("nbr_places"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));

return model;
}
bool metro ::supprimer(int matricule)
{
QSqlQuery query;
QString res=QString ::number(matricule);
query.prepare("delete from place where matricule= :matricule");
query.bindValue(":matricule",matricule);
return query.exec();
}
