#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QString>
#include<QSqlQueryModel>

class Personnel
{
public:
    Personnel();
    Personnel(int,int,int,QString,QString,QString,QString);
    int getid();
    int getsalaire();
    int getheures();
    QString getnom();
    QString getprenom();
    QString gettype();
    QString getexperience();
    void setid(int);
    void setsalaire(int);
    void setheures(int);
    void setnom(QString);
    void setprenom(QString);
    void settype(QString);
    void setexperience(QString);
    bool ajouter();
    QSqlQueryModel*afficher ();
bool supprimer(int);
bool modifier(int);
private:
    int id,salaire,heures;
    QString nom,prenom,type,experience;

};

#endif // PERSONNEL_H
