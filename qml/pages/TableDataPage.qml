import QtQuick 2.2
import Sailfish.Silica 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: tableDataPage
    clip: true

    property string selectedTable
    property Connector selectedConnector
    property ColumnModel columnModel

    Component.onCompleted: {
        if (selectedConnector && selectedTable) {
            var allData = selectedConnector.getAllDataFromTable(selectedTable)
            if (allData && allData.length > 0) {
                dataModel.clear()
                var count = allData.length

                for (var i = 0; i < count; ++i) {
                    var data = allData[i]
                    dataModel.append({ "name": data })
                }
            }
        }
    }

    ListModel {
        id: dataModel
    }

    SilicaFlickable {
        id: mainFlick
        anchors.fill: parent

        contentWidth: dataGrid.width > parent.width ? dataGrid.width : parent.width
        contentHeight: dataGrid.height

        PullDownMenu {
            MenuItem {
                text: qsTrId("debug")
                onClicked: {
                }
            }
        }

        PageHeader {
            id: header
            title: "Data"
        }

        Grid {
            id: dataGrid
            columns: columnModel ? columnModel.colCount() : 1
            columnSpacing: Theme.paddingMedium
            anchors.top: parent.top
            anchors.topMargin: header.height

            Repeater {
                model: columnModel

                Label {
                    text: name
                }
            }
        }
    }

//    SilicaFlickable {
//        anchors.fill: parent
////        anchors {
////            left: parent.left
////            top: header.bottom
////            right: parent.right
////            bottom: parent.bottom
////        }

//        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
//        PullDownMenu {
//            MenuItem {
//                text: qsTrId("label-about")
//                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
//            }

//            MenuItem {
//                text: qsTrId("label-runQuery")
//                onClicked: console.log("TODO: open query page...")
//            }
//        }

//        // Tell SilicaFlickable the height of its content.
//        contentHeight: column.height
//        contentWidth: column.width

//        // Place our content in a Column.  The PageHeader is always placed at the top
//        // of the page, followed by our content.
//        Column {
//            id: column

////            width: parent.width
//            width: children[1].width
//            spacing: Theme.paddingLarge

//            PageHeader {
//                id: header
//                title: ""
//            }

//            Repeater {
//                model: dataModel
//                Label {
//                    text: model.name
//                    //y: (parent.height / 2) - (height / 2)
//                    x: Theme.paddingMedium
//                    //width: parent.width - Theme.paddingMedium - Theme.paddingMedium
//                }
//            }
//        }
//    }
}
