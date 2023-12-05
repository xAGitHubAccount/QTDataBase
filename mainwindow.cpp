#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbauthhandler.h"
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reg = new regist;
    log = new login;
    authHandler = new DBAuthHandler();
    setWindowTitle("Test");
    //pass->setEchoMode(QLineEdit::Password);
    ui->stacked->addWidget(log);
    ui->stacked->addWidget(reg);
    connect(reg, SIGNAL(backClicked()), this, SLOT(goHome()));
    connect(log, SIGNAL(backClicked()), this, SLOT(goHome()));
    connect(reg, SIGNAL(confirmClicked(QString,QString,QJsonDocument)), this, SLOT(confirmUserSignUp(QString,QString,QJsonDocument)));
    connect(log, SIGNAL(updateClicked(QJsonDocument)), this, SLOT(updateData(QJsonDocument)));
    connect(log, SIGNAL(updateClick(QString)), this, SLOT(updatePass(QString)));
    connect(authHandler, SIGNAL(userSignedIn(QJsonDocument)), this, SLOT(goLogin(QJsonDocument)));
    connect(authHandler, SIGNAL(userDeniedSignIn()), this, SLOT(deniedLogin()));
    connect(authHandler, SIGNAL(userSignedUp()), this, SLOT(goRegist()));
    connect(authHandler, SIGNAL(userDeniedSignUp()), this, SLOT(goDeniedRegist()));
    connect(authHandler, SIGNAL(changedPass()), this, SLOT(loginChangePass()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    authHandler->userSignIn(ui->user->text(), ui->pass->text());
}

void MainWindow::confirmUserSignUp(QString user, QString pass, QJsonDocument jDoc)
{
    authHandler->userSignUp(user,pass,jDoc);
}

void MainWindow::updatePass(QString pass)
{
    authHandler->performAuthinticatedChangePass(pass);
}

void MainWindow::updateData(QJsonDocument jDoc)
{
    authHandler->performAuthinticatedPutData(jDoc);
}

void MainWindow::goLogin(QJsonDocument jDoc)
{
    ui->stacked->setCurrentWidget(log);
    log->userLoggedIn(jDoc);
}

void MainWindow::loginChangePass()
{
    log->changePassLogged();
}

void MainWindow::goRegist()
{
    reg->userRegistered();
}

void MainWindow::goDeniedRegist()
{
    reg->userDeniedRegist();
}

void MainWindow::deniedLogin()
{
    ui->label_3->setText("Incorrect username or password");
}

void MainWindow::on_registButton_clicked()
{
    ui->stacked->setCurrentWidget(reg);
}

void MainWindow::goHome()
{
    ui->stacked->setCurrentIndex(0);
}

