
#include "metro.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QSqlQueryModel>
Metro::Metro(){}
Metro::Metro(int matricule  , int nbr_passagers , int kilometrage , int nbr_places)
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
     QString res1=QString ::number(nbr_places);
     QString res2=QString ::number(kilometrage);
     QString res3=QString ::number(nbr_passagers);

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
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_places"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbr_passagers"));

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
    QString res1=QString ::number(nbr_places);
    QString res2=QString ::number(kilometrage);
    QString res3=QString ::number(nbr_passagers);
    query.prepare("UPDATE METRO SET MATRICULE=:matricule,NBRPLACES=:nbr_places,KILOMETRAGE=:kilometrage,NBRASSAGERS=:nbr_passagers where MATRICULE=:matricule");

    query.bindValue(":matricule",res);
    query.bindValue(":nbr_places",res1);
    query.bindValue(":kilometrage",res2);
    query.bindValue(":nbr_passagers",res3);

    return query.exec();
}


QSqlQueryModel* Metro::trimetro()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from METRO order by MATRICULE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbr_places"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbr_passagers"));


   return model;

}



QSqlQueryModel* Metro::recherchemetro(int matricule)

{

    QSqlQueryModel *model=new QSqlQueryModel();

                QString res=QString ::number(matricule);

            model->setQuery("select * from METRO where MATRICULE='"+res+"'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nombre de places"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("kilometrage"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("nombre de passagers"));


   return model;

}





void Metro::statistique(QVector<double>* ticks,QVector<QString> *labels)

{

    QSqlQuery q;

    int i=0;

    q.exec("select KILOMETRAGE from METRO");

    while (q.next())

    {

        QString identifiant = q.value(0).toString();

        i++;

        *ticks<<i;

        *labels <<identifiant;

    }

}

bool Metro ::affecter(int matricule,int id)

{

    QSqlQuery query;

    QString res = QString :: number(matricule);

    QString resc = QString :: number(id);

    query.prepare("insert into AFFECTER(MATRICULE,IDP)values(:matricule,:id)");

    //

    query.bindValue(":id",resc);

    query.bindValue(":matricule",res);

    return query.exec();

}




