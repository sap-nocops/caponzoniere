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

import QtQuick 2.9
import Ubuntu.Components 1.3

Page {
    id: songs
    anchors.fill: parent

    header: PageHeader {
        id: songsHeader
        title: i18n.tr('Songs')
    }

    ListView {
        width: parent.width; height: parent.height - songsHeader.height

        model: songModel
        delegate: Item {
            height: units.gu(5)
            width: parent.width
            Text {
                text: title
                font.pixelSize: units.gu(5)
            }

            MouseArea {
                height: parent.height
                width: parent.width
                onClicked: pageStack.push(Qt.resolvedUrl("Lyrics.qml"), {songTitle: title, songId: id})
            }
        }
    }
}
