import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    id: settingsPage

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Component.onCompleted: {
        console.log(pageStack[pageStack.depth - 1])
        var language = Settings.getStringSetting("Language", Qt.locale().name.substring(0,2))
        if (language === "en") {
            languageCombo.currentIndex = 0;
        } else if (language === "fi") {
            languageCombo.currentIndex = 1;
        }
    }

    Connections {
        target: TranslationHandler
        onTranslateUI: {
            translateUi()
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        clip: true
        contentHeight: contentColumn.height

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                id: pageHeader
                title: qsTrId("label-settings")
            }

            ComboBox {
                id: languageCombo
                label: qsTrId("label-language")

                menu: ContextMenu {
                    id: languageContext
                    MenuItem {
                        property string value: "en"
                        text: "English"
                        onClicked: {
                            setLanguage(value)
                        }
                    }
                    MenuItem {
                        property string value: "fi"
                        text: "Suomi"
                        onClicked: {
                            setLanguage(value)
                        }
                    }
                }
            }
        }
    }

    function setLanguage(value) {
        Settings.setSetting("Language", value)
        TranslationHandler.loadTranslation(value)
    }

    function translateUi() {
        pageHeader.title = qsTrId("label-settings")
        languageCombo.label = qsTrId("label-language")
    }
}
