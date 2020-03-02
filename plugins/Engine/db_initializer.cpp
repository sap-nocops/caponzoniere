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
#include "db_initializer.h"

#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>

void DbInitializer::initDb() {
    QSqlDatabase *m_db = new QSqlDatabase();
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/db");
    if (!this->createDbFolderIfNotExists(dbPath)) {
        return;
    }
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName(dbPath + "/caponzoniere_db.sqlite");
    if (!m_db->open()) {
        qDebug() << "failed to connect to db";
        return;
    }

    QSqlQuery query(*m_db);
    if (query.exec("SELECT COUNT(*) FROM songs")) {
        qDebug() << "database already initialized";
        m_db->close();
        QSqlDatabase::removeDatabase(m_db->connectionName());
        return;
    }

    QFile file("assets/initDb.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file: " << file.fileName();
        m_db->close();
        QSqlDatabase::removeDatabase(m_db->connectionName());
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
    m_db->close();
    QSqlDatabase::removeDatabase(m_db->connectionName());
}

bool DbInitializer::createDbFolderIfNotExists(QString dbPath) {
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
