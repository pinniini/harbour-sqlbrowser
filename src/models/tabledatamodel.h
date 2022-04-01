#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

#include "tabledata.h"

#include <QAbstractListModel>
#include <QObject>

class TableDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TableDataRoles
    {
        NameRole = Qt::UserRole + 1,
        DataTypeRole = Qt::UserRole + 2,
        IsHeaderRole = Qt::UserRole + 3,
        IsNonValueRole = Qt::UserRole + 4
    };

    explicit TableDataModel(QObject *parent = nullptr);
    ~TableDataModel();

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

    Q_INVOKABLE TableData* get(int index);
    Q_INVOKABLE int dataCount();
    Q_INVOKABLE int headerCount();

    void addData(TableData *data);

private:
    QVector<TableData *> *_data;
};

#endif // TABLEDATAMODEL_H
