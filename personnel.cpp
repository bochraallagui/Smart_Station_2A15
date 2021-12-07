#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <qcustomplot.h>
Personnel::Personnel()
{ id=0;salaire=0; heures=0;heuresmaximale=0; nom=" ";prenom= " "; type= " ";}

Personnel::Personnel(int id,int salaire,int heures,int heuresmaximale,QString nom,QString prenom,QString type )
{this->id=id; this->salaire=salaire; this->heures=heures,this->heuresmaximale=heuresmaximale; this->nom=nom; this->prenom=prenom; this->type=type;}
int Personnel:: getid() {return id;}
int Personnel:: getsalaire() {return salaire;}
int Personnel:: getheures(){return heures;}
int Personnel:: getheuresmaximale(){return heuresmaximale;}

QString Personnel:: getnom(){return nom;}
QString Personnel:: getprenom(){return prenom;}
QString Personnel:: gettype(){return type;}
void Personnel:: setid(int id){this->id=id;}
void Personnel:: setsalaire(int salaire){this->salaire=salaire;}
void Personnel:: setheures(int heures){this->heures=heures;}
void Personnel:: setheuresmaaximale(int heuresmaximale){this->heuresmaximale=heuresmaximale;}
void Personnel:: setnom(QString nom){this->nom=nom;}
void Personnel:: setprenom(QString prenom){this->prenom=prenom;}
void Personnel:: settype(QString type){this->type=type;}





bool Personnel ::ajouter ()
{
    QSqlQuery query ;
    QString id_string =QString::number(id);
    query.prepare("INSERT INTO personnel (id,salaire,heures,heuresmaximale,nom,prenom,type) " "VALUES(:id, :salaire, :heures, :heuresmaximale, :nom, :prenom, :type )");
    query.bindValue(0,id_string);
    query.bindValue(1,salaire);
    query.bindValue(2,heures);
    query.bindValue(3,heuresmaximale);

    query.bindValue(4,nom);
    query.bindValue(5,prenom);
    query.bindValue(6,type);






return query.exec() ;
}
bool Personnel ::supprimer (int id)
{
    QSqlQuery query ;
     QString id_string =QString::number(id);
    query.prepare("Delete from personnel where id=:id ");
    query.bindValue(":id",id_string);
    return query.exec();

}
QSqlQueryModel* Personnel ::afficher()
{
 QSqlQueryModel*  model=new QSqlQueryModel();
 model->setQuery("SELECT* FROM personnel");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr ("id")) ;
 model->setHeaderData(1, Qt::Horizontal, QObject::tr ("salaire")) ;
 model->setHeaderData(2, Qt::Horizontal, QObject::tr ("heures"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr ("heuresmaximale"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr ("nom")) ;
 model->setHeaderData(5, Qt::Horizontal, QObject::tr ("prenom")) ;
 model->setHeaderData(6, Qt::Horizontal, QObject::tr ("type")) ;



 return model ;

}
bool Personnel::modifier(int id)
{  QSqlQuery query ;
QString id_string =QString::number(id);
query.prepare("Update  personnel set salaire=:salaire ,heures=:heures,nom=:nom ,prenom=:prenom,type=:type where id=:id ");
query.bindValue(":id",id_string );
query.bindValue(":salaire",salaire);
query.bindValue(":heures",heures);
query.bindValue(":heuresmaximale",heuresmaximale);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":type",type);

return    query.exec();
}
QSqlQueryModel* Personnel::trinom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from personnel order by id,nom,type");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("salaire"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("heures"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("heuresmaximale"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("type"));



   return model;

}


QSqlQueryModel* Personnel::rechercher(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();

            model->setQuery("select * from personnel where NOM like '%"+nom+"%' or ID like '%"+nom+"%' or SALAIRE like '%"+nom+"%'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("salaire"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("heures"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("heuresmaximale"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("type"));

   return model;

}


void Personnel::statistique(QVector<double>* ticks,QVector<QString> *labels)

{

    QSqlQuery q;

    int i=0;

    q.exec("select SALAIRE from PERSONNEL");

    while (q.next())

    {

        QString identifiant = q.value(0).toString();

        i++;

        *ticks<<i;

        *labels <<identifiant;

    }

}




