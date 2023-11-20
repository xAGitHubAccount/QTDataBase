#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QJsonDocument>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    void userLoggedIn(QJsonDocument jDoc);
    ~login();

signals:
    void updateClicked(QString user, QString pass, QJsonDocument jDoc);
    void backClicked();

private slots:
    void on_pushButton_clicked();

    void on_update_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
