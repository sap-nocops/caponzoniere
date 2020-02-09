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
#include "runner.h"

#include <QDebug>

#include <chrono>
#include <thread>

void Runner::provideTitle(QStringList titles) {
    qDebug() << "provideTitle";
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        //emit songChanged("aiaiaiaiai");
        qDebug() << "song change emitted";
    }
}

void Runner::setRunning(bool running) {
    this->running = running;
}
