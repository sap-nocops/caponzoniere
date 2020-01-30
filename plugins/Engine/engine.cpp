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
#include "engine.h"

#include <QDebug>
#include <QFile>
#include <QtSql>

static int getCountResult(void *data, int argc, char **argv, char **azColName){
   qDebug() << "Count: " << argv[0];
   return 0;
}

Engine::Engine() : m_db(new QSqlDatabase()) {
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName("caponzoniere.db");
    if (!m_db->open()) {
        qDebug() << "failed to connect to db";
        return;
    }
    qDebug() << "connected";
    initDb();
}

Engine::~Engine() {
}

void Engine::initDb() {
    QSqlQuery query(*m_db);
    if (query.exec("SELECT COUNT(*) FROM songs")) {
        qDebug() << "database already initialized";
        return;
    }

    QFile file("initDb.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file: " << file.fileName();
        return;
    }

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

        //QSqlQuery query(*m_db);
        if (!query.exec(statement)) {
            qDebug() << "Error executing database file: " << file.fileName();
            qDebug() << query.lastError().text();
            qDebug() << "SQLite string: " << query.lastQuery();
        }
    }
}

void Engine::playRandomSongs() {
    QSqlQuery query(*m_db);
    if (!query.exec("SELECT COUNT(*) FROM songs")) {
        qDebug() << "nullaaaaa";
    }
    if (query.next()) {
        qDebug() << query.value(0).toString();
    }
}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
