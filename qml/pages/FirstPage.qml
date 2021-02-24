import QtQuick 2.2
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: page

    property string dbFile
    property int currentConnectionType: Type.Details
    property Connector currentConnector

    Component.onCompleted: {
        if (SQLConnectors) {
            console.log("Connectors exists:", SQLConnectors.length)
            connectorModel.clear()
            var count = SQLConnectors.length;
            for (var i = 0; i < count; ++i) {
                var connector = SQLConnectors[i]
                console.log(connector, connector.name, connector.type)
                connectorModel.append({ "name": connector.name, "type": connector.type })
            }
        }
    }

    Connections {
        target: TranslationHandler
        onTranslateUI: {
            translateUi()
        }
    }

    ListModel {
        id: connectorModel
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                id: menuAbout
                text: qsTrId("label-about")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                id: menuSettings
                text: qsTrId("label-settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                id: pageHeader
                title: qsTrId("main-header")
            }

            ComboBox {
                id: connectorCombo
                width: parent.width - Theme.paddingMedium
                label: qsTrId("label-connector")

                menu: ContextMenu {
                    Repeater {
                        id: connectorRepeater
                        model: connectorModel
                        MenuItem { text: name }
                    }
                }

                onCurrentItemChanged: {
                    console.log("Selected connector changed...")
                    currentConnector = SQLConnectors[currentIndex]
                    currentConnectionType = currentConnector.type
                }
            }

            ValueButton {
                id: fileButton
                width: parent.width
                label: qsTrId("label-dbFile")
                value: dbFile ? dbFile : qsTrId("label-noDbSelected")
                visible: currentConnectionType === Type.File
                enabled: currentConnectionType === Type.File
                onClicked: pageStack.push(filePickerPage)
            }

            Button {
                id: connectButton
                text: qsTrId("label-connect")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (dbFile) {
                        console.log("Connect to db...")
                        console.log(currentConnectionType)
                        console.log(currentConnector, currentConnector.name, currentConnector.type)

                        if (currentConnector.connectToDb("", 0, dbFile, "", "")) {
                            pageStack.push(Qt.resolvedUrl("TableListPage.qml"), { "selectedConnector": currentConnector })
                        }
                    }
                }
            }
        }
    }

    Component {
        id: filePickerPage
        FilePickerPage {
            nameFilters: [ '*.sqlite' ]
            onSelectedContentPropertiesChanged: {
                page.dbFile = selectedContentProperties.filePath
            }
        }
    }

    function translateUi() {
        menuAbout.text = qsTrId("label-about")
        menuSettings.text = qsTrId("label-settings")
        pageHeader.title = qsTrId("main-header")
        connectorCombo.label = qsTrId("label-connector")
        fileButton.label = qsTrId("label-dbFile")
    }
}
