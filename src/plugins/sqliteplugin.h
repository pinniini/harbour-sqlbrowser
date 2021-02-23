#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include "../interfaces/iconnector.h"
#include "../interfaces/connectioninfo.h"

#include <QObject>

class SQLitePlugin : public IConnector
{
public:
    SQLitePlugin();
    virtual ~SQLitePlugin();

    // IConnector interface
    bool connectToDb(const QString &server, const int &port, const QString &database, const QString &user, const QString &password) override;
    QString getError() const override;
    QStringList getTables() override;
    QStringList getColumnsForTable(const QString &tableName) override;
    QStringList getAllDataFromTable(const QString &tableName) override;

    QString name() const override;
    Type type() const override;

private:
    QSqlDatabase m_database;
    QString m_server;
    int m_port;
    QString m_databasePath;
    QString m_user;
    QString m_name;
    Type m_type;
};

#endif // SQLITEPLUGIN_H
