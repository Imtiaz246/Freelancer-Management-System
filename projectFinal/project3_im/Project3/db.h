#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QDebug>

class db
{
public:
    QSqlDatabase AllMemberDetails ;

    /* Database Connection Openning */

    bool connOpen();

    /* Database Connection Closing */

    bool connClose();

    /* Database Query Part */

    int DatabaseQuery(QString qry);
};

#endif // DB_H
