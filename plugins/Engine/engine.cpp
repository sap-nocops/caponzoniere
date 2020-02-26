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
#include "random_song_strategy.cpp"

#include <QDebug>
#include <QFile>
#include <QtSql>
#include <QThread>
#include <QStandardPaths>

Engine::Engine() : m_db(new QSqlDatabase()) {
    //TODO move this logic in a dedicated class    
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

void Engine::playRandomTexts(QString textType) {
    //TODO check for memory leaks
    QThread* thread = new QThread;
    this->worker = new Worker();
    this->worker->moveToThread(thread);
    if (textType == "songs") {
        this->worker->setStrategy(new RandomSongStrategy());
    } else {
        //TODO random topic strategy
    }
    connect(thread, SIGNAL (started()), this->worker, SLOT (process()));
    connect(this->worker, SIGNAL (randomTextChanged(QString)), this, SIGNAL (randomTextChanged(QString)));
    connect(this, SIGNAL (randomTextsFinished()), thread, SLOT (quit()));
    connect(this, SIGNAL (randomTextsFinished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void Engine::stopRandomTexts() {
    this->worker->stop();
    Q_EMIT randomTextsFinished();
}

QStringList Engine::getTopics() {
    QStringList topics;
    QSqlQuery query(*m_db);
    if (!query.exec("SELECT name FROM topics")) {
        qDebug() << "error retrieving topics";
        return topics;
    }
    int i = 0;
    while (query.next()) {
        topics.append(query.value(i).toString());
    }
    return topics;
}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}

bool Engine::createDbFolderIfNotExists(QString dbPath) {
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