#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
#include <QLineEdit>
#include <QJsonDocument>

namespace Ui {
class regist;
}

class regist : public QWidget
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();

public slots:
    void userRegistered();
    void userDeniedRegist();

signals:
    void confirmClicked(QString user, QString pass, QJsonDocument jDoc);
    void backClicked();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::regist *ui;
};

#endif // REGIST_H
