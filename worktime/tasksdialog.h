#ifndef TASKSDIALOG_H
#define TASKSDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "administrator.h"

namespace Ui {
class TasksDialog;
}
/**
 * @brief Клас для создания и сортировки задач
 */
class TasksDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief TasksDialog
     * @param type
     * @param parent
     */
    explicit TasksDialog(int type, QWidget *parent = nullptr, Employee* = nullptr);
    ~TasksDialog();
    /**
     * @brief positionChanged
     */
    void positionChanged();
    /**
     * @brief writeInFile
     */
    void writeInFile();

private slots:
    /**
     * @brief Кнопка "Создать" задачу
     */
    void on_createTask_clicked();
    /**
     * @brief Кнопка "Удалить" выбранную задачу
     */
    void on_removeTask_clicked();
    /**
     * @brief Назначить задачу тестировщикам
     * @param checked
     */
    void on_test_toggled(bool checked);
    /**
     * @brief Назначить задачу программистам
     * @param checked
     */
    void on_progr_toggled(bool checked);
    /**
     * @brief Назначить задачу художникам
     * @param checked
     */
    void on_artists_toggled(bool checked);
    /**
     * @brief Назначить задачу геймдизайнерам
     * @param checked
     */
    void on_gamed_toggled(bool checked);
    /**
     * @brief on_tasks_currentCellChanged
     * @param currentRow
     * @param currentColumn
     * @param previousRow
     * @param previousColumn
     */
    void on_tasks_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::TasksDialog *ui;
    //!
    Administrator* admin = nullptr;
};

#endif // TASKSDIALOG_H
