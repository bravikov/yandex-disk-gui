#ifndef YANDEXDISK_H
#define YANDEXDISK_H

#include <QObject>

class YandexDisk: public QObject
{
    Q_OBJECT

public:
    explicit YandexDisk(QObject* parent = nullptr);

    void showStatus() const;
    void start() const;
    void stop() const;

private:
    void run(const QString& command, const int timeout_ms) const;
    const char* processName{"yandex-disk"};
};

#endif // YANDEXDISK_H
