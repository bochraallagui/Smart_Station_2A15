#include "connection.h"
#include <QDebug>

Connection::Connection()
{

}

bool Connection::ouvrirConnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("bochra");//inserer nom de l'utilisateur
db.setPassword("bochra");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;



else
    qDebug()<< db.lastError().text();

    return  test;
}
