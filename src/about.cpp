#include "about.h"
#include "yandex-disk-name-and-version.h"

#include <QApplication>
#include <QMessageBox>

About::About(const YandexDiskNameAndVersion& yandexDiskVersion, QObject *parent)
    : QObject(parent)
    , m_yandexDiskVersion(yandexDiskVersion)
{}

void About::show()
{
    const QString name{QApplication::applicationName()};
    const QString version{QApplication::applicationVersion()};
    const QString url{"https://github.com/bravikov/yandex-disk-gui"};
    const QString email{"dmitry@bravikov.pro"};
    const QString message{
        QObject::tr(R"(
            <h1>%1</h1>
            Version: %2.
            <p>Open source <a href='%3'>project</a>.</p>
            <p>© 2019 Dmitry Bravikov (<a href='mailto:%4'>%4</a>)</p>
            <p>Based on %5</p>
        )").arg(name).arg(version).arg(url).arg(email).arg(m_yandexDiskVersion)
    };
    QMessageBox::about(nullptr, name, message);
}
