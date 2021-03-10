#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "users.h"
#include "administrator.h"

typedef struct _data
{
    int id;         //! уникальный идентификатор пользователя
    QString login;  //! логин
    QString name;   //! фамилия + инициалы
    QString password; //! пароль
    QString position; //! должность
    QString departament; //! отдел (только для рабочих)

} Employees;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/**
 * @brief Класс для главного окна пользователя
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief Считываем задания из файла tasks.txt
     * @return
     */
    bool readTasks();

private slots:
    /**
     * @brief Таймер
     */
    void on_timer();
    /**
     * @brief Кнопка "Выйти" из личного кабинета администратора
     */
    void on_exit_clicked();
    /**
     * @brief Кнопка "Создать задачи"
     */
    void on_createTask_clicked();
    /**
     * @brief Кнопка "Сортировка задач"
     */
    void on_sortTask_clicked();
    /**
     * @brief Кнопка "Выйти" из личного кабинета диспетчера
     */
    void on_exit2_clicked();
    /**
     * @brief Кнопка "Раздать задачи"
     */
    void on_manageTasks_clicked();
    /**
     * @brief Кнопка "Подтвердить задание" у рабочего
     */
    void on_accept_clicked();
    /**
     * @brief Кнопка "Отправить" у рабочего
     */
    void on_send_clicked();
    /**
     * @brief Кнопка "Выйти" из личного кабинета рабочего
     */
    void on_exit3_clicked();
    /**
     * @brief Кнопка "Отчёты" под пользователем диспетчер
     */
    void on_pushButton_2_clicked();
    /**
     * @brief Кнопка "Отчёты" у администратора
     */
    void on_Reports_clicked();
    /**
     * @brief Состояние кнопки "Подтвердить задание"
     * @param arg1 наличие галочки
     */
    void on_checkAccept_stateChanged(int arg1);

private:

    bool showLoginScreen(); //! Проверка на авторизацию
    /**
     * @brief Функция, показывающая главное окно в зависимости от пользователя
     */
    void setupScreenForEmployee();

    bool loadUsers(); //! Загружает данные пользователей
    size_t getEmployee(const QString& login, const QString& password);

private:
    Ui::MainWindow *ui;
    size_t id = 0;

    QVector<Employee*> employees; //! Вектор пользователей

    QList<task> tasksList; //! Список задач
};
#endif // MAINWINDOW_H
