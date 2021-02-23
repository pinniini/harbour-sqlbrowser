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
                text: qsTr("Select db")
                onClicked: {
                    console.log("Connection type (file):", Type.File)
                    console.log("Connection type (details):", Type.Details)
//                    pageStack.push(filePickerPage)
                }
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
                title: qsTr("SQL Browser")
            }

            ComboBox {
                id: connectorCombo
                width: parent.width - Theme.paddingMedium
                label: qsTr("Connector")

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
                label: qsTr("DB file")
                value: dbFile ? dbFile : qsTr("No db selected")
                visible: currentConnectionType === Type.File
                enabled: currentConnectionType === Type.File
                onClicked: pageStack.push(filePickerPage)
            }

            Button {
                id: connectButton
                text: qsTr("Connect")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (dbFile) {
                        console.log("Connect to db...")
                        console.log(currentConnectionType)
                        console.log(currentConnector, currentConnector.name, currentConnector.type)

                        if (currentConnector.connectToDb("", 0, dbFile, "", "")) {
                            pageStack.push(Qt.resolvedUrl("TableListPage.qml"), { "selectedConnector": currentConnector })

//                            var tables = currentConnector.getTables()
//                            console.log("Table count:", tables.length)

//                            var count = tables.length
//                            for (var i = 0; i < count; ++i) {
//                                console.log("Table:", tables[i])
//                                var fields = currentConnector.getColumnsForTable(tables[i]);
//                                var count2 = fields.length
//                                for (var j = 0; j < count2; ++j) {
//                                    console.log("Field:", fields[j])
//                                }
//                            }
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
}
