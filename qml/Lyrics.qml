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

import QtQuick 2.12
import Lomiri.Components 1.3

import Engine 1.0

Page {
    id: lyrics
    anchors.fill: parent
    property string songTitle
    property int songId

    header: PageHeader {
        id: lyricsHeader
        title: songTitle
    }

    ScrollView {
        height: parent.height - lyricsHeader.height
        width: parent.width
        clip: true
        anchors {
            top: lyricsHeader.bottom
        }
        Label {
           id: lyricsText
           color: Theme.palette.normal.foregroundText
           font.pixelSize: units.gu(4)
        }
    }

    Component.onCompleted: {
        lyricsText.text = Engine.getSongLyrics(songId);
    }
}
