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

#include <chrono>
#include <thread>

Engine::Engine() : m_db(new QSqlDatabase()) {
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName("caponzoniere.db");
    if (!m_db->open()) {
        qDebug() << "failed to connect to db";
        return;
    }
    qDebug() << "connected";
    initDb();
    this->runner = new Runner();
}

Engine::~Engine() {
}

void Engine::initDb() {
    QSqlQuery query(*m_db);
    if (query.exec("SELECT COUNT(*) FROM songs")) {
        qDebug() << "database already initialized";
        return;
    }

    QFile file("assets/initDb.sql");
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

        if (!query.exec(statement)) {
            qDebug() << "Error executing database file: " << file.fileName();
            qDebug() << query.lastError().text();
            qDebug() << "SQLite string: " << query.lastQuery();
        }
    }
}

void Engine::playRandomSongs() {
    QSqlQuery query(*m_db);
    if (!query.exec("SELECT title FROM songs")) {
        qDebug() << "error retrieving song titles";
        return;
    }
    QStringList titles;
    int i = 0;
    while (query.next()) {
        titles.append(query.value(i).toString());
    }
    this->runner->setRunning(true);
    std::thread titleProvider(&Runner::provideTitle, this->runner, titles);
}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
