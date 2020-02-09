
import QtQuick 2.7
import Ubuntu.Components 1.3
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Page {
    anchors.fill: parent

    header: PageHeader {
        id: header
        title: i18n.tr('Caponzoniere')
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

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Random Corridos')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomSongsPage.qml"), {})
        }
    }
}