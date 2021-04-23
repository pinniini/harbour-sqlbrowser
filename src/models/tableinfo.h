#ifndef TABLEINFO_H
#define TABLEINFO_H

#include <QObject>

class TableInfo : public QObject
{
    Q_OBJECT

public:
    explicit TableInfo(QObject *parent = nullptr);
    TableInfo(QString name, QObject *parent = nullptr);

    Q_PROPERTY(QString name READ name /*WRITE setName*/ NOTIFY nameChanged)

    QString name() const;
//    void setName(const QString &name);

signals:
    void nameChanged(QString name);

private:
    QString _name;
};

#endif // TABLEINFO_H
