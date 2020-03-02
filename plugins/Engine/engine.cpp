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
#include <QThread>

Engine::Engine() : dbInitializer(new DbInitializer()) {
    dbInitializer->initDb();
}

Engine::~Engine() {
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

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
