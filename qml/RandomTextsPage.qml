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

import QtQuick 2.7
import Ubuntu.Components 1.3
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

import Engine 1.0

Page {
    id: randomTextPage
    anchors.fill: parent
    property string pageTitle
    property string textType
    
    header: PageHeader {
        id: header
        title: randomTextPage.pageTitle
    }

    ColumnLayout {
        spacing: units.gu(2)
        anchors {
            margins: units.gu(2)
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Text {
            id: randomTextDisplay
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: units.gu(8)
            color:  Theme.palette.normal.foregroundText
        }
    }

    Connections {
        target: Engine
        onRandomTextChanged: {
            randomTextDisplay.text = randomText
        }
    }

    Component.onCompleted: {
        Engine.playRandomTexts(textType)
    }

    Component.onDestruction: {
        Engine.stopRandomTexts()
    }
}
