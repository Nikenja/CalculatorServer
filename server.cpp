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
    connect(socket, SIGNAL(disconnected()), this, SLOT(msgClientDisconnect()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readClientRequest()));
    std::cout << "New connection" << std::endl;
}

void Server::readClientRequest(){
    QTcpSocket *socket = nullptr;
    socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr){
        QTextStream inputStream(socket);
        QStringList allInputData("");
        while(socket->bytesAvailable())
             allInputData.append(inputStream.readAll());
        QString inputExpression = allInputData.join("");
        if(isValidExpression(inputExpression)){
            QString outputExpression = calculationExpressionResult(inputExpression);
            printInputOutputExpression(inputExpression,outputExpression);
            sendAnswerToClient(socket,outputExpression);
        }
        else
            sendAnswerToClient(socket,"Invalid input");
    }
    else
        std::cerr << "Bad cast" << std::endl;
}

QString Server::calculationExpressionResult(const QString &expression){
    Calculator calculator;
    return calculator.calculateExression(expression);
}

void Server::sendAnswerToClient(QTcpSocket *socket, const QString answer){
    QByteArray outData = QByteArray::fromStdString(answer.toStdString());
    socket->write(outData);
}

bool Server::isValidExpression(const QString &expression){
    ExpressionValidator expressionValidator;
    return expressionValidator.isCorrectExpression(expression);
}

void Server::msgClientDisconnect(){
    std::cout << "Client disconnect" << std::endl;
}

void Server::printInputOutputExpression(const QString &inputExpression, const QString &outputExpression){
    QString result("Input expression: " + inputExpression + ", Output expression: " + outputExpression);
    printMsg(result);
}

void Server::printMsg(const QString &msg){
    std::cout << msg.toStdString() << std::endl;
}
