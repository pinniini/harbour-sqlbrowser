#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QObject>

class TableData : public QObject
{
    Q_OBJECT
public:
    explicit TableData(QObject *parent = nullptr);
    TableData(QString name, QString dataType, bool isNonValue = false, bool isHeader = false, QObject *parent = nullptr);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString dataType READ dataType WRITE setDataType NOTIFY dataTypeChanged)
    Q_PROPERTY(bool isNonValue READ isNonValue NOTIFY isNonValueChanged)
    Q_PROPERTY(bool isHeader READ isHeader NOTIFY isHeaderChanged)

    QString name() const;
    void setName(const QString &name);

    QString dataType() const;
    void setDataType(const QString &dataType);

    bool isNonValue() const;
    bool isHeader() const;

signals:
    void nameChanged(QString name);
    void dataTypeChanged(QString dataType);
    void isHeaderChanged(bool isHeader);
    void isNonValueChanged(bool isNonValue);

private:
    QString _name;
    QString _dataType;
    bool _isNonValue;
    bool _isHeader;
};

#endif // TABLEDATA_H
