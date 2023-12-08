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

void login::userLoggedIn(QJsonDocument jDoc)
{
    ui->emailLogged->setText(jDoc.object().value("Email").toString());
    ui->userLogged->setText(jDoc.object().value("Username").toString());
    ui->passLogged->setText(jDoc.object().value("Password").toString());
}

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

void login::on_pushButton_clicked()
{
    emit backClicked();
    ui->label->setText("Logged in successfully!");
    ui->update->setEnabled(true);
}

void login::on_update_clicked()
{
    //QVariantMap newAccount;
    //newAccount["Email"] = ui->emailLogged->text();
    //newAccount["Username"] = ui->userLogged->text();
    //newAccount["Password"] = ui->changePass->text();
    //QJsonDocument jsonDoc = QJsonDocument::fromVariant(newAccount);
    ui->update->setEnabled(false);
    emit updateClick(ui->changePass->text());
    //emit updateClicked(jsonDoc);
}

