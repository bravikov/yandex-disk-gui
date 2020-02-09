#include "status-parser.h"

#include <QStringList>
#include <QHash>

Status StatusParser::parse(const QString& statusString) const
{
    Status status;

    if (statusString.startsWith("Error: daemon not started")) {
        status.syncStatus = SyncStatus::NotStarted;
        return status;
    }

    const auto lines = statusString.split('\n', QString::SkipEmptyParts);

    QString syncStatus;
    for (const auto& line: lines) {
        if (line.startsWith("Synchronization core status:")) {
            syncStatus = line;
            break;
        }
    }

    if (syncStatus.isEmpty()) {
        status.syncStatus = SyncStatus::Unknown;
    }

    const auto parts = syncStatus.split(':', QString::SkipEmptyParts);
    if (parts.size() == 2) {
        const auto statusValue = parts[1].simplified();
        QHash<QString, SyncStatus> statuses {
            {"index", SyncStatus::Index},
            {"busy", SyncStatus::Busy},
            {"idle", SyncStatus::Idle},
        };

        const auto statusIt = statuses.find(statusValue);

        if (statusIt == statuses.end()) {
            status.syncStatus = SyncStatus::Unknown;
        } else {
            status.syncStatus = statusIt.value();
        }
    }

    return status;
}
