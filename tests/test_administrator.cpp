#include "test_administrator.h"

test_administrator::test_administrator(QObject *parent) : QObject(parent)
{
    admin = new Administrator("Test admin", 0, "test", "test");
}

test_administrator::~test_administrator()
{
    delete admin;
}

void test_administrator::testReadTasks()
{
    admin->readTasks();
    QVERIFY(admin->getTask()->size() == 0 ? true : false);
}

void test_administrator::testAddTask()
{
    int oldSize = admin->getTask()->size();
    admin->addTask("test task");

    QVERIFY(admin->getTask()->size() > oldSize);
}

void test_administrator::testRemoveTask()
{
    int oldSize = admin->getTask()->size();
    admin->removeTask("test task");

    QVERIFY(admin->getTask()->size() < oldSize);
}
