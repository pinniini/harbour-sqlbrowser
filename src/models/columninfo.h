#ifndef COLUMNINFO_H
#define COLUMNINFO_H

#include <QObject>

class ColumnInfo : public QObject
{
    Q_OBJECT
public:
    explicit ColumnInfo(QObject *parent = nullptr);
    ColumnInfo(QString name, QString dataType, QObject *parent = nullptr);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString dataType READ dataType WRITE setDataType NOTIFY dataTypeChanged)

    QString name() const;
    void setName(const QString &name);

    QString dataType() const;
    void setDataType(const QString &dataType);

signals:
    void nameChanged(QString name);
    void dataTypeChanged(QString dataType);

private:
    QString _name;
    QString _dataType;
};

#endif // COLUMNINFO_H
