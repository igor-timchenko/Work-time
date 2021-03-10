#ifndef TEST_ADMINISTRATOR_H
#define TEST_ADMINISTRATOR_H

#include <QObject>
#include <QtTest/QTest>

#include "administrator.h"

class test_administrator : public QObject
{
    Q_OBJECT
public:
    explicit test_administrator(QObject *parent = nullptr);
    ~test_administrator();

private slots:
    void testReadTasks();
    void testAddTask();
    void testRemoveTask();

private:
    Administrator* admin = nullptr;
};

#endif // TEST_ADMINISTRATOR_H
