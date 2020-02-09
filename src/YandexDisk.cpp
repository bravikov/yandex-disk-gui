#include "YandexDisk.h"

#include "yandex-disk-name-and-version.h"

#include <QMessageBox>
#include <QProcess>
#include <QAction>

namespace
{
    struct YandexDiskHelp
    {
        QString nameAndVersion;
    };

    struct YandexDiskHelpParser
    {
        YandexDiskHelp parse(const QString& helpString) const
        {
            YandexDiskHelp help;
            help.nameAndVersion = helpString.section('\n', 0, 0);
            return help;
        }
    };
} // anonymous namespace


YandexDisk::YandexDiskNameAndVersionImpl::YandexDiskNameAndVersionImpl(const YandexDisk& yandexDisk)
        : m_yandexDisk{yandexDisk}
    {}

YandexDisk::YandexDiskNameAndVersionImpl::operator QString() const
    {
        const YandexDiskHelpParser yandexDiskHelpParser;
        const YandexDiskHelp yandexDiskHelp = yandexDiskHelpParser.parse(m_yandexDisk.getHelp());
        return yandexDiskHelp.nameAndVersion;
    }


YandexDisk::YandexDisk(QObject* parent)
    : QObject(parent)
    , m_yandexDiskNameAndVersionImpl{*this}
{
    emit syncStatusChanged(m_syncStatus);

    QTimer* statusTimer = new QTimer{this};
    connect(statusTimer, &QTimer::timeout, this, &YandexDisk::updateSyncStatus);
    statusTimer->start(2000);
}

void YandexDisk::showStatus() const
{
    runAndShowOutput("status", 1000);
}

void YandexDisk::start() const
{
    QAction* action = dynamic_cast<QAction*>(sender());
    QString actionText;
    if (action != nullptr) {
        action->setEnabled(false);
        actionText = action->text();
        action->setText(tr("Starting..."));
    }

    runAndShowOutput("start", -1);

    if (action != nullptr) {
        action->setText(actionText);
        action->setEnabled(true);
    }
}

void YandexDisk::stop() const
{
    runAndShowOutput("stop", 3000);
}

const YandexDiskNameAndVersion& YandexDisk::getNameAndVersion() const
{
    return m_yandexDiskNameAndVersionImpl;
}

QString YandexDisk::getHelp() const
{
    const auto output = run("--help", 1000);
    return output.stdOutput;
}

YandexDisk::Output YandexDisk::run(const QString& arguments, const int timeout_ms) const
{
    Output output;

    QProcess process;
    process.start(processName, {arguments});
    if (!process.waitForFinished(timeout_ms)) {
        return output;
    }

    output.finished = true;
    output.stdError = QString::fromUtf8(process.readAllStandardError());
    output.stdOutput =QString::fromUtf8(process.readAllStandardOutput());

    return output;
}

void YandexDisk::runAndShowOutput(const QString& command, const int timeout_ms) const
{
    const auto output = run(command, timeout_ms);

    if (!output.finished) {
        QMessageBox::warning(nullptr, tr("Yandex Disk"),
                         tr("Error while the %1 request.").arg(command));
        return;
    }

    QString message;
    message += output.stdError;
    if (!output.stdError.isEmpty() && !output.stdOutput.isEmpty()) {
        message += "\n\n";
    }
    message += output.stdOutput;

    QMessageBox::information(nullptr, tr("Yandex Disk"), message);
}

void YandexDisk::updateSyncStatus()
{
    const auto output = run("status", 1000);

    if (!output.finished) {
        return;
    }

    StatusParser statusParser;
    const auto status = statusParser.parse(output.stdOutput);
    m_syncStatus = status.syncStatus;
    emit syncStatusChanged(m_syncStatus);
}
