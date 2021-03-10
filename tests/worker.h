#ifndef WORKER_H
#define WORKER_H

#include "employee.h"

#include <qfile.h>
#include <qtextstream.h>

#include <qlist.h>

class Worker : public Employee
{
public:
    Worker(QString fio, size_t uniqueNumber,
           QString login, QString password, QString department);

    ~Worker();

    QString getTaskName();

    void readTasks();
    void saveTasks();

    void taskDone(const QString& _task);

private:
    QList<taskie> tasks;
};

#endif // WORKER_H
