#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QString>
#include<QSqlQueryModel>

class Personnel
{
public:
    Personnel();
    Personnel(int,int,int,int,QString,QString,QString);
    int getid();
    int getsalaire();
    int getheures();
    int getheuresmaximale();
    QString getnom();
    QString getprenom();
    QString gettype();

    void setid(int);
    void setsalaire(int);
    void setheures(int);
    void setheuresmaaximale(int);


    void setnom(QString);
    void setprenom(QString);
    void settype(QString);

    bool ajouter();
    QSqlQueryModel*afficher ();
bool supprimer(int);
bool modifier(int);
QSqlQueryModel*trinom();
QSqlQueryModel*rechercher(QString);



void statistique(QVector<double>* ticks,QVector<QString> *labels);
private:
    int id,salaire,heures,heuresmaximale;
    QString nom,prenom,type;

};

#endif // PERSONNEL_H
