#include "dbauthhandler.h"
#include <QJsonObject>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

DBAuthHandler::DBAuthHandler(QObject *parent)
    : QObject{parent}
{
    mode = 0;
    apiKey = "AIzaSyDWONq0OiwfuQ-PLnfhBDCQ1DYehWkSNYE";
    networkManager = new QNetworkAccessManager(this);
    //connect(this, SIGNAL(userSignedIn()), this, SLOT(performAuthinticatedDBCall()));
}

void DBAuthHandler::setAPIKey(const QString &APIKey)
{
    apiKey = APIKey;
}

void DBAuthHandler::userSignUp(const QString &email, const QString &password, const QJsonDocument jDoc)
{
    QString signUpEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + apiKey;
    jsonDoc = jDoc;
    userEmail = email;
    QVariantMap vPayload;
    vPayload["email"] = email;
    vPayload["password"] = password;
    vPayload["returnSecureToken"] = true;
    QJsonDocument jsonPayload = QJsonDocument::fromVariant(vPayload);
    mode = 2;

    performPOST(signUpEndpoint, jsonPayload);
}

void DBAuthHandler::userSignIn(const QString &email, const QString &password)
{
    QString signInEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + apiKey;
    userEmail = email;
    QVariantMap vPayload;
    vPayload["email"] = email;
    vPayload["password"] = password;
    vPayload["returnSecureToken"] = true;

    mode = 1;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant(vPayload);
    performPOST(signInEndpoint, jsonPayload);
}

void DBAuthHandler::performPOST(const QString &url, const QJsonDocument &payload)
{
    QNetworkRequest newRequest((QUrl(url)));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    networkReply = networkManager->post(newRequest, payload.toJson());

    connect(networkReply, SIGNAL(readyRead()), this, SLOT(parseResponse()));
}

void DBAuthHandler::networkReplyReadyRead()
{
    QByteArray response = networkReply->readAll();
    qDebug() << response;
    //parseResponse(response);
}

void DBAuthHandler::parseResponse()
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(networkReply->readAll());
    if(jsonDocument.object().contains("error"))
    {
        if(mode == 1)
        {
        }
        else if(mode == 2)
        {
            emit userDeniedSignUp();
        }
    }
    else if(jsonDocument.object().contains("kind"))
    {
        iDToken = jsonDocument.object().value("idToken").toString();
        if(mode == 1)
        {
            performAuthinticatedDBCall();
            emit userSignedIn(jsonDoc);
        }
        else if(mode == 2)
        {
            performAuthinticatedPostData();
            emit userSignedUp();
        }
    }
    else
    {

    }
    mode = 0;
}

void DBAuthHandler::performAuthinticatedPostData()
{
    qDebug() << userEmail;
    QString endpoint = "https://qttest-122de-default-rtdb.firebaseio.com/users/"+ userEmail.replace(".", ",") + ".json?auth=" + iDToken;
    QNetworkRequest newRequest((QUrl(endpoint)));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    //add data to database
    networkManager->put(newRequest, jsonDoc.toJson());
}

void DBAuthHandler::performAuthinticatedDBCall()
{
    qDebug() << userEmail;
    QString endpoint = "https://qttest-122de-default-rtdb.firebaseio.com/users/" + userEmail.replace(".", ",") + "/.json?auth=" + iDToken;
    networkReply = networkManager->get(QNetworkRequest(QUrl(endpoint)));
    QJsonDocument jsonDocument = QJsonDocument::fromJson(networkReply->readAll());
    qDebug() << networkReply->readAll();
    jsonDoc = jsonDocument;
}
