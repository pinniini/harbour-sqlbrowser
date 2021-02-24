#include <QDebug>
#include <QGuiApplication>
#include <sailfishapp.h>

#include "translationhandler.h"

TranslationHandler::TranslationHandler(QObject *parent) : QObject(parent)
{
    qDebug() << "Creating translation handler...";
    m_langPath = SailfishApp::pathTo("translations").toLocalFile();
    m_langFilePrefix = "harbour-sqlbrowser-";
    m_defaultLangPrefix = "harbour-sqlbrowser";
    qDebug() << "Language path " + m_langPath;
}

TranslationHandler::~TranslationHandler()
{

}

// Public

void TranslationHandler::loadTranslation(QString language)
{
    qDebug() << "Selected language: " << language;

    // No languge.
    if(language == "")
    {
        return;
    }

    // Remove old translator and load new file.
    qApp->removeTranslator(&m_translator);
    m_translator.load(m_langFilePrefix + language, m_langPath);

    // Try to actually load the translation.
    if(qApp->installTranslator(&m_translator))
    {
        emit translateUI();
    }
}
