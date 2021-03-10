#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include <QList>
#include "users.h"
#include "administrator.h"
#include "supervisor.h"

namespace Ui {
class ReportDialog;
}
/**
 * @brief Класс отчётности рабочих
 */
class ReportDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор отчётности рабочих
     * @param employees вектор сотрудников компании
     * @param adminId идентификатор администратора
     * @param parent
     */
    explicit ReportDialog(const QVector<Employee*>& employees, size_t adminId, QWidget *parent = nullptr);
    ~ReportDialog();
    /**
     * @brief Отчёты конкретных рабочих
     */
    void showResult();

private slots:
    /**
     * @brief Кнопка "Получить отчёт"
     */
    void on_pushButtonReport_clicked();

private:
    /**
     * @brief Получение задания от сотрудника
     */
    void getTasksFromEmployee();

private:
    Ui::ReportDialog *ui;
    //! Список задач
    const QList<taskie>* tasks = nullptr;
    //! Вектор рабочих отдела
    const QVector<Employee*>* workers = nullptr;

    Employee* admin = nullptr;
};

#endif // REPORTDIALOG_H
