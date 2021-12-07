#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQueryModel>


class Client
{
public:
    Client();
    Client(int,QString,QString,QString,int,int);
    int getidc();
    QString getnom();
    QString getprenom();
    QString getadresse();
    int getnbticket();
    int getage();
    void setidc(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setnbticket(int);
    void setage(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* trierclient();
    QSqlQueryModel* rechercherclient(QString);
    void statistique(QVector<double>* ticks,QVector<QString> *labels);


private:
    int idc,nbticket,age;
    QString nom , prenom,adresse;
};

#endif // CLIENT_H
