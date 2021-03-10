#include "employee.h"

Employee::Employee(QString fio, Positions _position, size_t uniqueNumber, QString login, QString password, QString department)
    : _fio(fio), _postion(_position), _uniqueNumber(uniqueNumber), _login(login), _password(password), _departement(department)
{

}

Employee::~Employee()
{

}

size_t Employee::getNumber() const
{
    return _uniqueNumber;
}

QString Employee::getName() const
{
    return _fio;
}

bool Employee::checkCredentials(const QString &login, const QString &password) const
{
    if (_login == login && _password == password)
    {
        return true;
    }

    return false;
}

Positions Employee::position() const
{
    return _postion;
}

QString Employee::getDepartment()
{
    return _departement;
}
