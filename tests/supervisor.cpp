#include "supervisor.h"

Supervisor::Supervisor(QString fio, size_t uniqueNumber, QString login, QString password, QString department)
    : Employee(fio, Positions::supervisior, uniqueNumber, login, password, department)
{

}

Supervisor::~Supervisor()
{

}

void Supervisor::readTasks()
{
    QFile tasksFile("tasks.txt");
    if(tasksFile.open(QFile::ReadOnly))
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

            if (t.dep == this->getDepartment())
                tasks.push_front(t);
        }

        tasksFile.close();
    }
}

void Supervisor::saveTasks()
{
    QFile tasksFile("tasks.txt");
    tasksFile.open(QIODevice::WriteOnly);

    if (!tasksFile.isOpen())
    {
        return;
    }

    QTextStream out(&tasksFile);

    QList<taskie>::Iterator it = tasks.begin();
    for (; it != tasks.end(); it++)
    {
        taskie& current = *it;
        out << current.task << '\n' << current.dep << '\n'
            << current.worker << '\n' << current.done <<'\n' << current.result << '\n';
    }

    tasksFile.close();
}

void Supervisor::setTaskWorker(const QString& _task, const QString& _worker)
{
    QList<taskie>::iterator it = tasks.begin();
    for (; it != tasks.end(); it++)
    {
        if ((*it).task == _task)
        {
            (*it).worker = _worker;
            saveTasks();

            return;
        }
    }
}

const QList<taskie> &Supervisor::getTasks()
{
    return this->tasks;
}
