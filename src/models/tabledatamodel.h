#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

#include <QAbstractListModel>
#include <QObject>

class TableDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TableDataRoles
    {
        NameRole = Qt::UserRole + 1,
        DataTypeRole = Qt::UserRole + 2
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

//    Q_INVOKABLE ColumnInfo* get(int index);
    Q_INVOKABLE int dataCount();
//    void addColumnInfo(ColumnInfo *info);

private:
//    QVector<ColumnInfo *> *_columns;
};

#endif // TABLEDATAMODEL_H
