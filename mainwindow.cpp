#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbauthhandler.h"
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Set up
    ui->setupUi(this);
    reg = new regist;
    log = new login;
    authHandler = new DBAuthHandler();
    setWindowTitle("Test");

    ui->stacked->addWidget(log);
    ui->stacked->addWidget(reg);

    //Set up signals and slots
    //Register screen signals
    connect(reg, SIGNAL(backClicked()), this, SLOT(goHome()));
    connect(reg, SIGNAL(confirmClicked(QString,QString,QJsonDocument)), this, SLOT(confirmUserSignUp(QString,QString,QJsonDocument)));

    //Login screen signals
    connect(log, SIGNAL(backClicked()), this, SLOT(goHome()));
    connect(log, SIGNAL(updateClicked(QJsonDocument)), this, SLOT(updateData(QJsonDocument)));
    connect(log, SIGNAL(updateClick(QString)), this, SLOT(updatePass(QString)));

    //Authenticator handler signals
    connect(authHandler, SIGNAL(userSignedIn(QJsonDocument)), this, SLOT(goLogin(QJsonDocument)));
    connect(authHandler, SIGNAL(userDeniedSignIn()), this, SLOT(deniedLogin()));
    connect(authHandler, SIGNAL(userSignedUp()), this, SLOT(goRegist()));
    connect(authHandler, SIGNAL(userDeniedSignUp()), this, SLOT(goDeniedRegist()));
    connect(authHandler, SIGNAL(changedPass()), this, SLOT(loginChangePass()));
}

//Decon
MainWindow::~MainWindow()
{
    delete ui;
}

//When login button is clicked
void MainWindow::on_loginButton_clicked()
{
    authHandler->userSignIn(ui->user->text(), ui->pass->text());
    ui->loginButton->setEnabled(false);
    ui->registButton->setEnabled(false);
}

//Go to logged in screen when successful authentication login
void MainWindow::goLogin(QJsonDocument jDoc)
{
    ui->stacked->setCurrentWidget(log);
    log->userLoggedIn(jDoc);
    ui->loginButton->setEnabled(true);
    ui->registButton->setEnabled(true);
}

//Login denied
void MainWindow::deniedLogin()
{
    ui->label_3->setText("Incorrect username or password");
    ui->loginButton->setEnabled(true);
    ui->registButton->setEnabled(true);
}

void MainWindow::loginChangePass()
{
    log->changePassLogged();
}

//Go to register button when register button is clicked
void MainWindow::on_registButton_clicked()
{
    ui->stacked->setCurrentWidget(reg);
}

void MainWindow::confirmUserSignUp(QString user, QString pass, QJsonDocument jDoc)
{
    authHandler->userSignUp(user,pass,jDoc);
}

//Slot to change the password of an account
void MainWindow::updatePass(QString pass)
{
    authHandler->performAuthinticatedChangePass(pass);
}

//Change data in database
void MainWindow::updateData(QJsonDocument jDoc)
{
    authHandler->performAuthinticatedPutData(jDoc);
}

void MainWindow::goRegist()
{
    reg->userRegistered();
}

void MainWindow::goDeniedRegist()
{
    reg->userDeniedRegist();
}

void MainWindow::goHome()
{
    ui->stacked->setCurrentIndex(0);
}

