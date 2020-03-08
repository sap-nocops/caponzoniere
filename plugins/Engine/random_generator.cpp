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
#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>

class RandomGenerator {
	public:
		int bounded(int min, int max) {
			std::random_device rd; // obtain a random number from hardware
    		std::mt19937 eng(rd()); // seed the generator
    		std::uniform_int_distribution<> distr(min, max); // define the range
        	return distr(eng);
		}

		int bounded(int max) {
		    return bounded(0, max);
		}
};

#endif
