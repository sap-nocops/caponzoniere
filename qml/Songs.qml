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
        spacing: 1
        anchors {
            margins: units.gu(1)
            top: songsHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Rectangle {
            id: searchSong
            Layout.preferredHeight: units.gu(5)
            Layout.preferredWidth: parent.width
            border.width: 1
            border.color: UbuntuColors.green
            color: Theme.palette.normal.background
            radius: 5
            focus: true

            TextInput {
                id: searchSongTextInput
                height: parent.height
                width: parent.width
                //validator: RegularExpressionValidator { regularExpression: /[a-z]+/ }
                font.pixelSize: units.gu(3)
                color: UbuntuColors.red
                Keys.onPressed: songFilter.setFilterString(text);

                property string placeholderText: i18n.tr('Search...')

                Text {
                    text: searchSongTextInput.placeholderText
                    color: "#aaa"
                    visible: !searchSongTextInput.text
                    font.pixelSize: units.gu(3)
                }
            }
       }

        ListView {
            Layout.preferredHeight: parent.height - searchSongTextInput.height
            Layout.preferredWidth: parent.width
            model: songFilter
            delegate: Item {
                height: units.gu(3)
                width: parent.width
                Text {
                    text: title
                    font.pixelSize: units.gu(3)
                    color: Theme.palette.normal.foregroundText
                }

                MouseArea {
                    height: parent.height
                    width: parent.width
                    onClicked: pageStack.push(Qt.resolvedUrl("Lyrics.qml"), {songTitle: title, songId: id})
                }
            }
        }
    }

    Component.onCompleted: {
        searchSongTextInput.forceActiveFocus();
    }
}
