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
#include <QtSql>
#include "db_initializer.h"
#define foreach Q_FOREACH

bool DbInitializer::createDbFolderIfNotExists(const QString &dbPath) {
    if (!QFile::exists(dbPath)) {
        QDir dir;
        bool createOk = dir.mkpath(dbPath);
        if (!createOk) {
            qWarning() << "Unable to create DB directory" << dbPath;
            return false;
        }
    }
    return true;
}

bool DbInitializer::initDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/db");
    if (!createDbFolderIfNotExists(dbPath)) {
        return false;
    }
    db.setDatabaseName(dbPath + "/caponzoniere_db.sqlite");
    if (!db.open()) {
        qDebug() << "failed to connect to db";
        return false;
    }

    if (QSqlDatabase::database().tables().contains(QStringLiteral("db_version"))) {
        qDebug() << "db already initialized";
        return updateDb();
    }

    QSqlQuery query(db);
    QString sql = "CREATE TABLE IF NOT EXISTS db_version(id CHAR(10) PRIMARY KEY);";
    if (!query.exec(sql)) {
        qDebug() << "Error executing db_version creation";
        qDebug() << query.lastError().text();
        return false;
    }
    return updateDb();
}

QJsonArray DbInitializer::listDbVersions() {
    //TODO retrieve app version
    QString appVersion = "1.0.0";
    QUrl url;
    url.setScheme("http");
    url.setHost("clorofilla.io");
    url.setPath("/versions/caponzoniere/" + appVersion);
    url.setPort(8000);
    QNetworkRequest request;
    request.setUrl(url);
    qnam = new QNetworkAccessManager();
    QEventLoop loop;
    reply = qnam->get(request);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->error()) {
        handleError();
        throw "cannot get db versions";
    }
    return QJsonDocument::fromJson(reply->readAll()).array();
}

QStringList DbInitializer::getVersions() {
    QJsonArray dbVersions = listDbVersions();
    QStringList versionsToGetChanges;
    QString currentDbVersion = getCurrentDbVersion();
    bool toAdd = currentDbVersion.isEmpty();
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

bool DbInitializer::updateDb() {
    QStringList versionsToGetChanges;
    try {
        versionsToGetChanges = getVersions();
    } catch (const char* msg) {
        qCritical() << msg;
        return false;
    }
    foreach (const QString v, versionsToGetChanges) {
        QEventLoop loop;
        reply = qnam->get(QNetworkRequest(QUrl("http://clorofilla.io:8000/changes/caponzoniere/" + v)));
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        if (reply->error()) {
            handleError();
            return false;
        }
        try {
            applyChange();
        } catch (const char* msg) {
            qCritical() << msg;
            return false;
        }
    }
    if (!versionsToGetChanges.isEmpty()) {
        return saveNewDbVersion(versionsToGetChanges.last());
    }
    return true;
}

void DbInitializer::applyChange() {
    QString change = QString::fromUtf8(reply->readAll());
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QStringList statements = change.split(";", QString::SkipEmptyParts);
    foreach (QString statement, statements) {
        if (statement.trimmed() == "") {
            continue;
        }
        if (!query.exec(statement)) {
            qDebug() << query.lastError().text();
            qDebug() << "SQLite string: " << query.lastQuery();
            throw "error applying Db change";
        }
    }
}

void DbInitializer::handleError() {
    qDebug() << "error" << reply->error();
    reply->deleteLater();
    reply = nullptr;
}

QString DbInitializer::getCurrentDbVersion() {
    QSqlDatabase m_db = QSqlDatabase::database();
    QSqlQuery query(m_db);
    if (!query.exec("SELECT id FROM db_version")) {
        throw "error retrieving current Db version";
    }
    if (query.first()) {
        return query.value(0).toString();
    }
    return "";
}

bool DbInitializer::saveNewDbVersion(QString &dbVer) {
    QSqlDatabase m_db = QSqlDatabase::database();
    QSqlQuery query(m_db);
    if (!query.exec("INSERT INTO db_version (id) VALUES ('" + dbVer + "')")) {
        qDebug() << "error saving new db version";
        return false;
    }
    return true;
}
