// Заголовочный файл класса administrator
#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QFile>
#include <QTextStream>
#include <QList>
#include "employee.h"

/**
 * @brief Класс Администратор
 */
class Administrator : public Employee
{
public:
    /**
     * @brief Конструктор класса Administrator
     * @param Фамилия и инициалы администратора
     * @param Идентификатор администратора
     * @param Логин администратора
     * @param Пароль администратора
     * @param Отдел (равен пустому значению)
     */
    Administrator(QString fio, size_t uniqueNumber,
                  QString login, QString password, QString department = "");

    ~Administrator();
    /**
     * @brief Читает из файла tasks.txt
     */
    void readTasks();
    /**
     * @brief Добавляет задачу, созданную администратором
     * @param name название задачи
     * @param dep отдел, для которого создана данная задача
     */
    void addTask(const QString& name, const QString& dep = "");
    /**
     * @brief Удаляет задачу
     * @param name название задачи
     */
    void removeTask(const QString&name);
    /**
     * @brief  Сохраняет отчёт о работнике в текстовый файл
     */
    void saveTasks();
    /**
     * @brief Выбираем отдел, который будет решать данную задачу
     * @param name название задачи
     * @param dep отдел, которому назначена задача
     */
    void sortTasks(const QString& name, const QString& dep);
    /**
     * @brief Возвращает список созданных задач
     * @return Список созданных задач
     */
    const QList<taskie> *getTask() const;
private:
    //! Список задач
    QList<taskie> tasks;
};

#endif // ADMINISTRATOR_H
