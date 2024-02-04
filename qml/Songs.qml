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
import QtQuick.Layouts 1.3
import Lomiri.Components 1.3

Page {
    id: songs
    anchors.fill: parent

    header: PageHeader {
        id: songsHeader
        title: i18n.tr('Songs')
    }

    ColumnLayout {
        spacing: 3

        anchors {
            margins: units.gu(1)
            top: songsHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        TextField {
            id: searchSongTextInput
            Layout.preferredWidth: parent.width
            onAccepted: {
                songFilter.setFilterString(text)
            }

            placeholderText: i18n.tr('Search...')
        }

        ListView {
            Layout.preferredHeight: parent.height - searchSongTextInput.height - units.gu(3)
            Layout.preferredWidth: parent.width
            model: songFilter
            delegate: Item {
                height: units.gu(3)
                width: parent.width
                Text {
                    text: title
                    font.pixelSize: units.gu(3)
                    color: Theme.palette.normal.foregroundText
                    wrapMode: Text.Wrap
                }

                MouseArea {
                    height: parent.height
                    width: parent.width
                    onClicked: pageStack.push(Qt.resolvedUrl("Lyrics.qml"), {songTitle: title, songId: id})
                }
            }
        }
    }
}
