#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

enum class Positions : uchar
{
    null,
    admininstrator,
    worker,
    supervisior
};

// Структура для описания задачи
struct taskie
{
    QString task;   // описание задачи
    QString dep;    // отдел, которому назначено задание
    QString worker; // рабочий, выполняющий задание
    int done;       // признак того, что задание выполнено
    QString result; // результат выполнения
};

class Employee
{
public:
    Employee(QString fio, Positions _postion, size_t uniqueNumber,
             QString login, QString password, QString department);
    virtual ~Employee();

    size_t getNumber() const;
    QString getName() const;
    bool checkCredentials(const QString& login, const QString& password) const;

    Positions position() const;
    QString getDepartment();

private:
    QString _fio;
    Positions _postion;

    size_t _uniqueNumber;

    QString _login;
    QString _password;

    QString _departement;
};

#endif // EMPLOYEE_H
