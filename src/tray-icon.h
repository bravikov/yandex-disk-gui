#ifndef TRAYICON_H
#define TRAYICON_H

#include "status-parser.h"

#include <QObject>
#include <QMenu>
#include <QSystemTrayIcon>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QMenu* menu, QObject *parent = nullptr);

public slots:
    void updateSyncStatus(const SyncStatus syncStatus);

private:
    QSystemTrayIcon* m_tray = nullptr;
};

#endif // TRAYICON_H
