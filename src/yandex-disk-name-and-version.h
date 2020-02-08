#ifndef YANDEXDISKNAMEANDVERSION_H
#define YANDEXDISKNAMEANDVERSION_H

#include <QString>

class YandexDiskNameAndVersion
{
public:
    virtual ~YandexDiskNameAndVersion() = default;
    virtual operator QString() const = 0;
};
#endif // YANDEXDISKNAMEANDVERSION_H
