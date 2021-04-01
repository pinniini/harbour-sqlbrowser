#include "tableinfo.h"

TableInfo::TableInfo(QObject *parent) : QObject(parent)
{

}

TableInfo::TableInfo(QString name, QObject *parent)
    : QObject(parent), _name((name))
{

}

QString TableInfo::name() const
{
    return _name;
}

void TableInfo::setName(const QString &name)
{
    if (_name != name)
    {
        _name = name;
        emit nameChanged(_name);
    }
}
