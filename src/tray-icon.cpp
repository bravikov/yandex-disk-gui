#include "tray-icon.h"

TrayIcon::TrayIcon(QMenu* menu, QObject *parent) : QObject(parent)
{
    m_tray = new QSystemTrayIcon{QIcon{":/YandexDiskInactive.png"}, this};
    m_tray->setContextMenu(menu);
    m_tray->show();
}

void TrayIcon::updateSyncStatus(const SyncStatus syncStatus)
{
    switch (syncStatus) {
        case SyncStatus::Unknown: {
            m_tray->setIcon(QIcon{":/YandexDiskInactive.png"});
            break;
        }
        case SyncStatus::NotStarted: {
            m_tray->setIcon(QIcon{":/YandexDiskInactive.png"});
            break;
        }
        case SyncStatus::Idle: {
            m_tray->setIcon(QIcon{":/YandexDisk.png"});
            break;
        }
        case SyncStatus::Busy: {
            m_tray->setIcon(QIcon{":/YandexDiskSync.png"});
            break;
        }
        case SyncStatus::Index: {
            m_tray->setIcon(QIcon{":/YandexDiskSync.png"});
            break;
        }
    }
}
