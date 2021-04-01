import QtQuick 2.2
import Sailfish.Silica 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: tablesPage
    clip: true

    property Connector selectedConnector

    Component.onCompleted: {
        if (selectedConnector) {
            tableList.model = selectedConnector.getTableModel();
        }
    }

    SilicaListView {
        id: tableList
        anchors.fill: parent
        //model: tableModel

        PullDownMenu {
            MenuItem {
                text: qsTrId("label-about")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

            MenuItem {
                text: qsTrId("label-runQuery")
                onClicked: console.log("TODO: open query page...")
            }
        }

        header: PageHeader {
            title: qsTrId("label-tables")
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
                    text: qsTrId("label-action")
                    onClicked: console.log("ContextMenu item clicked...")
                }
            }
        }
    }
}
