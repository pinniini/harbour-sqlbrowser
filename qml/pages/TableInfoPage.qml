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
            columnList.model = selectedConnector.getColumnModel(selectedTable)
        }
    }

    SilicaListView {
        id: columnList
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTrId("label-about")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

            MenuItem {
                text: qsTrId("label-runQuery")
                onClicked: console.log("TODO: open query page...")
            }

            MenuItem {
                text: qsTrId("label-showData")
                onClicked: pageStack.push(Qt.resolvedUrl("DataPage.qml"), { "selectedConnector": selectedConnector, "selectedTable": selectedTable })
            }
        }

        header: PageHeader {
            title: selectedTable
        }

        delegate: ListItem {
            contentHeight: Theme.itemSizeSmall
            width: parent.width

            DetailItem {
                label: model.name
                value: model.dataType
            }

//            Label {
//                text: model.name
//                y: (parent.height / 2) - (height / 2)
//                x: Theme.paddingMedium
//                width: parent.width - Theme.paddingMedium - Theme.paddingMedium
//            }

//            onClicked: {
//                console.log("Field \"" + model.name + "\" clicked at index: " + index);
//            }

            menu: ContextMenu {
                MenuItem {
                    text: qsTrId("label-action")
                    onClicked: console.log("ContextMenu item clicked...")
                }
            }
        }
    }
}
