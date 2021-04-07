#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>

class TableDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TableDataModel(QObject *parent = nullptr);
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

    //Q_INVOKABLE ColumnInfo* get(int index);
};

#endif // TABLEDATAMODEL_H
