#include "regist.h"
#include "ui_regist.h"
#include <QJsonDocument>

regist::regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::userRegistered()
{
    ui->label->setText("registered");
}

void regist::userDeniedRegist()
{
    ui->label->setText("Email already exists or invalid email");
}

void regist::on_pushButton_2_clicked()
{
    ui->emailRegist->setText("");
    ui->passRegist->setText("");
    ui->label->setText("");
    emit backClicked();
}


void regist::on_pushButton_clicked()
{
    //QVariantMap newAccount = {{ui->emailRegist->text().replace(".",","),QVariantMap{{"Email", ui->emailRegist->text()},{"Username", ui->userRegist->text()},{"Password", ui->passRegist->text()}}}};
    QVariantMap newAccount;
    newAccount["Email"] = ui->emailRegist->text();
    newAccount["Username"] = ui->userRegist->text();
    newAccount["Password"] = ui->passRegist->text();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newAccount);
    ui->label->setText("");
    emit confirmClicked(ui->emailRegist->text(), ui->passRegist->text(), jsonDoc);
}

