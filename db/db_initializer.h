/*
 * Copyright (C) 2020  Lorenzo Torracchi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * caponzoniere is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CAPONZONIERE_DB_INITIALIZER_H
#define CAPONZONIERE_DB_INITIALIZER_H

#include <QObject>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>

class DbInitializer : public QObject {
Q_OBJECT

private:
    QNetworkReply *reply;
    QMutex mutex;
    QNetworkAccessManager qnam;
    QMutex* outMutex;
public:
    void initDb();
    void setOutMutex(QMutex* mutex);
private:
    QStringList getVersions();
private slots:
    void updateDb();
    void applyChange();
};


#endif //CAPONZONIERE_DB_INITIALIZER_H
