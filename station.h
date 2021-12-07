#ifndef STATION_H
#define STATION_H
#include <QString>
#include <QSqlQueryModel>


class Station
{
public:
    Station();
        Station(QString,QString,QString, int);
        QString getnom();
        QString getregion();
        QString getadresse();
        int getcapacite();
        void setnom(QString);
        void setregion(QString);
        void setadresse(QString);
        void setcapacite(int);
        bool ajouter();
            bool supprimer(QString);
            QSqlQueryModel* afficher();
            bool modifier();
            bool rechercherNom();
            QSqlQueryModel* triparCapacite();
            QSqlQueryModel* triparCapaciteD();
            QSqlQueryModel* triparnom();
            QSqlQueryModel* triparnomD();
            bool rechercherRegion();
            QSqlQueryModel* rechercher_capacite(int capacite);
            QSqlQueryModel* rechercher_nom(QString nom);
            QSqlQueryModel* rechercher_region(QString region);
            QSqlQueryModel* rechercher_regionnom(QString region,QString nom);
            QSqlQueryModel* rechercher_regioncapacite(QString region,int capacite);
            QSqlQueryModel* rechercher_nomcapacite(QString nom,int capacite );
            QSqlQueryModel* rechercher_nomregioncapacite(QString nom,QString region,int capacite );
        void statistique(QVector<double>* ticks,QVector<QString> *labels);
private:
        QString nom ;
        QString region ;
        QString adresse ;
        int capacite;
};

#endif // STATION_H
