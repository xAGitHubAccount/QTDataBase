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

//When registration is successful
void regist::userRegistered()
{
    ui->label->setText("registered");
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}

//When registration is denied
void regist::userDeniedRegist()
{
    ui->label->setText("Invalid email/password or email already exists.");
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}


//When back button is clicked goes back to the main screen
void regist::on_pushButton_2_clicked()
{
    ui->emailRegist->setText("");
    ui->passRegist->setText("");
    ui->label->setText("");
    emit backClicked();
}

//When register button is clicked begins user sign up for the database
void regist::on_pushButton_clicked()
{
    QVariantMap newAccount;
    newAccount["Email"] = ui->emailRegist->text();
    newAccount["Username"] = ui->userRegist->text();
    newAccount["Password"] = ui->passRegist->text();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newAccount);
    ui->label->setText("");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    emit confirmClicked(ui->emailRegist->text(), ui->passRegist->text(), jsonDoc);
}

