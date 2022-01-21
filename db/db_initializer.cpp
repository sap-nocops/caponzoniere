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
#include "app_db_version.h"

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

    if (QSqlDatabase::database().tables().contains(QStringLiteral("current_app_db_version"))) {
        qDebug() << "db already initialized";
        return updateDb();
    }

    QSqlQuery query(db);
    QString sql = "CREATE TABLE IF NOT EXISTS current_app_db_version(db_version CHAR(10), app_version);";
    if (!query.exec(sql)) {
        qDebug() << "Error executing db_version creation";
        qDebug() << query.lastError().text();
        return false;
    }
    return updateDb();
}

QJsonArray DbInitializer::listDbVersions(QString appVersion) {
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

QStringList DbInitializer::getVersions(AppDbVersion currentDbVersion, QString appVersion) {
    bool newDbVer = currentDbVersion.getDbVersion().isEmpty();
    QJsonArray dbVersions;
    try {
        dbVersions = listDbVersions(appVersion);
    } catch (const char* msg) {
        if (newDbVer || currentDbVersion.getAppVersion() != appVersion) {
            throw msg;
        } else {
            qDebug() << msg;
        }
    }
    QStringList versionsToGetChanges;
    foreach (const QJsonValue & v, dbVersions) {
        if (currentDbVersion.getDbVersion() == v.toString()) {
            newDbVer = true;
            continue;
        }
        if (newDbVer) {
            versionsToGetChanges.append(v.toString());
        }
    }
    return versionsToGetChanges;
}

bool DbInitializer::updateDb() {
    QString appVersion = "1.0.0";
    AppDbVersion currentDbVersion = getCurrentAppDbVersion();
    QStringList versionsToGetChanges;
    try {
        versionsToGetChanges = getVersions(currentDbVersion, appVersion);
    } catch (const char* msg) {
        qCritical() << msg;
        return false;
    }
    for (int i = 0; i < versionsToGetChanges.size(); i++) {
        const QString v = versionsToGetChanges.at(i);
        QEventLoop loop;
        reply = qnam->get(QNetworkRequest(QUrl("http://clorofilla.io:8000/changes/caponzoniere/" + v)));
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        if (reply->error()) {
            handleError();
            if (appVersion == currentDbVersion.getAppVersion()) {
                return saveNewDbVersion(const_cast<QString &>(versionsToGetChanges.at(i - 1)), appVersion);
            }
            qCritical() << "THIS IS REALLY BAD";
            qCritical() << "IT IS BETTER TO WIPE DB FOLDER AND RESTART THE APP";
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
        return saveNewDbVersion(versionsToGetChanges.last(), appVersion);
    }
    return true;
}

void DbInitializer::applyChange() {
    QString change = QString::fromUtf8(reply->readAll());
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) {
        throw "error cannot open transaction";
    }
    QSqlQuery query(db);
    QStringList statements = change.split(";", QString::SkipEmptyParts);
    foreach (QString statement, statements) {
        if (statement.trimmed() == "") {
            continue;
        }
        if (!query.exec(statement)) {
            qDebug() << query.lastError().text();
            qDebug() << "SQLite string: " << query.lastQuery();
            if (!db.rollback()) {
                throw "error applying Db change, could not rollback";
            }
            throw "error applying Db change";
        }
    }
    if (!db.commit()) {
        throw "error cannot commit";
    }
}

void DbInitializer::handleError() {
    qDebug() << "error" << reply->error();
    reply->deleteLater();
    reply = nullptr;
}

AppDbVersion DbInitializer::getCurrentAppDbVersion() {
    QSqlDatabase m_db = QSqlDatabase::database();
    QSqlQuery query(m_db);
    if (!query.exec("SELECT app_version, db_version FROM current_app_db_version")) {
        throw "error retrieving current Db version";
    }
    ;
    if (query.first()) {
        return AppDbVersion(query.value(0).toString(), query.value(1).toString());
    }
    return AppDbVersion("", "");
}

bool DbInitializer::saveNewDbVersion(QString &dbVer, QString &appVer) {
    QSqlDatabase m_db = QSqlDatabase::database();
    QSqlQuery query(m_db);
    if (!query.exec("INSERT INTO current_app_db_version (db_version, app_version) VALUES ('" + dbVer + "', '" + appVer + "')")) {
        qCritical() << "error saving new app db version";
        qCritical() << "THIS IS REALLY BAD";
        qCritical() << "IT IS BETTER TO WIPE DB FOLDER AND RESTART THE APP";
        return false;
    }
    return true;
}
