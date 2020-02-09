#include "../src/status-parser.h"

#include <QtTest>
#include <QVector>

class StatusParserTest : public QObject
{
    Q_OBJECT

public:
    StatusParserTest();
    ~StatusParserTest();

private slots:
    void checkTabulation();
    void emptyStatus();
    void strangeStatus();
    void notStarted();
    void idle();
    void busy();
    void index();
    void busy2();
    void index2();

private:
    StatusParser m_parser;
    static const char* indexStatusWithSyncProgress;
    static const char* busyStatusWithSyncProgress;
    static const char* indexStatus;
    static const char* busyStatus;
    static const char* idleStatus;
};

const char* StatusParserTest::indexStatusWithSyncProgress = R"(
Sync progress: 0 B/ 775.55 KB (0 %)
Synchronization core status: index
Path to Yandex.Disk directory: '/home/bravikov/Yandex.Disk'
	Total: 16.02 GB
	Used: 14.04 GB
	Available: 1.98 GB
	Max file size: 50 GB
	Trash size: 9.26 MB

Last synchronized items:
	file: 'Projects/Programs/yandex-disk-gui/src/status-parser.h'
	file: 'Projects/Programs/yandex-disk-gui/tests/tst_statusparser.cpp'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tests'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/status-parser.o'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/Makefile'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tst_statusparser.o'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/target_wrapper.sh'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tst_statusparser.moc'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/.qmake.stash'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/moc_predefs.h'

)";

const char* StatusParserTest::busyStatusWithSyncProgress = R"(
Sync progress: 7.12 KB/ 10.70 KB (66 %)
Synchronization core status: busy
Path to Yandex.Disk directory: '/home/bravikov/Yandex.Disk'
	Total: 16.02 GB
	Used: 14.04 GB
	Available: 1.98 GB
	Max file size: 50 GB
	Trash size: 9.20 MB

Last synchronized items:
	file: 'Projects/Programs/yandex-disk-gui/.git/index'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/3a/1c8acff3d05b695c552ad1515d41dc72b5f637'
	file: 'Projects/Programs/yandex-disk-gui/.git/logs/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/src/YandexDisk.h'
	file: 'Projects/Programs/yandex-disk-gui/src/YandexDisk.cpp'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/02/56d755c3846a0493c0f05c36eb98eab68614ac'
	file: 'Projects/Programs/yandex-disk-gui/.git/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/42/afd938a6b9dc7e01bd9f2b74815bf33191b3fa'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/56/07cf4581ddf03e25ea62be7da1a14b3b492e42'
	directory: 'Projects/Programs/yandex-disk-gui/.git/objects/56'

)";

const char* StatusParserTest::indexStatus = R"(
Synchronization core status: index
Path to Yandex.Disk directory: '/home/bravikov/Yandex.Disk'
	The quota has not been received yet.
Last synchronized items:
	file: 'Projects/Programs/yandex-disk-gui/.git/gitk.cache'
	file: 'Projects/Programs/yandex-disk-gui/.git/logs/HEAD'
	file: 'Projects/Programs/yandex-disk-gui/.git/logs/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/.git/index'
	file: 'Projects/Programs/yandex-disk-gui/.git/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/69/332fcac00ccebabf58b23d488b5958dea7f724'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/76/f70933cfbbf7c6e60719f98f9e2f90aefd87cd'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/10/2b3b7ce413aa28ccab716ae2f53c576297340c'
	directory: 'Projects/Programs/yandex-disk-gui/.git/objects/76'
	directory: 'Projects/Programs/yandex-disk-gui/.git/objects/69'

)";

const char* StatusParserTest::busyStatus = R"(
Synchronization core status: busy
Path to Yandex.Disk directory: '/home/bravikov/Yandex.Disk'
	The quota has not been received yet.
Last synchronized items:
	file: 'Projects/Programs/yandex-disk-gui/.git/gitk.cache'
	file: 'Projects/Programs/yandex-disk-gui/.git/logs/HEAD'
	file: 'Projects/Programs/yandex-disk-gui/.git/logs/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/.git/index'
	file: 'Projects/Programs/yandex-disk-gui/.git/refs/heads/master'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/69/332fcac00ccebabf58b23d488b5958dea7f724'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/76/f70933cfbbf7c6e60719f98f9e2f90aefd87cd'
	file: 'Projects/Programs/yandex-disk-gui/.git/objects/10/2b3b7ce413aa28ccab716ae2f53c576297340c'
	directory: 'Projects/Programs/yandex-disk-gui/.git/objects/76'
	directory: 'Projects/Programs/yandex-disk-gui/.git/objects/69'

)";

const char* StatusParserTest::idleStatus = R"(
Synchronization core status: idle
Path to Yandex.Disk directory: '/home/bravikov/Yandex.Disk'
	Total: 16.02 GB
	Used: 14.04 GB
	Available: 1.98 GB
	Max file size: 50 GB
	Trash size: 9.26 MB

Last synchronized items:
	file: 'Projects/Programs/yandex-disk-gui/tests/tst_statusparser.cpp'
	file: 'Projects/Programs/yandex-disk-gui/src/status-parser.h'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tests'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/status-parser.o'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/Makefile'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tst_statusparser.o'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/target_wrapper.sh'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/tst_statusparser.moc'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/.qmake.stash'
	file: 'Projects/Programs/yandex-disk-gui/build-tests-Qt_5_9_5-Debug/moc_predefs.h'

)";

void StatusParserTest::checkTabulation()
{
    QVector<QString> statuses{
        indexStatusWithSyncProgress,
        busyStatusWithSyncProgress,
        indexStatus,
        busyStatus,
        idleStatus,
    };

    for (const auto& status: statuses) {
        QVERIFY2(status.contains('\t'), status.toStdString().c_str());
    }
}

StatusParserTest::StatusParserTest()
{}

StatusParserTest::~StatusParserTest()
{}

void StatusParserTest::emptyStatus()
{
    const auto status = m_parser.parse("");
    QTRY_COMPARE(status.syncStatus, SyncStatus::Unknown);
}

void StatusParserTest::strangeStatus()
{
    const auto status = m_parser.parse("aaabbbccc");
    QTRY_COMPARE(status.syncStatus, SyncStatus::Unknown);
}

void StatusParserTest::notStarted()
{
    const auto status = m_parser.parse("Error: daemon not started\n");
    QTRY_COMPARE(status.syncStatus, SyncStatus::NotStarted);
}

void StatusParserTest::idle()
{
    const auto status = m_parser.parse(idleStatus);
    QTRY_COMPARE(status.syncStatus, SyncStatus::Idle);
}

void StatusParserTest::busy()
{
    const auto status = m_parser.parse(busyStatusWithSyncProgress);
    QTRY_COMPARE(status.syncStatus, SyncStatus::Busy);
}

void StatusParserTest::index()
{
    const auto status = m_parser.parse(indexStatusWithSyncProgress);
    QTRY_COMPARE(status.syncStatus, SyncStatus::Index);
}

void StatusParserTest::busy2()
{
    const auto status = m_parser.parse(busyStatus);
    QTRY_COMPARE(status.syncStatus, SyncStatus::Busy);
}

void StatusParserTest::index2()
{
    const auto status = m_parser.parse(indexStatus);
    QTRY_COMPARE(status.syncStatus, SyncStatus::Index);
}

QTEST_APPLESS_MAIN(StatusParserTest)

#include "tst_statusparser.moc"
