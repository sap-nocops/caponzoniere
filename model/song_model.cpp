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
#include "song_model.h"

SongModel::SongModel(QObject *parent)
        : QAbstractListModel(parent)
{
}

void SongModel::addSong(const Song &song)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

int SongModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_songs.count();
}

QVariant SongModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_songs.count()){
        return QVariant();
    }

    const Song &song = m_songs[index.row()];
    if (role == Id) {
        return song.id();
    } else if (role == Title) {
        return song.title();
    }
    return QVariant();
}

QHash<int, QByteArray> SongModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Title] = "title";
    return roles;
}
