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
    trajet(int,QString,int,QString,int,QDate);
    int getprix();
    QString getdepart();
    int getid();
    int getduree();
    QString getterminus();
    QDate getdate();

    void setprix(int);
    void setdepart(QString);
    void setid(int);
    void setduree(int);
    void setterminus(QString);
    void setdate(QDate);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int );
    bool modifier(int ,QString,int,QString,int,QDate);

    QSqlQueryModel * trier(int choix);
    QSqlQueryModel * rechercher(int choix);
    void statistiques(QWidget * w);
    bool export_txt();

private:
    int prix,id,duree;
    QString terminus,depart;
    QDate date_t;




};

#endif // TRAJET_H
