#include "tabledatamodel.h"

TableDataModel::TableDataModel(QObject *parent)
    : QAbstractListModel(parent), _data(new QVector<TableData *>())
{

}

TableDataModel::~TableDataModel()
{
    if (_data != nullptr)
    {
        for (int i = 0; i < _data->length(); ++i)
        {
            delete _data->at(i);
            _data->replace(i, nullptr);
        }

        _data->clear();
        delete _data;
        _data = nullptr;
    }
}

int TableDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (_data != nullptr)
    {
        return _data->length();
    }
    else
    {
        return 0;
    }
}

QVariant TableDataModel::data(const QModelIndex &index, int role) const
{
    // Validate index.
    if (index.isValid() && index.row() < _data->length())
    {
        switch (role) {
        case NameRole:
            return _data->at(index.row())->name();
        case DataTypeRole:
            return _data->at(index.row())->dataType();
        case IsHeaderRole:
            return _data->at(index.row())->isHeader();
        case IsNonValueRole:
            return _data->at(index.row())->isNonValue();
        default:
            return QVariant();
        }
    }
    else // Invalid index, return empty.
    {
        return QVariant();
    }
}

QHash<int, QByteArray> TableDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DataTypeRole] = "dataType";
    roles[IsHeaderRole] = "isHeader";
    roles[IsNonValueRole] = "isNonValue";
    return roles;
}

TableData *TableDataModel::get(int index)
{
    if (_data == nullptr || index < 0 || index > _data->length() - 1)
    {
        return nullptr;
    }

    return _data->at(index);
}

int TableDataModel::dataCount()
{
    return _data != nullptr ? _data->count() : 0;
}

int TableDataModel::headerCount()
{
    int headers = 0;
    if (_data != nullptr)
    {
        for (int i = 0; i < _data->count(); ++i)
        {
            auto data = _data->at(i);
            if (!data->isHeader())
            {
                break;
            }

            ++headers;
        }
    }

    return headers;
}

void TableDataModel::addData(TableData *data)
{
    if (data != nullptr && _data != nullptr)
    {
        _data->push_back(data);
    }
}
