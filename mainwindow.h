#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <login.h>
#include <regist.h>
#include "dbauthhandler.h"
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    DBAuthHandler *authHandler;
    ~MainWindow();

public slots:

private slots:
    void confirmUserSignUp(QString, QString, QJsonDocument);
    void updatePass(QString);
    void updateData(QJsonDocument);
    void on_loginButton_clicked();
    void on_registButton_clicked();
    void goHome();
    void goLogin(QJsonDocument jDoc);
    void goRegist();
    void goDeniedRegist();

private:
    Ui::MainWindow *ui;
    login *log;
    regist *reg;
};
#endif // MAINWINDOW_H
