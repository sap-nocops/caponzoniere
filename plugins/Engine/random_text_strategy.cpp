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

#include <QStack>

class RandomTextStrategy {
    public:
    	virtual ~RandomTextStrategy() {};
        virtual TemporaryText* nextText() {};
    protected:
        QStack<TemporaryText*> stack;
};

#endif