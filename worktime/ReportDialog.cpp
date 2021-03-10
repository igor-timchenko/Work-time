#include "ReportDialog.h"
#include "ui_ReportDialog.h"
#include "users.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

ReportDialog::ReportDialog(const QVector<Employee*>& employees, size_t adminId, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ReportDialog)
{
    ui->setupUi(this);

    workers = &employees;
    admin = employees[adminId];

    QVector<Employee*>::const_iterator it = employees.cbegin();

    if(employees[adminId]->position() == Positions::admininstrator)
    {
        for(; it != employees.cend(); it++)
        {
            Employee& current = **it;
            if(current.position() == Positions::supervisior)
            {
                ui->comboBox->addItem(current.getName());
            }
        }

        tasks = ((Administrator*)admin)->getTask();
    }
    else if(employees[adminId]->position() == Positions::supervisior)
    {
        for(; it != employees.cend(); it++)
        {
            Employee& current = **it;
            if(current.position() == Positions::worker && employees[adminId]->getDepartment() == current.getDepartment())
            {
                ui->comboBox->addItem(current.getName());
            }
        }
    }

    getTasksFromEmployee();
}

ReportDialog::~ReportDialog()
{
    delete ui;
}

void ReportDialog::showResult()
{
    QString currentWorker = ui->comboBox->currentText();

    ui->result->clear();


    QList<taskie>::const_iterator it = tasks->cbegin();

    if(admin->position() == Positions::admininstrator)
    {
        for(; it != tasks->cend(); it++)
        {
            const taskie& current = *it;

            int idFound = 0;
            while(true)
            {
                if (currentWorker == workers->at(idFound)->getName())
                {
                    break;
                }
                else
                {
                    idFound++;
                }
            }

            if (workers->at(idFound)->getDepartment() == current.dep)
            ui->result->append(tr("Отдел: %1\nРаботник: %2\nЗадание: %3\nРезультат: %4\n")
                                .arg(current.dep)
                                .arg(!current.worker.isEmpty() ? current.worker : "Задание не распределено")
                                .arg(current.task)
                                .arg(current.done == 1 ? "Выполнено" : "Не выполнено"));
        }
    }
    else
    {
        for(; it != tasks->cend(); it++)
        {
            const taskie& current = *it;

            if (currentWorker == current.worker)
            {
                ui->result->append(tr("Отдел: %1\nРаботник: %2\nЗадание: %3\nРезультат: %4\n")
                                    .arg(current.dep)
                                    .arg(!current.worker.isEmpty() ? current.worker : "Задание не распределено")
                                    .arg(current.task)
                                    .arg(current.done == 1 ? "Выполнено" : "Не выполнено"));
            }

        }
    }
}

void ReportDialog::on_pushButtonReport_clicked()
{
    showResult();
}

void ReportDialog::getTasksFromEmployee()
{
    if(admin->position() == Positions::admininstrator)
    {
        ((Administrator*)admin)->readTasks();
        tasks = ((Administrator*)admin)->getTask();

    }
    else
    {
        ((Supervisor*)admin)->readTasks();
        tasks = &((Supervisor*)admin)->getTasks();
    }
}
