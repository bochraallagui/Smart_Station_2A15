#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QSqlQueryModel>
Personnel::Personnel()
{ id=0;salaire=0; heures=0; nom=" ";prenom= " "; type= " ";experience=" ";}

Personnel::Personnel(int id,int salaire,int heures,QString nom,QString prenom,QString type,QString experience )
{this->id=id; this->salaire=salaire; this->heures=heures; this->nom=nom; this->prenom=prenom; this->type=type; this->experience=experience;}
int Personnel:: getid() {return id;}
int Personnel:: getsalaire() {return salaire;}
int Personnel:: getheures(){return heures;}
QString Personnel:: getnom(){return nom;}
QString Personnel:: getprenom(){return prenom;}
QString Personnel:: gettype(){return type;}
QString Personnel:: getexperience(){return experience;}
void Personnel:: setid(int id){this->id=id;}
void Personnel:: setsalaire(int salaire){this->salaire=salaire;}
void Personnel:: setheures(int heures){this->heures=heures;}
void Personnel:: setnom(QString nom){this->nom=nom;}
void Personnel:: setprenom(QString prenom){this->prenom=prenom;}
void Personnel:: settype(QString type){this->type=type;}
void Personnel:: setexperience(QString experience){this->experience=experience;}




bool Personnel ::ajouter ()
{
    QSqlQuery query ;
    QString id_string =QString::number(id);
    query.prepare("INSERT INTO personnel (id,salaire,heures,nom,prenom,type,experience) " "VALUES(:id, :salaire, :heures, :nom, :prenom, :type, :experience)");
    query.bindValue(0,id_string);
    query.bindValue(1,salaire);
    query.bindValue(2,heures);
    query.bindValue(3,nom);
    query.bindValue(4,prenom);
    query.bindValue(5,type);
    query.bindValue(6,experience);





return query.exec() ;
}
bool Personnel ::supprimer (int id)
{
    QSqlQuery query ;
    query.prepare("Delete from personnel where id=:id ");
    query.bindValue(0,id);

}
QSqlQueryModel* Personnel ::afficher()
{
 QSqlQueryModel*  model=new QSqlQueryModel();
 model->setQuery("SELECT* FROM personnel");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr ("id")) ;
 model->setHeaderData(1, Qt::Horizontal, QObject::tr ("salaire")) ;
 model->setHeaderData(2, Qt::Horizontal, QObject::tr ("heures")) ;
 model->setHeaderData(3, Qt::Horizontal, QObject::tr ("nom")) ;
 model->setHeaderData(4, Qt::Horizontal, QObject::tr ("prenom")) ;
 model->setHeaderData(5, Qt::Horizontal, QObject::tr ("type")) ;
 model->setHeaderData(6, Qt::Horizontal, QObject::tr ("experience ")) ;


 return model ;

}
bool Personnel::modifier(int id)
{  QSqlQuery query ;
QString id_string =QString::number(id);
query.prepare("Update  personnel set salaire=:salaire ,heures=:heures,nom=:nom ,prenom=:prenom,type=:type,experience=:experience where id=:id ");
query.bindValue(":id",id_string );
query.bindValue(":salaire",salaire);
query.bindValue(":heures",heures);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":type",type);
query.bindValue(":experience",experience);
return    query.exec();
}
