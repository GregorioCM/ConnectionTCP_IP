#include "mysocket.h"

MySocket::MySocket(){
    stopServer = false;
    pMyServer = new QTcpServer();
    connect(pMyServer, SIGNAL(newConnection()), SLOT(newConnection()));
    pMyServer->listen(QHostAddress::AnyIPv4, 7100);
}

void MySocket::run(){
    cout << "Ha entrado en run" << endl;
    do{
        //cout << "Esperando" << endl;
        sleep(5);
        //connect(pMyServer, SIGNAL(NewConnection()), this, SLOT(messageReciever(myServer.nextPendingConnection())));
        if(pMyServer->hasPendingConnections()){
            cout << "tengo conexion" << endl;
            this->newConnection();
        }
    }while(stopServer == false && pMyServer->hasPendingConnections());
}

void MySocket::newConnection(){
    cout << "ha recibido nueva conexion" << endl;
    QTcpSocket *socket = pMyServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}


void MySocket::setPararHilo(bool _stopServer){
    stopServer = _stopServer;
}

void MySocket::read(){
   QTcpSocket *pSender = static_cast<QTcpSocket *>(QObject::sender());
   QByteArray data = pSender->readAll();
   cout << "datos: " << data.toStdString();
}
