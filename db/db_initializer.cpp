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

#include <QtNetwork>
#include "db_initializer.h"

void DbInitializer::setOutMutex(QMutex *outMutex) {
    this->outMutex = outMutex;
}

void DbInitializer::initDb() {
    outMutex->lock();
    //TODO retrieve app version
    reply = qnam.get(QNetworkRequest( QUrl::fromUserInput("clorofilla.io/versions/caponzoniere/1.0.0")));
    connect(reply, SIGNAL(&QNetworkReply::finished), this, SLOT(DbInitializer::updateDb()));
}

QStringList DbInitializer::getVersions() {
    QJsonArray dbVersions = QJsonDocument::fromJson(reply->readAll()).array();
    QStringList versionsToGetChanges;
    bool toAdd = false;
    QString currentDbVersion = "v1";
    foreach (const QJsonValue & v, dbVersions) {
        if (currentDbVersion == v.toString()) {
            toAdd = true;
            continue;
        }
        if (toAdd) {
            versionsToGetChanges.append(v.toString());
        }
    }
    return versionsToGetChanges;
}

void DbInitializer::updateDb() {
    if (reply->error()) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    QStringList versionsToGetChanges = getVersions();
    foreach (const QString v, versionsToGetChanges) {
        mutex.lock();
        reply = qnam.get(QNetworkRequest( QUrl::fromUserInput("clorofilla.io/changes/caponzoniere/" + v)));
        connect(reply, SIGNAL(&QNetworkReply::finished), this, SLOT(DbInitializer::applyChange()));
    }
    outMutex->unlock();
}

void DbInitializer::applyChange() {
    QString change = QString(reply->readAll());
    //TODO exec sql
    qDebug() << "changed applied";
    mutex.unlock();
}
