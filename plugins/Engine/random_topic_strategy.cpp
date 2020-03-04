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
#include "random_generator.cpp"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QList>

class RandomTopicStrategy: public RandomTextStrategy {
    private:
        void initTopicsStack() {
            QSqlDatabase m_db = QSqlDatabase::database();
            QSqlQuery query(m_db);
            if (!query.exec("SELECT name FROM topics")) {
                qDebug() << "error retrieving topics";
                return;
            }
            RandomGenerator randGen;
            QList<TemporaryText*> tmp;
            while (query.next()) {
                TemporaryText* tt = new TemporaryText(
                    query.value(0).toString(),
                    randGen.bounded(75, 100)
                );
                tmp.append(tt);
            }
            qDebug() << "YESSSS";
            int random;
            for (int i = 0;i < tmp.length();i++) {
                do {
                    random = randGen.bounded(tmp.length());
                } while(random == i);
                tmp.move(i, random);
            }
            for (int i = 0;i < tmp.length();i++) {
                this->stack.push(tmp.at(i));
            }
        }
    
    public:
        RandomTopicStrategy() {
            initTopicsStack();
        }

        ~RandomTopicStrategy() {
        }
        
        TemporaryText* nextText() {
            if (this->stack.isEmpty()) {
                initTopicsStack();
            }
            TemporaryText* toRet = this->stack.pop();
            qDebug() << "juice";
            return toRet;
        }
};

#endif
