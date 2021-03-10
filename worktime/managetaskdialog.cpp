#include "managetaskdialog.h"
#include "ui_managetaskdialog.h"
#include "users.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

ManageTaskDialog::ManageTaskDialog(const QVector<Employee*>& employees, size_t adminId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageTaskDialog)
{
    ui->setupUi(this);

    super = (Supervisor*)employees.at(adminId);

    ui->workers->horizontalHeader()->setStretchLastSection(true);

    QString supervisorDepartment = employees.at(adminId)->getDepartment();
    for(int i = 0; i < employees.size(); i++)
    {
        if(employees.at(i)->position() == Positions::worker && employees.at(i)->getDepartment() == supervisorDepartment)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(users[i].name);
            int row = ui->workers->rowCount();

            ui->workers->setRowCount(row+1);
            ui->workers->setItem(row, 0, newItem);

            QTableWidgetItem *newItemD = new QTableWidgetItem(tr("Не назначена"));
            ui->workers->setItem(row, 1, newItemD);
        }
    }

    readTasks();
}

ManageTaskDialog::~ManageTaskDialog()
{
    delete ui;
}

void ManageTaskDialog::readTasks()
{
    super->readTasks();
    const QList<taskie>& tasks = super->getTasks();

    for (int i = 0; i < tasks.size(); i++)
    {
        if(tasks.at(i).worker.isEmpty())
        {
            QListWidgetItem *newItem = new QListWidgetItem(tasks[i].task);
            ui->tasks->insertItem(0, newItem);
        }

        for(int r = 0; r < ui->workers->rowCount(); r++)
            if(tasks[i].worker == ui->workers->item(r, 0)->text())
                ui->workers->item(r, 1)->setText(tasks[i].task);
    }
}

// Распределяем задания автоматически
void ManageTaskDialog::on_pushButton_clicked()
{
    for(int i = 0; i < ui->workers->rowCount(); i++)
    {
        if(ui->workers->item(i, 1)->text() == "Не назначена")
        {
            QString task;
            if(ui->tasks->count() > 0)
            {
                task = ui->tasks->takeItem(0)->text();
                ui->workers->item(i, 1)->setText(task);

                super->setTaskWorker(task, ui->workers->item(i, 0)->text());
            }
        }
    }

    super->saveTasks();
}
