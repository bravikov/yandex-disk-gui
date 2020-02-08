#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>

class YandexDiskNameAndVersion;

class About : public QObject
{
    Q_OBJECT

public:
    explicit About(const YandexDiskNameAndVersion& yandexDiskVersion, QObject *parent = nullptr);

public slots:
    void show();

private:
    const YandexDiskNameAndVersion& m_yandexDiskVersion;
};

#endif // ABOUT_H
