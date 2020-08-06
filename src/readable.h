#pragma once
#include <QStringList>

class Readable
{
public:
    virtual QStringList getList() = 0;
    virtual ~Readable() = default;
};

