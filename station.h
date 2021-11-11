#ifndef STATION_H
#define STATION_H
#include <QString>
#include <QSqlQueryModel>
class Station
{
public:
    Station();
    Station(QString,QString,int, int);
    QString getnom();
    QString getadresse();
    int getdimension();
    int getligne();
    void setnom(QString);
    void setadresse(QString);
    void setdimension(int);
    void setligne(int);
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel* afficher();
    bool modifier();
private:
    QString nom ;
    QString adresse ;
    int dimension;
    int ligne;


};

#endif // STATION_H
