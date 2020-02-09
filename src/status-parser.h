#ifndef STATUSPARSER_H
#define STATUSPARSER_H

#include <QString>

enum class SyncStatus
{
    Unknown,
    NotStarted,
    Idle,
    Busy,
    Index
};



struct Status
{
    SyncStatus syncStatus = SyncStatus::Unknown;
};

class StatusParser
{
public:
    Status parse(const QString& statusString) const;
};

#endif // STATUSPARSER_H
