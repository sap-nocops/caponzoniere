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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtCore/QMutex>
#include "model/song_model.h"
#include "model/song.h"
#include "model/songfilterproxymodel.h"
#include "db/db_initializer.h"

#define foreach Q_FOREACH

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

int main(int argc, char *argv[]) {
    qDebug() << "Starting app from main.cpp";
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("caponzoniere.sap");

    QQuickStyle::setStyle("Suru");

    QMutex mutex;
    DbInitializer dbInit;
    dbInit.setOutMutex(&mutex);
    dbInit.initDb();
    mutex.lock();

    SongModel songModel;
    QSqlQuery query;
    if (!query.exec("SELECT id, title FROM songs ORDER BY title")) {
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
    SongFilterProxyModel filterModel;
    filterModel.setSourceModel(&songModel);
    filterModel.setFilterRole(SongModel::SongRoles::Title);
    filterModel.setSortRole(SongModel::SongRoles::Title);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "engine rootObjects is empty";
        return -1;
    }
    engine.rootContext()->setContextProperty("songFilter", &filterModel);
    return QGuiApplication::exec();
}
