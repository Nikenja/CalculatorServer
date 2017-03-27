#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QString>

class Server : public QObject{
    Q_OBJECT
public:
    explicit Server(int port, QObject *parent = 0);
private:
    QTcpServer *server;
    QString calculationExpressionResult(const QString &expression);
    void sendAnswerToClient(QTcpSocket *socket, const QString answer);
    bool isValidExpression(const QString &expression);
    void printMsg(const QString &msg);
    void printInputOutputExpression(const QString &inputExpression, const QString &outputExpression);
public slots:
    void newConnection();
    void readClientRequest();
    void msgClientDisconnect();
};

#endif // SERVER_H
