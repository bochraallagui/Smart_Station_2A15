#include "connection.h"
// test tutoriel Git
// ici c'est la gestion
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("mahdi");//inserer nom de l'utilisateur
db.setPassword("mahdi");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
