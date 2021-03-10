#ifndef TEST_WORKER_H
#define TEST_WORKER_H

#include <QObject>
#include <QtTest/QTest>

#include "worker.h"

class test_worker : public QObject
{
    Q_OBJECT
public:
    explicit test_worker(QObject *parent = nullptr);
    ~test_worker();

private slots:
    void testReadTasks();
    void testGetTaskName();
    void testSetTaskDone();

private:
    Worker* worker = nullptr;
};

#endif // TEST_WORKER_H
