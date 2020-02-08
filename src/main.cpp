#include "YandexDisk.h"
#include "about.h"
#include "yandex-disk-name-and-version.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Yandex Disk GUI");
    a.setApplicationVersion("0.2.0");
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
    menu.addSeparator();

    About about{yandexDisk.getNameAndVersion()};
    menu.addAction(QObject::tr("About"), &about, &About::show);

    tray.setContextMenu(&menu);
    tray.show();

    return a.exec();
}
