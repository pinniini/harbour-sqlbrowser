import QtQuick 2.2
import Sailfish.Silica 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: tableInfoPage
    clip: true

    property string selectedTable: ""
    property Connector selectedConnector

    Component.onCompleted: {
        if (selectedConnector && selectedTable) {
            var fields = selectedConnector.getColumnsForTable(selectedTable)
            if (fields && fields.length > 0) {
                tableInfoModel.clear()
                var count = fields.length

                for (var i = 0; i < count; ++i) {
                    var field = fields[i]
                    tableInfoModel.append({ "name": field })
                }
            }
        }
    }

    ListModel {
        id: tableInfoModel
    }

    SilicaListView {
        anchors.fill: parent
        model: tableInfoModel

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

            MenuItem {
                text: qsTr("Run query")
                onClicked: console.log("TODO: open query page...")
            }

            MenuItem {
                text: qsTr("Show data")
                onClicked: pageStack.push(Qt.resolvedUrl("DataPage.qml"), { "selectedConnector": selectedConnector, "selectedTable": selectedTable })
            }
        }

        header: PageHeader {
            title: selectedTable
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
                console.log("Field \"" + model.name + "\" clicked at index: " + index);
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
