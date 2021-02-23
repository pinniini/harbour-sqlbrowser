#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include <QObject>

class ConnectionInfo
{
    Q_GADGET
public:
    enum Type {
        File,
        Details
    };
    Q_ENUM(Type)

private:
    explicit ConnectionInfo();
};

typedef ConnectionInfo::Type Type;

#endif // CONNECTIONINFO_H
