#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QThread>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

class MySocket : public QThread
{
public:
    MySocket();
    void run() override;
    // Message Reciever
    void newConnection();
    void read();
    // Stop Thread
    void setPararHilo(bool _pararHilo);
private:
    bool stopServer;
    QTcpServer *pMyServer;
};

#endif // MYSOCKET_H
