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

#include <QGuiApplication>
#include <QUrl>
#include <QString>
#include <QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore/QDir>
#include <QtSql/QSqlDatabase>
#include <QtCore/QStandardPaths>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtQuickControls2/QQuickStyle>
#include <QQmlContext>
#include "model/song_model.h"
#include "model/song.h"

bool createDbFolderIfNotExists(const QString &dbPath) {
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

bool initDb() {
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

    if (QSqlDatabase::database().tables().contains(QStringLiteral("songs"))) {
        qDebug() << "db already initialized";
        return true;
    }

    QFile file("assets/initDb.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file: " << file.fileName();
        return false;
    }

    QSqlQuery query(db);
    QString sql;
    QTextStream in(&file);
    while (!in.atEnd()) {
        sql += in.readLine() + "\n";
    }
    file.close();

    QStringList statements = sql.split(";", QString::SkipEmptyParts);
            foreach (QString statement, statements) {
            if (statement.trimmed() == "") {
                continue;
            }

            if (!query.exec(statement)) {
                qDebug() << "Error executing database file: " << file.fileName();
                qDebug() << query.lastError().text();
                qDebug() << "SQLite string: " << query.lastQuery();
            }
        }
    statements.clear();
    return true;
}

int main(int argc, char *argv[]) {
    qDebug() << "Starting app from main.cpp";
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("caponzoniere.sap");

    QQuickStyle::setStyle("Suru");

    if (!initDb()) {
        qCritical() << "cannot init db";
        return -1;
    }

    SongModel songModel;
    QSqlQuery query;
    if (!query.exec("SELECT id, title FROM songs")) {
        qCritical() << "cannot load songs";
        return -1;
    }
    while (query.next()) {
        songModel.addSong(
                Song(
                        query.value(0).toInt(),
                        query.value(1).toString()
                )
        );
    };

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "engine rootObjects is empty";
        return -1;
    }
    engine.rootContext()->setContextProperty("songModel", &songModel);
    return QGuiApplication::exec();
}
