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
#ifndef RANDOM_SONG_STRATEGY
#define RANDOM_SONG_STRATEGY

#include "random_text_strategy.cpp"
#include "random_generator.cpp"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QStandardPaths>
#include <QList>

class RandomSongStrategy: public RandomTextStrategy {
    private:
        void initSongsStack() {
            QSqlDatabase *m_db = new QSqlDatabase();
            QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/db");
            *m_db = QSqlDatabase::addDatabase("QSQLITE");
            m_db->setDatabaseName(dbPath + "/caponzoniere_db.sqlite");
            if (!m_db->open()) {
                qDebug() << "strategy failed to connect to db";
                return;
            }
            QSqlQuery query(*m_db);
            if (!query.exec("SELECT s.title, st.duration FROM songs s JOIN song_types st ON s.type_id = st.id")) {
                qDebug() << "error retrieving song titles";
                m_db->close();
                return;
            }
            RandomGenerator randGen;
            QList<TemporaryText*> tmp;
            while (query.next()) {
                TemporaryText* tt = new TemporaryText(
                    query.value(0).toString(),
                    query.value(1).toInt() + randGen.bounded(-5, 10)
                );
                tmp.append(tt);
            }
            int i = 0;
            int random;
            while (i != tmp.length()) {
                //Think this better, it could terminate in a very long time
                do {
                    random = randGen.bounded(tmp.length());
                } while(!tmp[random]);
                this->stack.push(tmp.at(random));
                i++;
                tmp[random] = 0;
            }
            m_db->close();
            QSqlDatabase::removeDatabase(m_db->connectionName());
        }
    
    public:
        RandomSongStrategy() {
            initSongsStack();
        }

        ~RandomSongStrategy() {
        }
        
        TemporaryText* nextText() {
            if (this->stack.isEmpty()) {
                initSongsStack();
            }
            return this->stack.pop();
        }
};

#endif
