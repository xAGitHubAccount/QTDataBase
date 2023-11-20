#include "login.h"
#include "ui_login.h"
#include <QJsonDocument>
#include <QJsonObject>

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

void login::on_pushButton_clicked()
{
    emit backClicked();
}

void login::on_update_clicked()
{
    //QVariantMap newAccount = {{ui->emailRegist->text().replace(".",","),QVariantMap{{"Email", ui->emailRegist->text()},{"Username", ui->userRegist->text()},{"Password", ui->passRegist->text()}}}};
    QVariantMap newAccount;
    newAccount["Email"] = ui->emailLogged->text();
    newAccount["Username"] = ui->userLogged->text();
    newAccount["Password"] = ui->changePass->text();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newAccount);
    //ui->label->setText("");
    emit updateClicked(ui->emailLogged->text(), ui->changePass->text(), jsonDoc);
}

