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
#ifndef CAPONZONIERE_SONG_MODEL_H
#define CAPONZONIERE_SONG_MODEL_H

#include <QtCore/QAbstractListModel>
#include "song.h"

class SongModel : public QAbstractListModel
{
Q_OBJECT
public:
    enum SongRoles {
        Id = Qt::UserRole + 1,
        Title
    };

    SongModel(QObject *parent = 0);

    void addSong(const Song &song);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Song> m_songs;
};

#endif
