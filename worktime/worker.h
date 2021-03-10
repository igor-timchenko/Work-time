#ifndef WORKER_H
#define WORKER_H

#include "employee.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qlist.h>

/**
 * @brief Класс Рабочий
 */
class Worker : public Employee
{
public:
    /**
     * @brief Конструктор класса Worker
     * @param fio фамилия и инициалы рабочего
     * @param uniqueNumber идентификатор рабочего
     * @param login логин рабочего
     * @param password пароль рабочего
     * @param department отдел, в котором работает рабочий
     */
    Worker(QString fio, size_t uniqueNumber,
           QString login, QString password, QString department);

    ~Worker();
    /**
     * @brief Возвращает название задачи
     * @return Название задачи
     */
    QString getTaskName();
    /**
     * @brief Читает из файла tasks.txt
     */
    void readTasks();
    /**
     * @brief Сохраняет отчёт о работнике в текстовый файл
     */
    void saveTasks();
    /**
     * @brief Изменение состояния задач в выполнено
     * @param Название задачи
     */
    void taskDone(const QString& _task); // 2

private:
    //! Список задач по отделам и общий список задач
    QList<taskie> tasksDep, tasksAll;
};

#endif // WORKER_H
