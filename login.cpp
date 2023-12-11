#include "login.h"
#include "ui_login.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

//Sets up login screen data from database based on user that logged in
void login::userLoggedIn(QJsonDocument jDoc)
{
    ui->emailLogged->setText(jDoc.object().value("Email").toString());
    ui->userLogged->setText(jDoc.object().value("Username").toString());
    ui->passLogged->setText(jDoc.object().value("Password").toString());
}

//Changes password of user account and updates the database as well
void login::changePassLogged()
{
    ui->passLogged->setText(ui->changePass->text());
    QVariantMap newAccount;
    newAccount["Email"] = ui->emailLogged->text();
    newAccount["Username"] = ui->userLogged->text();
    newAccount["Password"] = ui->changePass->text();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newAccount);
    emit updateClicked(jsonDoc);
    ui->label->setText("Password changed");
    ui->update->setEnabled(true);
}

//Back to main window
void login::on_pushButton_clicked()
{
    emit backClicked();
    ui->label->setText("Logged in successfully!");
    ui->update->setEnabled(true);
}

//When update clicked begins update of user password passed on what was in the line edit
void login::on_update_clicked()
{
    ui->update->setEnabled(false);
    emit updateClick(ui->changePass->text());
}

