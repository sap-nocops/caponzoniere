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
    property var colors
    
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
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width - units.gu(1)
            font.pixelSize: units.gu(3)
            //TODO i18n
            text: "Colors: " + colors
            color:  Theme.palette.normal.foregroundText
            wrapMode: Text.Wrap
        }

        Text {
            id: banner
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width - units.gu(1)
            font.pixelSize: units.gu(6)
            //TODO i18n
            text: "Choose one color each singer and sing when the text is of your color"
            color:  Theme.palette.normal.foregroundText
            wrapMode: Text.Wrap
        }
        
        Text {
            id: randomTextDisplay
            visible: false
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width - units.gu(1)
            font.pixelSize: units.gu(8)
            color:  Theme.palette.normal.foregroundText
            wrapMode: Text.Wrap
        }
    }

    Connections {
        target: Engine
        onRandomTextChanged: {
            randomTextDisplay.text = randomText
            randomTextDisplay.color = pickRandomColor(randomTextDisplay.color)
        }
    }

    Component.onCompleted: {
        
    }

    Component.onDestruction: {
        Engine.stopRandomTexts();
        pageStack.pop();
    }

    Timer {
        id: bannerTimer
        interval: 5000;
        running: true;
        repeat: false
        onTriggered: {
            banner.visible = false;
            randomTextDisplay.visible = true;
            countDownTimer.start();
        }
    }

    Timer {
        id: countDownTimer
        interval: 1000;
        repeat: true
        property int countDown: 5
        triggeredOnStart: true
        onTriggered: {
            if (countDown == 0) {
                countDownTimer.stop();
                startRandomTexts();
            }
            randomTextDisplay.text = countDown;
            countDown--;
        }
    }

    function startRandomTexts() {
        Engine.playRandomTexts(textType);
    } 

    function pickRandomColor(currentColor) {
        if (colors.length == 1) {
            return colors[0];
        }
        var randomColor;
        var random;
        do {
            random = Math.floor(Math.random() * colors.length);
            randomColor = colors[random];
        } while (randomColor == currentColor);
        return randomColor;
    }
}
