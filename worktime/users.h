#ifndef USERS_H
#define USERS_H

#include <QString>

/**
 * @brief Структура для описания пользователя системы
 */
struct user
{
    int id;                  //! Уникальный идентификатор пользователя
    QString login;           //! Логин
    QString name;            //! Фамилия + инициалы
    QString password;        //! Пароль
    QString position;        //! Должность
    QString departament;     //! Отдел (только для рабочих)
};


/**
 * @brief Структура для описания задачи
 */
struct task
{
    QString task;   //! Описание задачи
    QString dep;    //! Отдел, которому назначено задание
    QString worker; //! Рабочий, выполняющий задание
    int done;       //! Признак того, что задание выполнено
    QString result; //! Результат выполнения
};

extern user users[21];

#endif // USERS_H
