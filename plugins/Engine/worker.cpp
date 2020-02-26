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

Worker::Worker() {
	this->running = true;
}

Worker::~Worker() {
}

void Worker::process() {
	for (int i = 10;i >0 && this->running;i--) {
		Q_EMIT randomTextChanged(QString::number(i));
        qDebug() << "count down emitted";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
    while (this->running) {
        TemporaryText* tt = this->strategy->nextText();
        Q_EMIT randomTextChanged(tt->getText());
        std::this_thread::sleep_for(std::chrono::seconds(tt->getDuration()));
        qDebug() << "text change emitted";
    }
}

void Worker::stop() {
    qDebug() << "STOPPED";
    this->running = false;
}

void Worker::setStrategy(RandomTextStrategy* strategy) {
    this->strategy = strategy;
}
