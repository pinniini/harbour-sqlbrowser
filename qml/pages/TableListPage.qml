import QtQuick 2.2
import Sailfish.Silica 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: tablesPage
    clip: true

    property Connector selectedConnector

    Component.onCompleted: {
        if (selectedConnector) {
            var tables = selectedConnector.getTables()
            if (tables && tables.length > 0) {
                tableModel.clear()
                var count = tables.length

                for (var i = 0; i < count; ++i) {
                    var table = tables[i]
                    tableModel.append({ "name": table })
                }
            }
        }
    }

    ListModel {
        id: tableModel
    }

    SilicaListView {
        anchors.fill: parent
        model: tableModel

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

            MenuItem {
                text: qsTr("Run query")
                onClicked: console.log("TODO: open query page...")
            }
        }

        header: PageHeader {
            title: qsTr("Tables")
        }

        delegate: ListItem {
            contentHeight: Theme.itemSizeSmall
            width: parent.width

            Label {
                text: model.name
                y: (parent.height / 2) - (height / 2)
                x: Theme.paddingMedium
                width: parent.width - Theme.paddingMedium - Theme.paddingMedium
            }

            onClicked: {
                console.log("Table \"" + model.name + "\" clicked at index: " + index);
                pageStack.push(Qt.resolvedUrl("TableInfoPage.qml"), { "selectedTable": model.name, "selectedConnector": selectedConnector })
            }

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Action")
                    onClicked: console.log("ContextMenu item clicked...")
                }
            }
        }
    }
}
