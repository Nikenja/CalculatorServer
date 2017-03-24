#include "server.h"

#include <iostream>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextStream>
#include <QStringList>

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
}

void Server::readClientRequest(){
    QTcpSocket *socket = nullptr;
    socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr){
        QTextStream inputStream(socket);
        QStringList allInputData("");
        while(socket->bytesAvailable())
             allInputData.append(inputStream.readLine());
        QString resultExression = allInputData.join("");
        calculationExpressionResult(resultExression);
        //проверку на валидность?
    }
    else
        std::cout << "Bad cast" << std::endl;
}

void Server::calculationExpressionResult(const QString &resultExpression){

}

void Server::sendAnswerToClient(){

}
