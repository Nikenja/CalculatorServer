#include "server.h"

#include <iostream>
#include <QTcpSocket>
#include <QByteArray>

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
    std::cout << "hi" << std::endl;
}
