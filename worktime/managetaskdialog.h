#ifndef MANAGETASKDIALOG_H
#define MANAGETASKDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QList>
#include "users.h"
#include "supervisor.h"

namespace Ui {
class ManageTaskDialog;
}
/**
 * @brief Класс радачи задач рабочим
 */
class ManageTaskDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор раздачи задач рабочим
     * @param employees вектор сотрудников компании
     * @param adminId идентификатор администратора
     * @param parent
     */
    explicit ManageTaskDialog(const QVector<Employee*>& employees, size_t adminId, QWidget *parent = nullptr);
    ~ManageTaskDialog();
    /**
     * @brief readTasks
     */
    void readTasks();


private slots:
    /**
     * @brief Кнопка "Распределить задачи"
     */
    void on_pushButton_clicked();

private:
    Ui::ManageTaskDialog *ui;

    Supervisor* super = nullptr;
};

#endif // MANAGETASKDIALOG_H
