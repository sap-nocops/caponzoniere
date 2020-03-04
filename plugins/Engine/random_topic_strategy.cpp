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
#ifndef RANDOM_TOPIC_STRATEGY
#define RANDOM_TOPIC_STRATEGY

#include "random_text_strategy.cpp"

#include <QDebug>

class RandomTopicStrategy: public RandomTextStrategy {
    protected:
        QList<TemporaryText*> getTemporaryTexts(QSqlQuery query) {
            QList<TemporaryText*> tmp;
            if (!query.exec("SELECT name FROM topics")) {
                qDebug() << "error retrieving topics";
                return tmp;
            }
            RandomGenerator randGen;
            while (query.next()) {
                TemporaryText* tt = new TemporaryText(
                    query.value(0).toString(),
                    randGen.bounded(75, 100)
                );
                tmp.append(tt);
            }
            return tmp;
        }
        
    
    public:
        RandomTopicStrategy() {
            initStack();
        }
};

#endif
