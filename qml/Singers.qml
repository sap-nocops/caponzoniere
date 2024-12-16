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
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colorNames: [i18n.tr('blue')], colors: ['#0000ff']})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Two Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colorNames: [i18n.tr('blue'), i18n.tr('red')], colors: ['#0000ff', '#ff0000']})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Three Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colorNames: [i18n.tr('blue'), i18n.tr('red'), i18n.tr('yellow')], colors: ['#0000ff', '#ff0000', '#ffff00']})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(4)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Four Singer')
            onClicked: pageStack.push(Qt.resolvedUrl("qrc:/RandomTextsPage.qml"), {pageTitle: singers.pageTitle, textType: singers.textType, colorNames: [i18n.tr('blue'), i18n.tr('red'), i18n.tr('yellow'), i18n.tr('purple')], colors: ['#0000ff', '#ff0000', '#ffff00', '#a020f0']})
        }
    }
}
