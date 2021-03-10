#include "test_worker.h"

test_worker::test_worker(QObject *parent) : QObject(parent)
{
    worker = new Worker("test worker", 2, "worker", "worker", "Тестировщики");
}

test_worker::~test_worker()
{
    delete worker;
}

void test_worker::testReadTasks()
{
    worker->readTasks();
    QVERIFY(worker->getTaskName().isEmpty() ? false : true);
}

void test_worker::testGetTaskName()
{
    QVERIFY(worker->getTaskName().isEmpty() ? false : true);
}

void test_worker::testSetTaskDone()
{
    QString taskName = worker->getTaskName();
    worker->taskDone(taskName);

    QVERIFY(worker->getTaskName().isEmpty() ? true : false);
}
