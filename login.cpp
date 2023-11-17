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
    ui->userLogged->setText(jDoc.object().value("Username").toString());
    ui->passLogged->setText(jDoc.object().value("Password").toString());
}

void login::on_pushButton_clicked()
{
    emit backClicked();
}

