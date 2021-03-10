#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "employee.h"
#include <qlist.h>
#include <qfile.h>
#include <qtextstream.h>

/**
 * @brief Класс Диспетчер
 */
class Supervisor : public Employee
{
public:
    /**
     * @brief Конструктор класса Supervisor
     * @param Фамилия и инициалы диспетчера
     * @param Идентификатор диспетчера
     * @param Логин диспетчера
     * @param Пароль диспетчера
     * @param Отдел, которым управляет
     */
    Supervisor(QString fio, size_t uniqueNumber,
               QString login, QString password, QString department);
    ~Supervisor();
    /**
     * @brief Читает из файла tasks.txt
     */
    void readTasks();
    /**
     * @brief Сохраняет отчёт о работнике в текстовый файл
     */
    void saveTasks();
    /**
     * @brief Выдача работнику задачи
     * @param task название задачи
     * @param worker рабочий, которому выданно задание
     */
    void setTaskWorker(const QString& task, const QString& worker);
    /**
     * @brief Возвращает список задач для отдела
     * @return
     */
    const QList<taskie> &getTasks();

private:
    //! Список задач по отделам и общий список задач
    QList<taskie> tasksDep, tasksAll;
    //! Список рабочих отдела
    QList<Employee*> workers;
};

#endif // SUPERVISOR_H
