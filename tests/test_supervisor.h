#ifndef TEST_SUPERVISOR_H
#define TEST_SUPERVISOR_H

#include <QObject>
#include <QtTest/QtTest>

#include "supervisor.h"
#include "administrator.h"

class test_supervisor : public QObject
{
    Q_OBJECT

public:
    explicit test_supervisor(QObject *parent = nullptr);
    ~test_supervisor();

private slots:
    void testReadTasks();
    //void testSaveTasks();
    void testSetTaskWorker();
    void testGetTasks();

private:
    Supervisor* super = nullptr;
    Administrator* admin = nullptr;
};

#endif // TEST_SUPERVISOR_H
