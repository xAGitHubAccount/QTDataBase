#include "dbhandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>

DBHandler::DBHandler(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
}

DBHandler::~DBHandler()
{
    networkManager->deleteLater();
}

//get data from db
void DBHandler::getRead()
{
    //get data from db
    networkReply = networkManager->get(QNetworkRequest(QUrl()));
    connect(networkReply, SIGNAL(readyRead()), this, SLOT(networkReplyRead()));
}

void DBHandler::networkReplyRead()
{
    networkReply->readAll();
}

//push/add data
void DBHandler::postData()
{
    QVariantMap newCar;
    newCar["Type"] = "Honda";
    newCar["Color"] = "Black";
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newCar);
    QNetworkRequest newCarRequest((QUrl()));
    newCarRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    //add data to db
    networkManager->post(newCarRequest, jsonDoc.toJson());
}

void DBHandler::putData()
{
    QVariantMap newCar;
    newCar["Type"] = "Honda";
    newCar["Color"] = "Black";
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newCar);
    QNetworkRequest newCarRequest((QUrl()));
    newCarRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    //add data to db
    networkManager->post(newCarRequest, jsonDoc.toJson());
}
