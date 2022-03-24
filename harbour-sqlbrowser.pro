# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

QT += sql

# The name of your application
TARGET = harbour-sqlbrowser

CONFIG += sailfishapp

SOURCES += src/harbour-sqlbrowser.cpp \
    src/interfaces/connectioninfo.cpp \
    src/interfaces/iconnector.cpp \
    src/models/columninfo.cpp \
    src/models/columnmodel.cpp \
    src/models/tabledatamodel.cpp \
    src/models/tableinfo.cpp \
    src/models/tablemodel.cpp \
    src/plugins/sqliteplugin.cpp \
    src/settings.cpp \
    src/translationhandler.cpp

DISTFILES += qml/harbour-sqlbrowser.qml \
    qml/cover/CoverPage.qml \
    qml/pages/AboutPage.qml \
    qml/pages/DataPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/TableDataPage.qml \
    qml/pages/TableInfoPage.qml \
    qml/pages/TableListPage.qml \
    rpm/harbour-sqlbrowser.changes.in \
    rpm/harbour-sqlbrowser.changes.run.in \
    rpm/harbour-sqlbrowser.spec \
    rpm/harbour-sqlbrowser.yaml \
    translations/*.ts \
    harbour-sqlbrowser.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
CONFIG += sailfishapp_i18n_idbased

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-sqlbrowser-en.ts \
    translations/harbour-sqlbrowser-fi.ts

HEADERS += \
    src/interfaces/connectioninfo.h \
    src/interfaces/iconnector.h \
    src/models/columninfo.h \
    src/models/columnmodel.h \
    src/models/tabledatamodel.h \
    src/models/tableinfo.h \
    src/models/tablemodel.h \
    src/plugins/sqliteplugin.h \
    src/settings.h \
    src/translationhandler.h
