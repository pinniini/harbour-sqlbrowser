import QtQuick 2.2
import Sailfish.Silica 1.0

import fi.pinniini.sqlBrowser 1.0

Page {
    id: tableDataPage
    clip: true

    property string selectedTable
    property Connector selectedConnector
    property TableDataModel tableDataModel: null

    Component.onCompleted: {
        if (selectedConnector && selectedTable) {
            var dataModel = selectedConnector.getTableDataModel(selectedTable)
            dataGrid.columns = dataModel.headerCount()
            tableDataModel = dataModel
        }
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

        Grid {
            id: dataGrid
            columnSpacing: Theme.paddingMedium

            Repeater {
                model: tableDataModel

                Label {
                    text: name
                    font.family: isHeader ? Theme.fontFamilyHeading : Theme.fontFamily
                    font.bold: isHeader ? true : false
                    font.italic: isNonValue ? true : false
                    color: isNonValue ? Theme.secondaryColor : Theme.primaryColor
                }
            }
        }
    }
}
