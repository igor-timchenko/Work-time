#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"
#include "users.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);

    userId = -1;
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}

int AuthorizationDialog::getUserId() const
{
    return userId;
}

QString AuthorizationDialog::getName() const
{
    return this->ui->login->text();
}

QString AuthorizationDialog::getPass() const
{
        return this->ui->password->text();
}

// При нажатии кнопки Ok проверяется логин и пароль и в случае корректных данных окно закрывается.
// Если данные неправильные, то пользователю предлагается повторно ввести данные.

void AuthorizationDialog::on_ok_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->password->text();

    if(login.isEmpty())
    {
        ui->error->setText("Введите логин");
        return;
    }

    if(pass.isEmpty())
    {
        ui->error->setText("Введите пароль");
        return;
    }
    accept();
}
