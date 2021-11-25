#ifndef METRO_H
#define METRO_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>


class Metro
{
        int matricule;
        int nbr_places;
        int kilometrage;
        int nbr_passagers;


public:
        Metro();

    Metro(int, int, int, int );
        //
      int  getmatricule(){return matricule;}
        int  getnbr_places(){return nbr_places;}
        int  getkilometrage(){return kilometrage;}
        int  getnbr_passagers(){return nbr_passagers;}

        //

        void setmatricule(int mat){matricule=mat;}
        void setnbr_places(int places){nbr_places=places;}
        void setkilometrage(int kilo){kilometrage=kilo;}
        void setnbr_passagers(int passagers){nbr_passagers=passagers;}

        //
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer (int);
        bool modifier (int);
        QSqlQueryModel *trimetro();
        QSqlQueryModel *recherchemetro(int matricule);
        void statistique(QVector<double>* ticks,QVector<QString> *labels);
        bool affecter(int matricule,int id);
};

#endif // METRO_H
