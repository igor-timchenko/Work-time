#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationdialog.h"
#include "tasksdialog.h"
#include "users.h"
#include "managetaskdialog.h"
#include "ReportDialog.h"

#include "administrator.h"
#include "supervisor.h"
#include "worker.h"

#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool isLoaded = loadUsers();
    if (!isLoaded)
    {
        QMessageBox::warning(this, "Warning", "Users file is corrupted or not found!");
        exit(0);
    }

    if (showLoginScreen())
    {
        setupScreenForEmployee();
    }
    else
    {
        exit(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    for (QVector<Employee*>::iterator it = employees.begin(); it != employees.end(); it++)
    {
        delete *it;
    }

    employees.clear();
}


void MainWindow::on_exit_clicked()
{
    setVisible(false);

    id = 0; // reset user

    if (showLoginScreen())
    {
        setVisible(true);
        setupScreenForEmployee();
    }
    else
    {
        exit(0);
    }
}

// Создание задачи
void MainWindow::on_createTask_clicked()
{
    TasksDialog * dia = new TasksDialog(1, this, employees[id]);
    if(dia->exec())
    {

    }
}

void MainWindow::on_sortTask_clicked()
{
    TasksDialog * dia = new TasksDialog(2, this, employees[id]);
    if(dia->exec())
    {

    }
}

void MainWindow::on_exit2_clicked()
{
    setVisible(false);

    id = 0; // reset user

    if (showLoginScreen())
    {
        setVisible(true);
        setupScreenForEmployee();
    }
    else
    {
        exit(0);
    }
}

void MainWindow::on_manageTasks_clicked()
{
    ManageTaskDialog * dia = new ManageTaskDialog(employees, id, this);
    if(dia->exec())
    {

    }
}

void MainWindow::on_timer()
{
    static bool found = false;
    if(!found)
    {
        found = readTasks();
    }
}

bool MainWindow::readTasks()
{
    // Считываем задания из файла
    ui->task->setText(tr("Заданий нет"));
    bool found = false;

    QFile tasks("tasks.txt");
    if(tasks.open(QFile::ReadOnly))
    {
        tasksList.clear();
        QTextStream in(&tasks);
        while(!in.atEnd())
        {
            task t;
            t.task = in.readLine();
            t.dep = in.readLine();
            t.worker = in.readLine();
            t.done = in.readLine().toInt();
            t.result = in.readLine();

            if(t.dep == employees[id]->getDepartment())
            {
                if(!t.done)
                {
                    ui->task->setText(t.task);
                    found = true;
                }
            }
        }

        tasks.close();
    }

    return found;
}

// Потверждение выполнения работы
void MainWindow::on_accept_clicked()
{
    if(!ui->checkAccept->isChecked())
    {
        QMessageBox::critical(0, tr("Ошибка"), tr("Перед нажатием на кнопку Подтвердить необходимо отметить пункт ниже, подтверждающий выполнение задания."));
        return;
    }

    for(int i = 0; i < tasksList.count(); i++)
    {
        task *t = &tasksList[i];

        if(t->task == ui->task->text() && t->worker == users[id].name)
        {
            t->result = ui->result->toPlainText();
            t->done = 1;
            QMessageBox::information(0, tr("Подтверждено"), tr("Вы подтвердили выполнение задания! Нажмите кнопку отправить!"));
            return;
        }
    }
}

void MainWindow::on_send_clicked()
{
    ((Worker*)employees[id])->taskDone(ui->task->text());

    QMessageBox::information(0, tr("Отправлено"), tr("Выполнение задания успешно отправлено!"));
}

void MainWindow::on_exit3_clicked()
{
    setVisible(false);

    id = 0; // reset user

    if (showLoginScreen())
    {
        setVisible(true);
        setupScreenForEmployee();
    }
    else
    {
        exit(0);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ReportDialog * dia = new ReportDialog(employees, id, this);
    if(dia->exec())
    {

    }
}

void MainWindow::on_Reports_clicked()
{
    ReportDialog * dia = new ReportDialog(employees, id, this);
    if(dia->exec())
    {

    }
}

bool MainWindow::loadUsers()
{
    QFile usersData("users.txt");
    usersData.open(QIODevice::ReadOnly);

    if (!usersData.isOpen())
    {
        return false;
    }

    qint64 fileSize = usersData.size();
    if (fileSize == 0)
    {
        return false;
    }

    Employee *data = nullptr;

    QTextStream file(&usersData);

    int id = 0;
    QString login, name, password, position, department;

    while (!file.atEnd())
    {
        id = file.readLine().toInt();
        login = file.readLine();
        name = file.readLine();
        password = file.readLine();
        position = file.readLine();
        department = file.readLine();

        if (position == "Администратор")
        {
            data = new Administrator(name, id, login, password);
        }
        else if (position == "Диспетчер")
        {
            data = new Supervisor(name, id, login, password, department);
        }
        else if (position == "Рабочий")
        {
            data = new Worker(name, id, login, password, department);

        }

        employees.push_back(data);
    }

    usersData.close();

    return true;
}

size_t MainWindow::getEmployee(const QString &_login, const QString &_password)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (employees[i]->checkCredentials(_login, _password))
        {
            return employees[i]->getNumber();
        }
    }

    return 0;
}

void MainWindow::on_checkAccept_stateChanged(int arg1)
{
    bool enabled = false;
    if (arg1 == 0)
    {
        enabled = false;
    }
    else
    {
        enabled = true;
    }

    ui->send->setEnabled(enabled);
}

bool MainWindow::showLoginScreen()
{
    AuthorizationDialog *dia = new AuthorizationDialog(this);

    QString login;
    QString password;

    while (id == 0)
    {
        if (login != "" && password != "" && id ==0)
        {
            QMessageBox::warning(this, "Warning", "Enter true credentials!");
        }
        if (!dia->exec())
        {
            return false;
        }
        else
        {
            login = dia->getName();
            password = dia->getPass();

            id = getEmployee(login, password);
        }
    }

    id--;
    delete dia;

    return true;
}

void MainWindow::setupScreenForEmployee()
{
    ui->tabs->setTabBarAutoHide(true);

    // В зависимости от должности, показываем главное окно
    if(employees[id]->position() == Positions::admininstrator)
    {
        ui->tabs->setTabEnabled(2, false);
        ui->tabs->setTabEnabled(1, false);

        ui->tabs->setTabEnabled(0, true);
        ui->tabs->setCurrentIndex(0);

        ui->name->setText(employees[id]->getName());
        ui->id->setText(QString::number(employees[id]->getNumber()));
    }
    else if(employees[id]->position() == Positions::supervisior)
    {
        ui->tabs->setTabEnabled(2, false);
        ui->tabs->setTabEnabled(0, false);

        ui->tabs->setTabEnabled(1, true);
        ui->tabs->setCurrentIndex(1);

        ui->name2->setText(employees[id]->getName());
        ui->id2->setText(QString::number(employees[id]->getNumber()));
    }
    else if(employees[id]->position() == Positions::worker)
    {
        ui->tabs->setTabEnabled(0, false);
        ui->tabs->setTabEnabled(1, false);

        ui->tabs->setTabEnabled(2, true);
        ui->tabs->setCurrentIndex(2);

        ui->name3->setText(employees[id]->getName());
        ui->id3->setText(QString::number(employees[id]->getNumber()));

        ((Worker*)employees[id])->readTasks(); //загружаем таскы

        QString taskLabel = ((Worker*)employees[id])->getTaskName();
        ui->task->setText(taskLabel);
    }
}
