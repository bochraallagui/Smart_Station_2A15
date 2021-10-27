#ifndef METRO_H
#define METRO_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>


class metro
{
        int matricule;
        int nbr_places;
        int kilometrage ;
        int nbr_passagers;


public:
    metro();

    metro(int, int, int, int );
        //

        int  getmatricule(){return matricule;}
        int  getnbr_places(){return nbr_places;}
        int  getkilometrage(){return kilometrage;}
        int  getnbr_passagers(){return nbr_passagers;}

        //

        void setmatricule(int mat){matricule=mat;}
        void setid(int places){nbr_places=places;}
        void setage(int kilo){kilometrage=kilo;}
        void setpoids(int passagers){nbr_passagers=passagers;}

        //
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer (int matricule);





};

#endif // METRO_H
