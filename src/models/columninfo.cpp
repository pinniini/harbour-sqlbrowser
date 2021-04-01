#include "columninfo.h"

ColumnInfo::ColumnInfo(QObject *parent) : QObject(parent)
{

}

ColumnInfo::ColumnInfo(QString name, QString dataType, QObject *parent)
    : QObject(parent), _name(name), _dataType(dataType)
{

}

QString ColumnInfo::name() const
{
    return _name;
}

void ColumnInfo::setName(const QString &name)
{
    if (_name != name)
    {
        _name = name;
        emit nameChanged(_name);
    }
}

QString ColumnInfo::dataType() const
{
    return _dataType;
}

void ColumnInfo::setDataType(const QString &dataType)
{
    if (_dataType != dataType)
    {
        _dataType = dataType;
        emit dataTypeChanged(_dataType);
    }
}
