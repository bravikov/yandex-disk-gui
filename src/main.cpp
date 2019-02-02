#include "YandexDisk.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QObject>

void showStatus();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    YandexDisk yandexDisk;

    QSystemTrayIcon tray{QIcon{":/YandexDisk.png"}};

    QMenu menu;
    menu.addAction(QObject::tr("Status"), &yandexDisk, &YandexDisk::showStatus);
    menu.addSeparator();
    menu.addAction(QObject::tr("Start"), &yandexDisk, &YandexDisk::start);
    menu.addAction(QObject::tr("Stop"), &yandexDisk, &YandexDisk::stop);
    menu.addSeparator();
    menu.addAction(QObject::tr("Exit"), &a, &QApplication::exit);

    tray.setContextMenu(&menu);
    tray.show();

    return a.exec();
}
