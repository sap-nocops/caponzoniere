
import QtQuick 2.7
import Ubuntu.Components 1.3
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

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
            Layout.preferredHeight: (parent.height > parent.width) ? (parent.width - units.gu(4)) * (1052/744) : parent.height - units.gu(16)
            Layout.preferredWidth: (parent.height > parent.width) ? (parent.width - units.gu(4)) : (parent.height - units.gu(16)) * (744/1052)
            source: "../assets/gnu_tux_capoeira.svg"
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(1)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Random Songs')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: i18n.tr('Random Songs'), textType: "songs"})
        }

        Button {
            Layout.preferredWidth: parent.width - units.gu(1)
            Layout.alignment: Qt.AlignHCenter
            text: i18n.tr('Random Topics')
            onClicked: pageStack.push(Qt.resolvedUrl("RandomTextsPage.qml"), {pageTitle: i18n.tr('Random Topics'), textType: "topics"})
        }
    }
}
