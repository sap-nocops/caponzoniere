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

#ifndef RANDOM_TEXT_STRATEGY
#define RANDOM_TEXT_STRATEGY

#include "temporary_text.cpp"
#include "random_generator.cpp"

#include <QStack>
#include <QtSql/QSqlQuery>
#include <QDebug>

class RandomTextStrategy {
    public:
        virtual TemporaryText* nextText() {
            if (this->stack.isEmpty()) {
                initStack();
            }
            return this->stack.pop();
        };
        virtual ~RandomTextStrategy() {
            qDebug() << "destroying RandomTextStrategy";
            this->stack.clear();
        }
    protected:
        QStack<TemporaryText*> stack;
        virtual QList<TemporaryText*> getTemporaryTexts(QSqlQuery* query) = 0;
    	virtual void initStack() {
            QSqlDatabase m_db = QSqlDatabase::database();
            QSqlQuery query(m_db);
            QList<TemporaryText*> tmp = shuffleList(getTemporaryTexts(&query));
            for (int i = 0;i < tmp.length();i++) {
                this->stack.push(tmp.at(i));
            }
        }
    private:
        virtual QList<TemporaryText*> shuffleList(QList<TemporaryText*> tmp) {
            RandomGenerator randGen;
            int random;
            for (int i = 0;i < tmp.length();i++) {
                do {
                    random = randGen.bounded(tmp.length());
                } while(random == i);
                tmp.move(i, random);
            }
            return tmp;
        }
};

#endif