#include <QCoreApplication>
#include <QtTest/QTest>

#include "test_administrator.h"
#include "test_supervisor.h"
#include "test_worker.h"

int main(int argc, char *argv[])
{
    freopen("test.log", "w", stdout);
    //QCoreApplication a(argc, argv);

    QTest::qExec(new test_administrator, argc, argv);
    QTest::qExec(new test_supervisor, argc, argv);
    QTest::qExec(new test_worker, argc, argv);

    return 0;
}
