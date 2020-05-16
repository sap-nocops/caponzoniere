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

void DbInitializer::initDb() {
    qDebug() << "init";
    //TODO retrieve app version
    QUrl url;
    url.setScheme("http");
    url.setHost("localhost");
    //url.setPath("/versions/caponzoniere/1.0.0");
    url.setPort(8080);
    QNetworkRequest request;
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setUrl(url);
    qnam = new QNetworkAccessManager();
    QEventLoop loop;
    reply = qnam->get(request);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    updateDb();
    qDebug() << "chiamato";
}

QStringList DbInitializer::getVersions() {
    QString tmp = QString::fromUtf8(reply->readAll());
    qDebug() << tmp;
    QJsonArray dbVersions = QJsonDocument::fromJson(tmp.toUtf8()).array();
    QStringList versionsToGetChanges;
    bool toAdd = false;
    //TODO retrieve current db version
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
    qDebug() << "update";
    if (handleError()) {
        return;
    }
    qDebug() << "no error";
    QStringList versionsToGetChanges = getVersions();
    foreach (const QString v, versionsToGetChanges) {
        QEventLoop loop;
        reply = qnam->get(QNetworkRequest(QUrl("http://localhost:8080/changes/caponzoniere/" + v)));
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        if (handleError()) {
            break;
        }
        qDebug() << "cambiamento";
    }
    qDebug() << "finito";
}

void DbInitializer::applyChange() {
    QString change = QString::fromUtf8(reply->readAll());
    //TODO exec sql
    qDebug() << change;
    qDebug() << "changed applied";
}

bool DbInitializer::handleError() {
    if (reply->error()) {
        qDebug() << "error" << reply->error();
        reply->deleteLater();
        reply = nullptr;
        return true;
    }
    return false;
}