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
import Lomiri.Components 1.3
import QtQuick.Window 2.2
import Qt.labs.settings 1.0
import QtSystemInfo 5.0

MainView {
    id: root
    objectName: 'mainView'
    applicationName: "caponzoniere.sap"
    automaticOrientation: true
    width: Suru.units.gu(45)
    height: Suru.units.gu(75)
    visible: true

    PageStack {
        id: pageStack
        anchors.fill: parent
    }

    Component.onCompleted: {
        pageStack.push(Qt.resolvedUrl("qrc:/Menu.qml"), {})
    }

    ScreenSaver {
        id: screen_saver
        screenSaverEnabled: Qt.application.state !== Qt.ApplicationActive
    }
}
