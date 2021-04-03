#ifndef COLUMNMODEL_H
#define COLUMNMODEL_H

#include "columninfo.h"

#include <QObject>
#include <QAbstractListModel>

class ColumnModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ColumnRoles
    {
        NameRole = Qt::UserRole + 1,
        DataTypeRole = Qt::UserRole + 2
    };

    ColumnModel(QObject *parent = nullptr);
    ~ColumnModel();

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

    Q_INVOKABLE ColumnInfo* get(int index);

    void addColumnInfo(ColumnInfo *info);

private:
    QVector<ColumnInfo *> *_columns;
};

#endif // COLUMNMODEL_H
