//#ifdef QT_QML_DEBUG
//#include <QtQuick>
//#endif

#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>
#include <QLocale>
#include <sailfishapp.h>

#include "interfaces/iconnector.h"
#include "interfaces/connectioninfo.h"
#include "plugins/sqliteplugin.h"
#include "translationhandler.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/harbour-sqlbrowser.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QScopedPointer<QGuiApplication> a(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QTranslator translator;
    Settings setts;
    QString sysLocale = QLocale::system().name();
    sysLocale.resize(2);
    bool translationsLoaded = false;
    QString locale = setts.getStringSetting("Language", sysLocale);
    if(locale != "en" && !translator.load("harbour-sqlbrowser-" + locale, SailfishApp::pathTo("translations").toLocalFile()))
    {
        qDebug() << "Could not load locale: " + locale;

        locale = QLocale::system().name();
        if(!translator.load("harbour-sqlbrowser-" + locale, SailfishApp::pathTo("translations").toLocalFile()))
        {
            qDebug() << "Could not load locale: " + locale;
        }
        else
        {
            translationsLoaded = true;
        }
    }

    // Just for safety.
    if (!translationsLoaded)
    {
        locale = "en";
        if(!translator.load("harbour-sqlbrowser-" + locale, SailfishApp::pathTo("translations").toLocalFile()))
        {
            qDebug() << "Could not load locale: " + locale;
        }
    }

    a->installTranslator(&translator);

    qRegisterMetaType<Type>("Type");
    qmlRegisterUncreatableType<ConnectionInfo>("fi.pinniini.sqlBrowser", 1, 0, "Type", "Not creatable.");

    qmlRegisterType<IConnector>("fi.pinniini.sqlBrowser", 1, 0, "Connector");

    QVariantList connectors;
    IConnector *sqlite = new SQLitePlugin();
    connectors.append(QVariant::fromValue(sqlite));

    // Settings
    Settings *settings = new Settings(nullptr);

    // Translator
    TranslationHandler *handler = new TranslationHandler(nullptr);

    QString appVersion = "0.1.0";
    view->rootContext()->setContextProperty("Settings", settings);
    view->rootContext()->setContextProperty("TranslationHandler", handler);
    view->rootContext()->setContextProperty("SQLConnectors", connectors);
    view->rootContext()->setContextProperty("appVersion", appVersion);
    view->setSource(SailfishApp::pathToMainQml());
    view->show();
    return a->exec();

//    return SailfishApp::main(argc, argv);
}
