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
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.3
import Lomiri.Components 1.3

MainView {
    id: root
    objectName: 'mainView'
    applicationName: 'caponzoniere.sap'
    automaticOrientation: true
    width: Suru.units.gu(45)
    height: Suru.units.gu(75)

    Page{
        anchors.fill: parent

        header: PageHeader {
            id: errorHeader
            title: i18n.tr('Error')
        }

        ColumnLayout {
            spacing: units.gu(2)
            anchors {
                margins: units.gu(2)
                top: errorHeader.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            Text {
                id: banner
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width - units.gu(1)
                font.pixelSize: units.gu(6)
                horizontalAlignment: Text.AlignHCenter
                text: i18n.tr('Cannot initialize the app. Please check your internet connection')
                color:  Theme.palette.normal.foregroundText
                wrapMode: Text.Wrap
            }
        }
    }
}
