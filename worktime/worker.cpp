#include "worker.h"

Worker::Worker(QString fio, size_t uniqueNumber, QString login, QString password, QString department)
    : Employee(fio, Positions::worker, uniqueNumber, login, password, department)
{

}

Worker::~Worker()
{

}

QString Worker::getTaskName()
{
    if (tasksDep.size() > 0)
        return tasksDep.front().task;

    return "";
}

void Worker::readTasks()
{
    tasksDep.clear();

    QFile tasksFile("tasks.txt");
    if(tasksFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&tasksFile);
        taskie t;

        while(!in.atEnd())
        {
            t.task = in.readLine();
            t.dep = in.readLine();
            t.worker = in.readLine();
            t.done = in.readLine().toInt();
            t.result = in.readLine();

            if (t.worker == this->getName() && t.done == 0)
                tasksDep.push_front(t);
            else
                tasksAll.push_front(t);
        }

        tasksFile.close();
    }
}

void Worker::saveTasks()
{
    QFile tasksFile("tasks.txt");
    tasksFile.open(QIODevice::WriteOnly);

    if (!tasksFile.isOpen())
    {
        return;
    }

    QTextStream out(&tasksFile);

    QList<taskie>::Iterator it = tasksDep.begin();
    for (; it != tasksDep.end(); it++)
    {
        taskie& current = *it;
        out << current.task << '\n' << current.dep << '\n'
            << current.worker << '\n' << current.done <<'\n' << current.result << '\n';
    }

    QList<taskie>::Iterator it1 = tasksAll.begin();
    for (; it1 != tasksAll.end(); it1++)
    {
        taskie& current = *it1;
        out << current.task << '\n' << current.dep << '\n'
            << current.worker << '\n' << current.done <<'\n' << current.result << '\n';
    }

    tasksFile.close();
}

void Worker::taskDone(const QString& _task)
{
    QList<taskie>::iterator it = tasksDep.begin();
    for (; it != tasksDep.end(); it++)
    {
        taskie& currentTask = *it;
        if (currentTask.task == _task && currentTask.worker == this->getName())
        {
            currentTask.done = 1;

            saveTasks();
            return;
        }
    }
}
