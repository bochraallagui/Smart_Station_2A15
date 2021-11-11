#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQueryModel>
class Client
{
public:
    Client();
    Client(int,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
private:
    int id;
    QString nom , prenom,adresse;
};

#endif // CLIENT_H
