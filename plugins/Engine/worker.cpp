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
#include "worker.h"
#include "temporary_text.cpp"

#include <QDebug>

#include <chrono>
#include <thread>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

Worker::Worker() {
}

Worker::~Worker() {
    qDebug() << "destroying worker";
    this->running = false;
    delete this->strategy;
}

void Worker::process() {
    this->running = true;
    while (this->running) {
        TemporaryText* tt = this->strategy->nextText();
        Q_EMIT randomTextChanged(tt->getText());
        milliseconds start = std::chrono::duration_cast<milliseconds>(
            Clock::now().time_since_epoch()
        );
        milliseconds now;
        milliseconds diff;
        do {
            std::this_thread::sleep_for(milliseconds(300));
            now = std::chrono::duration_cast<milliseconds>(Clock::now().time_since_epoch());
            diff = std::chrono::duration_cast<milliseconds>(now - start);
        } while (running && (diff.count() < tt->getDuration() * 1000));
    }
    qDebug() << "FINISHED";
    Q_EMIT finished();
}

void Worker::stop() {
    qDebug() << "STOPPED";
    this->running = false;
}

void Worker::setStrategy(RandomTextStrategy* strategy) {
    this->strategy = strategy;
}
