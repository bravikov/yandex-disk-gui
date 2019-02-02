#include "YandexDisk.h"
#include <QMessageBox>
#include <QProcess>

YandexDisk::YandexDisk(QObject* parent): QObject(parent) {}

void YandexDisk::showStatus() const
{
    run("status", 1000);
}

void YandexDisk::start() const
{
    run("start", 3000);
}

void YandexDisk::stop() const
{
    run("stop", 3000);
}

void YandexDisk::run(const QString& command, const int timeout_ms) const
{
    QProcess process;
    process.start(processName, {command});
    if (!process.waitForFinished(timeout_ms)) {
        QMessageBox::warning(nullptr, tr("Yandex Disk"),
                             tr("Error while the %1 request.").arg(command));
        return;
    }

    QString processError{QString::fromUtf8(process.readAllStandardError())};
    QString processOutput{QString::fromUtf8(process.readAllStandardOutput())};

    QString message;
    message += processError;
    if (!processError.isEmpty() && !processOutput.isEmpty()) {
        message += "\n\n";
    }
    message += processOutput;

    QMessageBox::information(nullptr, tr("Yandex Disk"), message);
}
