#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "employee.h"

#include <qlist.h>
#include <qfile.h>
#include <qtextstream.h>

class Supervisor : public Employee
{
public:
    Supervisor(QString fio, size_t uniqueNumber,
               QString login, QString password, QString department);
    ~Supervisor();

    void readTasks();
    void saveTasks();

    void setTaskWorker(const QString& task, const QString& worker);

    const QList<taskie> &getTasks();

private:
    QList<taskie> tasks;
};

#endif // SUPERVISOR_H
