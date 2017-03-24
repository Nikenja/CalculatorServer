#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject{
    Q_OBJECT
public:
    explicit Server(int port, QObject *parent = 0);
private:
    QTcpServer *server;
signals:

public slots:
    void newConnection();
    void readClientRequest();
};

#endif // SERVER_H
