#ifndef TRAJET_H
#define TRAJET_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class trajet
{
public:
    trajet();
    trajet(int,int,int,QString,int,QDate);
    int getcode();
    int getdepart();
    int getid();
    int getredandance();
    QString getterminus();
    QDate getdate();


    void setcode(int);
    void setdepart(int);
    void setid(int);
    void setredandance(int);
    void setterminus(QString);
    void setdate(QDate);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int );
    bool modifier(int ,int,int,QString,int,QDate);

    QSqlQueryModel * trier(int choix);
    QSqlQueryModel * rechercher(int choix);
    void statistiques(QWidget * w);
    bool export_msg();
    int plan();

private:
    int code,depart,id,redandance;

    QString terminus;
    QDate date_t;




};

#endif // TRAJET_H
