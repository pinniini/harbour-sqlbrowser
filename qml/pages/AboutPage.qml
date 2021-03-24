import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: aboutPage

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    property string issuesText: qsTrId("about-issueText")
    property string generalAboutText: qsTrId("about-general")

    Component.onCompleted: {
        issueLabel.text = Theme.highlightText(issuesText, "github", Theme.highlightColor)
    }

    SilicaFlickable {
        id: aboutFlick
        anchors.fill: parent

        contentHeight: contentColumn.height

        // Place page content to a column.
        Column {
            id: contentColumn

            width: aboutPage.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTrId("about-header-page")
            }

            SectionHeader {
                text: qsTrId("about-header-info")
            }

            Label {
                id: generalAboutLabel
                text: generalAboutText
                wrapMode: Text.Wrap
                width: parent.width - Theme.paddingMedium - Theme.paddingMedium
                textFormat: Text.AutoText
                x: Theme.paddingMedium
            }

            Label {
                text: qsTrId("about-version") + " " + appVersion
                x: Theme.paddingMedium
            }

            SectionHeader {
                text: qsTrId("about-header-author")
            }

            Label {
                text: "pinniini (Joni Korhonen)"
                x: Theme.paddingMedium
                wrapMode: Text.Wrap
                width: parent.width - Theme.paddingMedium
            }

            SectionHeader {
                text: qsTrId("about-header-licence")
            }

            Label {
                text: "MIT"
                font.underline: true
                x: Theme.paddingMedium
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://opensource.org/licenses/MIT")
                }
            }

            SectionHeader {
                text: qsTrId("about-header-sourceCode")
            }

            Label {
                text: "https://github.com/pinniini/harbour-sqlbrowser"
                font.underline: true
                wrapMode: Text.Wrap
                width: parent.width - Theme.paddingMedium
                x: Theme.paddingMedium
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://github.com/pinniini/harbour-sqlbrowser")
                }
            }

            SectionHeader {
                text: qsTrId("about-header-issues")
            }

            Label {
                id: issueLabel
                textFormat: Text.AutoText
                wrapMode: Text.Wrap
                width: parent.width - Theme.paddingMedium - Theme.paddingMedium
                x: Theme.paddingMedium

                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://github.com/pinniini/harbour-tekstitv/issues")
                }
            }
        }
    }
}
