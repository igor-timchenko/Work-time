#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
/**
 * @brief Перечисление должностей в данной ИС
 */
enum class Positions : uchar
{
    null,
    admininstrator,
    worker,
    supervisior
};

/**
 * @brief Структура
 */
struct taskie
{
    QString task;   //! Описание задачи
    QString dep;    //! Отдел, которому назначено задание
    QString worker; //! Рабочий, выполняющий задание
    int done;       //! Признак того, что задание выполнено
    QString result; //! Результат выполнения
};
/**
 * @brief Класс пользователя системы
 */
class Employee
{
public:
    /**
     * @brief Конструктор класса Employee
     * @param fio фамилия и инициалы пользователя
     * @param _postion должность пользователя
     * @param uniqueNumber идентификатор пользователя
     * @param login логин пользователя
     * @param password пароль пользователя
     * @param department отдел, к которому принадлежит пользователь
     */
    Employee(QString fio, Positions _postion, size_t uniqueNumber,
             QString login, QString password, QString department);
    virtual ~Employee();
    //! Возвращает идентификатор пользователя
    size_t getNumber() const;
    //! Возвращает фамилию и инициалы пользователя
    QString getName() const;
    /**
     * @brief Функция проверяет логин и пароль на входе в систему
     * @param login логин пользователя
     * @param password пароль пользователя
     * @return истину (данные правильные) или ложь (данные не верные)
     */
    bool checkCredentials(const QString& login, const QString& password) const;

    /**
     * @brief Функция, возвращающая должность пользователя
     * @return Должность пользователя
     */
    Positions position() const;
    /**
     * @brief Функция, возвращающая название отдела пользователя
     * @return Название отдела пользователя
     */
    QString getDepartment();

private:
    //! Фамилия и инициалы пользователя
    QString _fio;
    //! Должность пользователя
    Positions _postion;
    //! Идентификатор пользователя
    size_t _uniqueNumber;
    //! Логин пользователя
    QString _login;
    //! Пароль пользователя
    QString _password;
    //! Отдел, к которому принадлежит пользователь
    QString _departement;
};

#endif // EMPLOYEE_H
