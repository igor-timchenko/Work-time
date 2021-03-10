#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QFile>
#include <QTextStream>

#include <QList>

#include "employee.h"

class Administrator : public Employee
{
public:
    Administrator(QString fio, size_t uniqueNumber,
                  QString login, QString password, QString department = "");

    ~Administrator();

    void readTasks();

    void addTask(const QString& name, const QString& dep = "");
    void removeTask(const QString&name);

    void saveTasks();

    void sortTasks(const QString& name, const QString& dep);

    const QList<taskie> *getTask() const;

private:
    QList<taskie> tasks;
};

#endif // ADMINISTRATOR_H
