#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractListModel(parent), _tables(new QVector<TableInfo *>())
{

}

TableModel::~TableModel()
{
    if (_tables != nullptr)
    {
        for (int i = 0; i < _tables->length(); ++i)
        {
            delete _tables->at(i);
            _tables->replace(i, nullptr);
        }

        _tables->clear();
        delete _tables;
        _tables = nullptr;
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (_tables != nullptr)
    {
        return _tables->length();
    }
    else
    {
        return 0;
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // Validate index.
    if (index.isValid() && index.row() < _tables->length())
    {
        switch (role) {
        case NameRole:
            return _tables->at(index.row())->name();
        default:
            return QVariant();
        }
    }
    else // Invalid index, return empty.
    {
        return QVariant();
    }
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

TableInfo *TableModel::get(int index)
{
    if (_tables == nullptr || index < 0 || index > _tables->length() - 1)
    {
        return nullptr;
    }

    return _tables->at(index);
}

void TableModel::addTableInfo(TableInfo *info)
{
    if (info != nullptr && _tables != nullptr)
    {
        _tables->push_back(info);
    }
}

