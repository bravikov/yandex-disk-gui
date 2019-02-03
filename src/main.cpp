#include "YandexDisk.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QObject>
#include <QMessageBox>

void about();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Yandex Disk GUI");
    a.setApplicationVersion("0.1.0");
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
    menu.addAction(QObject::tr("About"), &a, &about);

    tray.setContextMenu(&menu);
    tray.show();

    return a.exec();
}

void about()
{
    const QString name{QApplication::applicationName()};
    const QString version{QApplication::applicationVersion()};
    const QString url{"https://github.com/bravikov/yandex-disk-gui"};
    const QString email{"dmitry@bravikov.pro"};
    const QString message{
        QObject::tr(
            "<h1>%1</h1>"
            "Version: %2."
            "<p>Open source <a href='%3'>project</a>.</p>"
            "<p>© 2019 Dmitry Bravikov (<a href='mailto:%4'>%4</a>)</p>"
        ).arg(name).arg(version).arg(url).arg(email)
    };
    QMessageBox::about(nullptr, name, message);
}
