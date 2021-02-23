#include "iconnector.h"

IConnector::IConnector()
{

}

IConnector::~IConnector()
{

}

bool IConnector::connectToDb(const QString &server, const int &port, const QString &database, const QString &user, const QString &password)
{
    Q_UNUSED(server)
    Q_UNUSED(port)
    Q_UNUSED(database)
    Q_UNUSED(user)
    Q_UNUSED(password)

    return false;
}

QString IConnector::getError() const
{
    return "Implement me!";
}

QStringList IConnector::getTables()
{
    return QStringList();
}

QStringList IConnector::getColumnsForTable(const QString &tableName)
{
    Q_UNUSED(tableName)

    return QStringList();
}

QStringList IConnector::getAllDataFromTable(const QString &tableName)
{
    Q_UNUSED(tableName)

    return QStringList();
}

QString IConnector::name() const
{
    return "Implement me!";
}

Type IConnector::type() const
{
    return Type::File;
}
