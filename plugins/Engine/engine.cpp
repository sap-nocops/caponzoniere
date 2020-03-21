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
#include "random_topic_strategy.cpp"
#include "db_initializer.h"

#include <QDebug>
#include <QThreadPool>

Engine::Engine() {
    DbInitializer dbInitializer;
    dbInitializer.initDb();
}

Engine::~Engine() {
    qDebug() << "destroying engine";
    if (worker) {
        worker->stop();
    }
}

void Engine::playRandomTexts(QString textType) {
    if (textType == "songs") {
        worker = new Worker(new RandomSongStrategy());
    } else {
        worker = new Worker(new RandomTopicStrategy());
    }
    connect(worker, SIGNAL (randomTextChanged(QString)), this, SIGNAL (randomTextChanged(QString)));

    QThreadPool::globalInstance()->start(worker);
}

void Engine::stopRandomTexts() {
    qDebug() << "stopping worker";
    worker->stop();
}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
