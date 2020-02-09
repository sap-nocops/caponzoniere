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

#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QtSql/QSqlQuery>

#include "worker.h"

class Engine: public QObject {
    Q_OBJECT

signals:
	void songChanged(QString title);
	void randomSongsFinished();

public:
    Engine();
    ~Engine();

    Q_INVOKABLE void playRandomSongs();
    Q_INVOKABLE void listSongs();
    Q_INVOKABLE void getSongLyrics();

private:
	QSqlDatabase *m_db;
	Worker *worker;

	void initDb();
    QStringList getSongTitles();
    void stopRandomSongs();
};

#endif
