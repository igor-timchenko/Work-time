#include "administrator.h"

Administrator::Administrator(QString fio, size_t uniqueNumber, QString login, QString password, QString department)
    : Employee(fio, Positions::admininstrator, uniqueNumber, login, password, department)
{
    readTasks();
}

Administrator::~Administrator()
{
    saveTasks();
}

void Administrator::readTasks()
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

            if (t.done == 0)
            {
                tasks.push_front(t);
            }
        }

        tasksFile.close();
    }
}

void Administrator::addTask(const QString& name, const QString& dep)
{
    taskie new_taskie = {};
    new_taskie.dep = dep;
    new_taskie.task = name;

    tasks.append(new_taskie);
}

void Administrator::removeTask(const QString &name)
{
//    QList<taskie>::const_iterator it = tasks.cbegin();
//    for (; it != tasks.cend(); it++)
//    {
//        const taskie& current = *it;
//        if ((*it).task == name)
//        {
//            tasks.removeOne(current);
//        }
//    }

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks.at(i).task == name)
        {
            tasks.removeAt(i);
        }
    }
}

void Administrator::saveTasks()
{
    if (tasks.size() > 0)
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

}

void Administrator::sortTasks(const QString &name, const QString &dep)
{
    QList<taskie>::Iterator it = tasks.begin();
    for (; it != tasks.end(); it++)
    {
        if ((*it).task == name)
        {
            (*it).dep = dep;
        }
    }

    saveTasks();
}

const QList<taskie> *Administrator::getTask() const
{
    return &this->tasks;
}
