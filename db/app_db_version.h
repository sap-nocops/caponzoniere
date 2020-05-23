//
// Created by sap on 23/05/20.
//

#ifndef CAPONZONIERE_APP_DB_VERSION_H
#define CAPONZONIERE_APP_DB_VERSION_H

#include <QString>

class AppDbVersion {
public:
    AppDbVersion(QString appVer, QString dbVer);
    QString getAppVersion();
    QString getDbVersion();
private:
    QString appVer;
    QString dbVer;
};


#endif //CAPONZONIERE_APP_DB_VERSION_H
