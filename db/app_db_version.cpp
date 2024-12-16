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
#include "app_db_version.h"

AppDbVersion::AppDbVersion(QString appVer, QString dbVer) {
    this->appVer = appVer;
    this->dbVer = dbVer;
}

QString AppDbVersion::getAppVersion() {
    return this->appVer;
}

QString AppDbVersion::getDbVersion() {
    return this->dbVer;
}
