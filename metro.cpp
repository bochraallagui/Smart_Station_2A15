#include "metro.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QSqlQueryModel>
Metro::Metro(){}
Metro::Metro(int matricule  , int nbr_passagers , int kilometrage , int nbr_places  )
{

         this->matricule=matricule;
         this->nbr_places=nbr_places;
         this->kilometrage=kilometrage;
         this->nbr_passagers=nbr_passagers;
}


bool Metro ::ajouter()
{
    QSqlQuery query;
     QString res=QString ::number(matricule);

    query.prepare("insert into METRO(MATRICULE,NBRPLACES,KILOMETRAGE,NBRASSAGERS)""values(:matricule,:nbr_places,:kilometrage,:nbr_passagers )");
    //
    query.bindValue(":matricule",res);
    query.bindValue(":nbr_places",nbr_places);
    query.bindValue(":kilometrage",kilometrage);
    query.bindValue(":nbr_passagers",nbr_passagers);



    return query.exec();
}


QSqlQueryModel * Metro :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("select * from METRO");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("nbr_places"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_passagers"));

return model;
}


bool Metro ::supprimer(int matricule)
{
QSqlQuery query;
  QString res=QString ::number(matricule);
query.prepare("delete from METRO where MATRICULE= :matricule");
query.bindValue(":matricule",res);
return query.exec();
}


bool Metro::modifier(int matricule)
{
    QSqlQuery query;
    QString res=QString ::number(matricule);

    query.prepare("UPDATE METRO SET MATRICULE=:matricule,NBRPLACES=:nbr_places,KILOMETRAGE=:kilometrage,NBRASSAGERS=:nbr_passagers where MATRICULE=:matricule");

    query.bindValue(":matricule",res);
    query.bindValue(":nbr_places",nbr_places);
    query.bindValue(":kilometrage",kilometrage);
    query.bindValue(":nbr_passagers",nbr_passagers);
    return query.exec();
}


QSqlQueryModel* Metro::trimatricule()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from METRO order by MATRICULE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_places"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbr_passagers"));


   return model;

}


QSqlQueryModel* Metro::triplaces()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from METRO order by NBRPLACES");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_places"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbr_passagers"));


   return model;

}


QSqlQueryModel* Metro::trikilometrage()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from METRO order by KILOMETRAGE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_places"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbr_passagers"));


   return model;

}






