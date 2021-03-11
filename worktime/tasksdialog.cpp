#include "tasksdialog.h"
#include "ui_tasksdialog.h"
#include "users.h"

#include <QInputDialog>
#include <QMessageBox>

#include <QFile>
#include <QTextStream>
#include <QDebug>

TasksDialog::TasksDialog(int type, QWidget *parent, Employee* emlpoyee) :
    QDialog(parent),
    ui(new Ui::TasksDialog)
{
    ui->setupUi(this);

    admin = (Administrator*) emlpoyee;

    // 16 задач для всех работников
    ui->tasks->setColumnCount(2);
    ui->tasks->horizontalHeader()->setStretchLastSection(true);

    if(type == 1)
    {
        ui->frame->setVisible(false);
        ui->dep->setVisible(false);

        ui->tasks->setColumnWidth(0, 600);
        setWindowTitle(tr("Создать задачи"));
        ui->label->setText(tr("Создать задачи"));
    }
    else if(type == 2)
    {
        ui->createTask->setVisible(false);
        ui->removeTask->setVisible(false);
        ui->deplabel->setVisible(false);

        ui->tasks->setColumnWidth(0, 400);
        setWindowTitle(tr("Сортировка задач"));
        ui->label->setText(tr("Сортировка задач"));
    }

    admin->readTasks();
    const QList<taskie>* tasks_list = admin->getTask();
    QList<taskie>::const_iterator it = tasks_list->cbegin();

    ui->tasks->clearContents();

    for (; it != tasks_list->cend(); it++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem((*it).task);
        int row = ui->tasks->rowCount();

        ui->tasks->setRowCount(row + 1);
        ui->tasks->setItem(row, 0, newItem);

        QTableWidgetItem *newItemD = new QTableWidgetItem((*it).dep);
        ui->tasks->setItem(row, 1, newItemD);
    }

    ui->tasks->selectRow(0);

    writeInFile();
}

TasksDialog::~TasksDialog()
{
    delete ui;
}

void TasksDialog::positionChanged()
{
    int row = ui->tasks->currentRow();
    if(row < 0) return;

    QString dep;
    if(ui->gamed->isChecked())
    {
        dep = "Геймдизайнеры";
    }
    else if(ui->artists->isChecked())
    {
        dep = "Художники";
    }
    else if(ui->progr->isChecked())
    {
        dep = "Программисты";
    }
    else if(ui->test->isChecked())
    {
        dep = "Тестировщики";
    }

    admin->sortTasks(ui->tasks->item(row, 0)->text(), dep);
    ui->tasks->item(row, 1)->setText(dep);

    writeInFile();
}

void TasksDialog::writeInFile()
{
    int count[4] = {0};

    for(int i = 0; i < ui->tasks->rowCount(); i++)
    {
        QString dep = ui->tasks->item(i, 1)->text();

        if(dep == "Геймдизайнеры")
            count[0]++;
        if(dep == "Художники")
            count[1]++;
        if(dep == "Программисты")
            count[2]++;
        if(dep == "Тестировщики")
            count[3]++;
    }

    ui->bgamed->setText(QString("Геймдизайнеры [%1]").arg(count[0]));
    ui->bartists->setText(QString("Художники [%1]").arg(count[1]));
    ui->bprogr->setText(QString("Программисты [%1]").arg(count[2]));
    ui->btest->setText(QString("Тестировщики [%1]").arg(count[3]));
}

void TasksDialog::on_createTask_clicked()
{
    if(ui->tasks->rowCount() == 16)
    {
        QMessageBox::critical(0, tr("Список задач заполнен"), tr("Список задач не может содержать более 16 задач (по количеству работников"));
        return;
    }
    QString task = QInputDialog::getText(0, tr("Новая задача"), tr("Введите текст новой задачи"));
    if(task.isEmpty())  return;
    QTableWidgetItem *newItem = new QTableWidgetItem(task);
    int row = ui->tasks->rowCount();
    ui->tasks->setRowCount(row+1);
    ui->tasks->setItem(row, 0, newItem);
    QTableWidgetItem *newItemD = new QTableWidgetItem("Не назначен");
    ui->tasks->setItem(row, 1, newItemD);

    admin->addTask(task);
    admin->saveTasks();
}

void TasksDialog::on_removeTask_clicked()
{
    admin->removeTask(ui->tasks->currentItem()->text());

    if(ui->tasks->currentRow() >= 0)
        ui->tasks->removeRow(ui->tasks->currentRow());
}

void TasksDialog::on_test_toggled(bool checked)
{
    if(checked) positionChanged();
}

void TasksDialog::on_progr_toggled(bool checked)
{
    if(checked) positionChanged();
}

void TasksDialog::on_artists_toggled(bool checked)
{
    if(checked) positionChanged();
}

void TasksDialog::on_gamed_toggled(bool checked)
{
    if(checked) positionChanged();
}

void TasksDialog::on_tasks_currentCellChanged(int , int , int , int)
{
    int row = ui->tasks->currentRow();
    if(row < 0) return;

    QString dep = ui->tasks->item(row, 1)->text();
    if(dep == "Геймдизайнеры")
        ui->gamed->setChecked(true);
    else if(dep == "Тестировщики")
        ui->test->setChecked(true);
    else if(dep == "Программисты")
        ui->progr->setChecked(true);
    else if(dep == "Художники")
        ui->artists->setChecked(true);
    else
    {
        ui->gamed->setAutoExclusive(false);
        ui->gamed->setChecked(false);
        ui->gamed->setAutoExclusive(true);
        ui->test->setAutoExclusive(false);
        ui->test->setChecked(false);
        ui->test->setAutoExclusive(true);
        ui->progr->setAutoExclusive(false);
        ui->progr->setChecked(false);
        ui->progr->setAutoExclusive(true);
        ui->artists->setAutoExclusive(false);
        ui->artists->setChecked(false);
        ui->artists->setAutoExclusive(true);
    }
}
