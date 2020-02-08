#ifndef YANDEXDISK_H
#define YANDEXDISK_H

#include "yandex-disk-name-and-version.h"

#include <QObject>

class YandexDisk: public QObject
{
    Q_OBJECT

public:
    explicit YandexDisk(QObject* parent = nullptr);

    void showStatus() const;
    void start() const;
    void stop() const;
    const YandexDiskNameAndVersion& getNameAndVersion() const;
    QString getHelp() const;

private:
    struct Output
    {
        bool finished = false;
        QString stdOutput;
        QString stdError;
    };

    Output run(const QString& arguments, const int timeout_ms) const;
    void runAndShowOutput(const QString& command, const int timeout_ms) const;
    const char* processName{"yandex-disk"};

    class YandexDiskNameAndVersionImpl: public YandexDiskNameAndVersion
    {
    public:
        explicit YandexDiskNameAndVersionImpl(const YandexDisk& yandexDisk);
        operator QString() const override;
    private:
        const YandexDisk& m_yandexDisk;
    };

    YandexDiskNameAndVersionImpl m_yandexDiskNameAndVersionImpl;
};

#endif // YANDEXDISK_H
