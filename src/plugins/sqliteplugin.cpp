#include "sqliteplugin.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlIndex>
#include <QDebug>
#include <QSqlDriver>

SQLitePlugin::SQLitePlugin() : m_server(""), m_port(0), m_databasePath(""), m_user("")
{
    qDebug() << QSqlDatabase::drivers();
    m_name = "SQLite";
    m_type = Type::File;
}

SQLitePlugin::~SQLitePlugin()
{
    m_database.close();
}

bool SQLitePlugin::connectToDb(const QString &server, const int &port, const QString &database, const QString &user, const QString &password)
{
    Q_UNUSED(server);
    Q_UNUSED(port);
    Q_UNUSED(user);
    Q_UNUSED(password);

    if(database == "")
    {
        return false;
    }

    if (m_database.isOpen())
    {
        m_database.close();
        QSqlDatabase::removeDatabase("sqliteConnection");
    }

    m_databasePath = database;
    m_database = QSqlDatabase::addDatabase("QSQLITE", "sqliteConnection");
    m_database.setDatabaseName(database);

    qDebug() << "Named placeholders support:" << m_database.driver()->hasFeature(QSqlDriver::NamedPlaceholders);
    qDebug() << "Positional placeholders support:" << m_database.driver()->hasFeature(QSqlDriver::PositionalPlaceholders);
    qDebug() << "Prepared queries support:" << m_database.driver()->hasFeature(QSqlDriver::PreparedQueries);

    return m_database.open();
}

QString SQLitePlugin::getError() const
{
    QSqlError error = QSqlDatabase::database("sqliteConnection").lastError();
    return error.text();
}

QStringList SQLitePlugin::getTables()
{
    return m_database.tables(QSql::Tables);
}

TableModel *SQLitePlugin::getTableModel()
{
    TableModel *model = new TableModel();
    QStringList tables = m_database.tables(QSql::Tables);
    foreach (QString tableName, tables)
    {
        model->addTableInfo(new TableInfo(tableName));
    }

    return model;
}

QStringList SQLitePlugin::getColumnsForTable(const QString &tableName)
{
    QStringList retList;

    if (!m_database.isOpen())
    {
        return retList;
    }

    // Get fields.
    QSqlRecord record = m_database.record(tableName);
    if(record.isEmpty())
    {
        return retList;
    }

    QSqlIndex primary = m_database.primaryIndex(tableName);
    if (!primary.isEmpty())
    {
        retList << primary.name() + ": primary index";
    }

    // Build return list.
    for(int i = 0; i < record.count(); ++i)
    {
        QSqlField field = record.field(i);
        retList << field.name() + ": " + QVariant::typeToName(field.type());
    }

    return retList;

//    QSqlQuery *query = new QSqlQuery(m_database);
//    //if(!query->prepare("PRAGMA schema.table_info(?)"))
//    if(!query->prepare("PRAGMA table_info(TestTable)"))
//    {
//        qDebug() << "PRAGMA query preparation failed.";

//        qDebug() << query->lastError().text();

//        qDebug() << getError();
//        return retList;
//    }

//    //query->bindValue(0, tableName);

//    if(!query->exec())
//    {
//        qDebug() << "PRAGMA query exec failed.";
//        qDebug() << query->lastError().text();
//        return retList;
//    }

//    for(int i = 0; i < query->record().count(); ++i)
//    {
//        retList.append(query->record().value(i).toString());
//    }

//    query->finish();
//    delete query;
//    query = 0;
    //    return retList;
}

ColumnModel *SQLitePlugin::getColumnModel(const QString &tableName)
{

    if (!m_database.isOpen())
    {
        return nullptr;
    }

    // Get fields.
    QSqlRecord record = m_database.record(tableName);
    if(record.isEmpty())
    {
        return nullptr;
    }

    QStringList retList;
    ColumnModel *model = new ColumnModel ();

    QStringList primaryFields;
    QSqlIndex primary = m_database.primaryIndex(tableName);
    if (!primary.isEmpty())
    {
        for (int i = 0; i < primary.count(); ++i)
        {
            primaryFields << primary.field(i).name();
        }
//        model->addColumnInfo(new ColumnInfo("Primary index", primaryFields.join(",")));
    }

    // Build return list.
    for(int i = 0; i < record.count(); ++i)
    {
        QSqlField field = record.field(i);
        ColumnInfo *info = new ColumnInfo();
        info->setName(field.name());
        QString tmpType = QVariant::typeToName(field.type());

        if (primaryFields.contains(info->name()))
        {
            tmpType += ", Primary key";
        }
        info->setDataType(tmpType);

//        model->addColumnInfo(new ColumnInfo(field.name(), QVariant::typeToName(field.type())));
        model->addColumnInfo(info);
    }

    return model;
}

QStringList SQLitePlugin::getAllDataFromTable(const QString &tableName)
{
    qDebug() << "Getting data from table " << tableName << "...";

    QStringList retList;

    if (!m_database.isOpen())
    {
        return retList;
    }

    // Get fields.
    QSqlRecord record = m_database.record(tableName);
    if(record.isEmpty())
    {
        return retList;
    }

    QSqlQuery query(m_database); //("SELECT * FROM " + tableName);
    //query.prepare("SELECT rowid FROM :tablename");
    QString tmpTable = m_database.driver()->escapeIdentifier(tableName, QSqlDriver::TableName);
    if (!query.prepare(QString("SELECT * FROM %1").arg(tmpTable)))
    {
        qDebug() << query.lastError().text();
    }
//    query.prepare("SELECT * FROM Favorite");
    //query.bindValue(0, tableName);
//    query.bindValue(0, "articleId");
    query.exec();

    qDebug() << query.isActive();
    qDebug() << query.isValid();
    qDebug() << query.lastError().text();
    qDebug() << query.executedQuery();
    qDebug() << getError();

    while (query.next())
    {
        QString data = "";
        for (int i = 0; i < record.count(); ++i)
        {
            data += query.value(i).toString() + " - ";
        }

        retList << data;
    }

    return retList;
}

int SQLitePlugin::getRowCount(const QString &tableName)
{
    QSqlQuery query(m_database);
    QString tmpTable = m_database.driver()->escapeIdentifier(tableName, QSqlDriver::TableName);
    if (!query.prepare(QString("SELECT COUNT(*) FROM %1").arg(tmpTable)))
    {
        qDebug() << query.lastError().text();
    }

    int rowCount = 0;
    query.exec();
    while (query.next())
    {
        rowCount = query.value(0).toInt();
        qDebug() << "Row count:" << rowCount;
    }

    return rowCount;
}

QString SQLitePlugin::name() const
{
    return m_name;
}

Type SQLitePlugin::type() const
{
    return m_type;
}
