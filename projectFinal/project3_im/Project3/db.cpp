#include "db.h"

bool db::connOpen() {
    AllMemberDetails = QSqlDatabase::addDatabase("QSQLITE"); // Database Object Name
    AllMemberDetails.setDatabaseName("C:/Users/Riaz/Desktop/projectFinal/DatabaseFiles/AllMemberDetails.db");
    AllMemberDetails.open();

    if (AllMemberDetails.isOpen()) {
        return true;
    } else {
        return false;
    }
}

bool db::connClose() {
    AllMemberDetails.close();
    AllMemberDetails.removeDatabase(QSqlDatabase::defaultConnection);

    if (!AllMemberDetails.isOpen()) {
        return true;
    } else {
        return false;
    }
}

int db::DatabaseQuery(QString qry) {
    QSqlQuery Query;
    Query.exec(qry);

    int foundNumber = 0;

    if (Query.next()) {
        foundNumber++;
    }

    if (foundNumber == 1) {
        return 1;
    }
    else if (foundNumber > 1) {
        return 2;
    }
    else if (foundNumber < 1) {
        return -1;
    }
    else return 0;
}
