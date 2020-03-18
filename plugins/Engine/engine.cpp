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
#include "worker.h"

#include <QDebug>
#include <QThread>

Engine::Engine() {
    DbInitializer dbInitializer;
    dbInitializer.initDb();
}

Engine::~Engine() {
    qDebug() << "destroyng engine";
    Q_EMIT stopWorker();
}

void Engine::playRandomTexts(QString textType) {
    QThread* thread = new QThread;
    Worker* worker = new Worker();
    worker->moveToThread(thread);
    if (textType == "songs") {
        worker->setStrategy(new RandomSongStrategy());
    } else {
        worker->setStrategy(new RandomTopicStrategy());
    }
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(this, SIGNAL (stopWorker()), worker, SLOT (stop()));
    connect(worker, SIGNAL (randomTextChanged(QString)), this, SIGNAL (randomTextChanged(QString)));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

    thread->start();
}

void Engine::stopRandomTexts() {
    Q_EMIT stopWorker();
}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
