#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AuthorizationDialog;
}

/**
 * @brief Класс авторизации
 */
class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса AuthorizationDialog
     * @param parent
     */
    explicit AuthorizationDialog(QWidget *parent = nullptr);
    ~AuthorizationDialog();
    /**
     * @brief Получение идентификатора пользователя
     * @return Идентификатор пользователя
     */
    int getUserId() const;
    /**
     * @brief Получение логина пользователя
     * @return Логин пользователя
     */
    QString getName() const;
    /**
     * @brief Получение пароля пользователя
     * @return Пароль пользователя
     */
    QString getPass() const;

private slots:
    /**
     * @brief Нажатие на кнопку, для входа в ИС
     */
    void on_ok_clicked();

private:
    Ui::AuthorizationDialog *ui;
    //! Идентдификатор пользователя
    size_t userId;
};

#endif // AUTHORIZATIONDIALOG_H
