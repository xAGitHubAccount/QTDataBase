#ifndef DBAUTHHANDLER_H
#define DBAUTHHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class DBAuthHandler : public QObject
{
    Q_OBJECT
public:
    explicit DBAuthHandler(QObject *parent = nullptr);
    void setAPIKey(const QString &APIKey);
    void userSignUp(const QString &email, const QString &password, const QJsonDocument jDoc);
    void userSignIn(const QString &email, const QString &password);
public slots:
    //void networkReplyReadyRead();
    void performAuthinticatedDBCall();
    void performAuthinticatedPostData();
    void parseResponse();
    void networkReplyReadyRead();
signals:
    void userSignedIn(QJsonDocument jDoc);
    void userSignedUp();
    void userDeniedSignUp();
private:
    void performPOST(const QString &url, const QJsonDocument &payload);
    QString apiKey;
    QString iDToken;
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    int mode;
    QJsonDocument jsonDoc;
    QString userEmail;
};

#endif // DBAUTHHANDLER_H
