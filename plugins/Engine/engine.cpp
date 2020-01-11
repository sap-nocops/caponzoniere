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

#include <QDebug>

#include "engine.h"
#include <sqlite3.h> 

static int getCountResult(void *data, int argc, char **argv, char **azColName){
   qDebug() << "Count: " << argv[0];
   return 0;
}

Engine::Engine() {
	int error = sqlite3_open("caponzoniere.db", &db);
	if (error) {
	   throw sqlite3_errmsg(db);
	}
}

Engine::~Engine() {
	sqlite3_close(db);
}

void Engine::initDb() {
	char *zErrMsg = 0;
	const char *sqlCreateSongsTable = "CREATE TABLE IF NOT EXISTS songs("  \
    	"id            INTEGER 	 PRIMARY KEY    AUTOINCREMENT," \
    	"title         CHAR(10)			 NOT NULL," \
    	"type_id    INT 				 NOT NULL," \
    	"lyrics       CHAR(300);";
    const char *sqlCreateSongTypeTable = "CREATE TABLE IF NOT EXISTS songs("  \
    	"id            INTEGER 	 PRIMARY KEY," \
    	"name       CHAR(10)	 NOT NULL," \
    	"duration  INT 				 NOT NULL;";
    const char *sqlCheckIfAlreadyInit = "SELECT COUNT(*) FROM songs;";
    const char *sqlInsert = "INSERT INTO songs (title, type_id, lyrics) "  \
         "VALUES ('Dona Maria do camboatà', 1, 'Dona Maria do camboatà ela chega na venda e comenca a gingar'); " \
         "INSERT INTO songs (title, type_id, lyrics) "  \
         "VALUES ('Camungere', 1, 'Camungere come vai como ta camungere como vai voce camungere como vai de saude camungere para mi è un prazer'); "     \
         "INSERT INTO songs (title, type_id, lyrics) "  \
         "VALUES ('Dona Alice', 1, 'Dona Alice nao me pegue nao, nao me aggarra nao me pegue nao, Dona Alice nao me pegue nao, nao me pegue nao me pegue nao me pegue nao');" \
         "INSERT INTO songs (title, type_id, lyrics) "  \
         "VALUES ('Marinhero sò', 1, 'Eu nao sou da qui, Marinhero sò, eu nao tenho amor, Marinhero sò, eu so da bahia, Marinhero sò, de San Salvador ');";

    int res = sqlite3_exec(db, sqlCreateSongTypeTable, nullptr, 0, &zErrMsg);
    if (res != SQLITE_OK) {
    	qDebug() <<  zErrMsg;
    	sqlite3_free(zErrMsg);
    	throw "can't create song_type table";
    }

    res = sqlite3_exec(db, sqlCreateSongsTable, nullptr, 0, &zErrMsg);
    if (res != SQLITE_OK) {
    	qDebug() <<  zErrMsg;
    	sqlite3_free(zErrMsg);
    	throw "can't create songs table";
    }

    res = sqlite3_exec(db, sqlCheckIfAlreadyInit, getCountResult, 0, &zErrMsg);
}

void Engine::playRandomSongs() {

}

void Engine::listSongs() {

}

void Engine::getSongLyrics() {

}
