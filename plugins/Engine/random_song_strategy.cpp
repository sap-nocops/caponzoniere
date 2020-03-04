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

#include <QDebug>

class RandomSongStrategy: public RandomTextStrategy {    
    public:
        RandomSongStrategy() {
            initStack();
        }
    protected:
        QList<TemporaryText*> getTemporaryTexts(QSqlQuery query) {
            QList<TemporaryText*> tmp;
            if (!query.exec("SELECT s.title, st.duration FROM songs s JOIN song_types st ON s.type_id = st.id")) {
                qDebug() << "error retrieving song titles";
                return tmp;
            }
            RandomGenerator randGen;
            while (query.next()) {
                TemporaryText* tt = new TemporaryText(
                    query.value(0).toString(),
                    query.value(1).toInt() + randGen.bounded(-5, 10)
                );
                tmp.append(tt);
            }
            return tmp;
        }
};

#endif
