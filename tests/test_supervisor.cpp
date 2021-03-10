#include "test_supervisor.h"

test_supervisor::test_supervisor(QObject *parent) : QObject(parent)
{
    admin = new Administrator("Test admin", 0, "test", "test");
    super = new Supervisor("Test supervisisor", 1, "super", "super", "Тестировщики");
}

test_supervisor::~test_supervisor()
{
    delete super;
    delete admin;
}

void test_supervisor::testReadTasks()
{
    admin->addTask("test task", "Тестировщики");
    admin->saveTasks();

    super->readTasks();
    QVERIFY(super->getTasks().size() > 0 ? true : false);
}

void test_supervisor::testSetTaskWorker()
{
    super->setTaskWorker("test task", "test worker");
    QVERIFY(super->getTasks().at(0).worker == "test worker" ? true : false);
}

void test_supervisor::testGetTasks()
{
    QVERIFY(super->getTasks().size() > 0);
}
