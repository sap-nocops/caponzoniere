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
import Qt.labs.settings 1.0
import Lomiri.Components 1.3

Page {
    anchors.fill: parent

    header: PageHeader {
        id: menuHeader
        title: i18n.tr('Caponzoniere')
    }

   ColumnLayout {
        spacing: units.gu(1)
        anchors {
            margins: units.gu(1)
            top: menuHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Image {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: (parent.height > parent.width) ? (parent.width - units.gu(8)) * (1052/744) : parent.height - units.gu(16)
            Layout.preferredWidth: (parent.height > parent.width) ? (parent.width - units.gu(8)) : (parent.height - units.gu(16)) * (744/1052)
            source: "../assets/gnu_tux_capoeira.svg"
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Songs lyrics')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/Songs.qml"))
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Random Songs')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/Singers.qml"), {pageTitle: i18n.tr('Random Songs'), textType: "songs"})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Random Topics')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/Singers.qml"), {pageTitle: i18n.tr('Random Topics'), textType: "topics"})
        }
    }
}
