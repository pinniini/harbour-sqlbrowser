#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "tableinfo.h"

#include <QObject>
#include <QAbstractListModel>
#include <QVector>

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TableRoles
    {
        NameRole = Qt::UserRole + 1
    };

    TableModel(QObject *parent = nullptr);
    ~TableModel();

    ///
    /// \brief rowCount
    /// \param parent
    /// \return
    ///
    virtual int rowCount(const QModelIndex &parent) const;

    ///
    /// \brief data
    /// \param index
    /// \param role
    /// \return
    ///
    virtual QVariant data(const QModelIndex &index, int role) const;

    ///
    /// \brief roleNames
    /// \return
    ///
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE TableInfo* get(int index);

    void addTableInfo(TableInfo *info);

private:
    QVector<TableInfo *> *_tables;
};

#endif // TABLEMODEL_H
