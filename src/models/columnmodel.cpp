#include "columnmodel.h"

ColumnModel::ColumnModel(QObject *parent)
    : QAbstractListModel(parent), _columns(new QVector<ColumnInfo *>())
{

}

ColumnModel::~ColumnModel()
{
    if (_columns != nullptr)
    {
        for (int i = 0; i < _columns->length(); ++i)
        {
            delete _columns->at(i);
            _columns->replace(i, nullptr);
        }

        _columns->clear();
        delete _columns;
        _columns = nullptr;
    }
}

int ColumnModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (_columns != nullptr)
    {
        return _columns->length();
    }
    else
    {
        return 0;
    }
}

QVariant ColumnModel::data(const QModelIndex &index, int role) const
{
    // Validate index.
    if (index.isValid() && index.row() < _columns->length())
    {
        switch (role) {
        case NameRole:
            return _columns->at(index.row())->name();
        case DataTypeRole:
            return _columns->at(index.row())->dataType();
        default:
            return QVariant();
        }
    }
    else // Invalid index, return empty.
    {
        return QVariant();
    }
}

QHash<int, QByteArray> ColumnModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DataTypeRole] = "dataType";
    return roles;
}

ColumnInfo *ColumnModel::get(int index)
{
    if (_columns == nullptr || index < 0 || index > _columns->length() - 1)
    {
        return nullptr;
    }

    return _columns->at(index);
}

void ColumnModel::addColumnInfo(ColumnInfo *info)
{
    if (info != nullptr && _columns != nullptr)
    {
        _columns->push_back(info);
    }
}
