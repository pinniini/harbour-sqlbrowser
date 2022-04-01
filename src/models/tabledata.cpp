#include "tabledata.h"

TableData::TableData(QObject *parent)
    : QObject(parent), _name(""), _dataType(""), _isNonValue(false), _isHeader(false)
{

}

TableData::TableData(QString name, QString dataType, bool isNonValue, bool isHeader, QObject *parent)
    : QObject(parent), _name(name), _dataType(dataType), _isNonValue(isNonValue), _isHeader(isHeader)
{

}

QString TableData::name() const
{
    return _name;
}

void TableData::setName(const QString &name)
{
    if (_name != name)
    {
        _name = name;
        emit nameChanged(_name);
    }
}

QString TableData::dataType() const
{
    return _dataType;
}

void TableData::setDataType(const QString &dataType)
{
    if (_dataType != dataType)
    {
        _dataType = dataType;
        emit dataTypeChanged(_dataType);
    }
}

bool TableData::isNonValue() const
{
    return _isNonValue;
}

bool TableData::isHeader() const
{
    return _isHeader;
}
