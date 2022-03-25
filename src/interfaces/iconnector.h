#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include <QObject>
#include <QSqlDatabase>

#include "../interfaces/connectioninfo.h"
#include "../models/tablemodel.h"
#include "../models/columnmodel.h"
#include "../models/tabledatamodel.h"

class IConnector : public QObject
{
    Q_OBJECT
public:
    IConnector();
    ~IConnector();

    Q_INVOKABLE virtual bool connectToDb(const QString &server, const int &port, const QString &database, const QString &user, const QString &password);
    Q_INVOKABLE virtual QString getError() const;
    Q_INVOKABLE virtual QStringList getTables();
    Q_INVOKABLE virtual TableModel* getTableModel();
    Q_INVOKABLE virtual QStringList getColumnsForTable(const QString &tableName);
    Q_INVOKABLE virtual ColumnModel* getColumnModel(const QString &tableName);
    Q_INVOKABLE virtual QStringList getAllDataFromTable(const QString &tableName);
    Q_INVOKABLE virtual TableDataModel* getTableDataModel(const QString &tableName);
    Q_INVOKABLE virtual int getRowCount(const QString &tableName);

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)

    virtual QString name() const;
    virtual Type type() const;

signals:
    void nameChanged();
    void typeChanged();

public slots:
};

#endif // ICONNECTOR_H
