#include "server.h"

#include <iostream>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextStream>
#include <QStringList>
#include "expressionvalidator.h"
#include "calculator.h"

Server::Server(int port, QObject *parent) : QObject(parent){
    this->server = new QTcpServer(this);
    if(server->listen(QHostAddress::Any, port)){
        std::cout << "Server start on port:" << port << std::endl;
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }
    else
        std::cerr << "Server not start on port:" << port << std::endl;
}

void Server::newConnection(){
    QTcpSocket *socket = this->server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readClientRequest()));
    std::cout << "Новое подключние" << std::endl;
}

void Server::readClientRequest(){
    QTcpSocket *socket = nullptr;
    socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr){
        QTextStream inputStream(socket);
        QStringList allInputData("");
        while(socket->bytesAvailable())
             allInputData.append(inputStream.readAll());
        QString resultExression = allInputData.join("");
        if(isValidExpression(resultExression))
            sendAnswerToClient(socket,calculationExpressionResult(resultExression));
        else
            sendAnswerToClient(socket,"Некорректный ввод");
    }
    else
        std::cout << "Bad cast" << std::endl;
}

QString Server::calculationExpressionResult(const QString &expression){
    Calculator calculator;
    return calculator.calculateExression(expression);
}

void Server::sendAnswerToClient(QTcpSocket *socket, const QString answer){
    QByteArray outData(answer.toUtf8());
    socket->write(outData);
}

bool Server::isValidExpression(const QString &expression){
    ExpressionValidator expressionValidator;
    return expressionValidator.isCorrectExpression(expression);
}
