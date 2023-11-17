#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DBHandler : public QObject
{
    Q_OBJECT
public:
    explicit DBHandler(QObject *parent = nullptr);
    ~DBHandler();

public slots:
    void getRead();
    void networkReplyRead();
    void postData();
    void putData();

signals:

private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
};

#endif // DBHANDLER_H
