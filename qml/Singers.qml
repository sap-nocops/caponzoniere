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
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
//import Ergo 0.0
import Ubuntu.Components 1.3

Page {
    id: singers
    anchors.fill: parent
    property string pageTitle
    property string textType

    header: PageHeader {
        id: menuHeader
        title: i18n.tr('Choose Singers')
    }

    ColumnLayout {
        spacing: units.gu(1)
        anchors {
            margins: units.gu(1)
            top: menuHeader.bottom
            left: parent.left
            right: parent.right
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('One Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colors: ["blue"]})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Two Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colors: ["blue", "red"]})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Three Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colors: ["blue", "red", "yellow"]})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Four Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colors: ["blue", "red", "yellow", "purple"]})
        }
    }
}
