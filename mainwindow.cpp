#include "mainwindow.h"
#include "ui_mainwindow.h"

//  Mensajes cambio a audio
QString solicitarCAProtocolo= "101AU";
QString acceptarCAProtocolo = "101OK";
QString rechazarCAProtocolo = "101RE";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMyServer = nullptr;
    pTcpConexion = nullptr;
    pUdpConexion = nullptr;
    connect(ui->actionLanzarServidor, SIGNAL(triggered()), SLOT(lanzarServidor()));
    connect(ui->actionPasarAudio, SIGNAL(triggered()), SLOT(solicitarCambioAudio()));
    connect(this, SIGNAL(pasarAudio()), SLOT(pasadoAudio()));
    connect(this, SIGNAL(terminarAudio()), SLOT(terminadoAudio()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//              Modificar interfaz
void MainWindow::modificarChat(QString _mensaje){
    ui->textBrowserChat->setText(ui->textBrowserChat->toPlainText() + _mensaje);
}

//              Funciones privadas del servidor
void MainWindow::lanzarServidor(){
    int puerto = -1;
    if(pMyServer == nullptr){
        DialogSeleccionPuerto seleccionPuerto(this);
        if(seleccionPuerto.exec() == QDialog::Accepted && seleccionPuerto.getPuerto() != -1){
            puerto = seleccionPuerto.getPuerto();
        }
    }
    if(puerto != -1){
        pMyServer = new QTcpServer();
        connect(pMyServer, SIGNAL(newConnection()), SLOT(conexionRecibida()));
        pMyServer->listen(QHostAddress::AnyIPv4, static_cast<quint16>(puerto));
    } else {
        QString mensaje = "Por favor introduzca un puerto para configurar el servidor.";
        DialogMensajeError mensajeError(this);
        mensajeError.setMensajeError(mensaje);
        mensajeError.exec();
    }
}

void MainWindow::pararServidor(){

}

void MainWindow::conexionRecibida(){
    pTcpConexion = pMyServer->nextPendingConnection();
    QString datosConexion = "Nueva conexion cuyo nombre es: " + pTcpConexion->peerName() +
            " con direccion IP: " + pTcpConexion->peerAddress().toString();
    DialogAcceptarConexion aceptar(nullptr);
    aceptar.setDatosConexion(datosConexion);
    if(aceptar.exec() == QDialog::Accepted){
        connect(pTcpConexion, SIGNAL(readyRead()), this, SLOT(leerMensaje()));
        connect(pTcpConexion, SIGNAL(disconnected()), this, SLOT(desconectar()));
        QHostAddress direcionConexion = pTcpConexion->peerAddress();
        QString mensajeConexion;
        if(ui->textBrowserChat->toPlainText() != 0){
            QString separacion = "\n----------------------------------------------------------------";
            this->modificarChat(separacion);
            mensajeConexion = "\nCliente: " + pTcpConexion->peerName() + "\tCon IP: " + direcionConexion.toString();
        } else {
            mensajeConexion = "Cliente: " + pTcpConexion->peerName() + "\tCon IP: " + direcionConexion.toString();
        }
        this->modificarChat(mensajeConexion);
    } else {
        pTcpConexion->close();
        pTcpConexion->deleteLater();
        pTcpConexion = nullptr;
    }
}

void MainWindow::desconectar(){
    QHostAddress direccion = pTcpConexion->peerAddress();
    QString mensajeDesconexion = "\n\nCliente con nombre: " + pTcpConexion->peerName() + " \ty IP: " + direccion.toString()
            + " se ha desconectado.";
    this->modificarChat(mensajeDesconexion);
    pTcpConexion->deleteLater();
    pTcpConexion = nullptr;
}

void MainWindow::on_pushButtonSendMessage_clicked()
{
    QString mensaje = ui->lineEditMessage->text();
    pTcpConexion->write(mensaje.toLatin1());
    if(ui->textBrowserChat->toPlainText() == 0){
        mensaje = " Mensaje enviado a " + pTcpConexion->peerName() + " \tMensaje: " + mensaje;
    } else {
        mensaje = "\nMensaje enviado a " + pTcpConexion->peerName() + "\tMensaje: " + mensaje;
        QString separacion = "\n----------------------------------------------------------------";
        this->modificarChat(separacion);
    }
    this->modificarChat(mensaje);
    ui->lineEditMessage->setText("");
}

void MainWindow::leerMensaje(){;
    QByteArray datos = pTcpConexion->readAll();
    QHostAddress address = pTcpConexion->peerAddress();
    QString mensaje = QString::fromUtf8(datos.toStdString().c_str());
    if(mensaje != solicitarCAProtocolo && mensaje != acceptarCAProtocolo && mensaje != rechazarCAProtocolo){
        if(ui->textBrowserChat->toPlainText() == 0){
            mensaje = "Cliente: " + address.toString() + "\tMensaje: " + QString::fromUtf8(datos.toStdString().c_str());
        } else {
            mensaje = "\nCliente: " + address.toString() + "\tMensaje: " + QString::fromUtf8(datos.toStdString().c_str());
            QString separacion = "\n----------------------------------------------------------------";
            this->modificarChat(separacion);
        }
        this->modificarChat(mensaje);
    } else {
        if(mensaje == solicitarCAProtocolo){
            // se ha recibido una solicitud de cambio a audio
            DialogAcceptarConexion aceptar(nullptr);
            aceptar.setLabelTitulo("Se ha solicitado el cambio a audio");
            aceptar.setDatosConexion("El usuario con nombre: " + pTcpConexion->peerName() + " y direccion IP: "
            + pTcpConexion->peerAddress().toString() + " solicita pasar a audio la conexion");
            this->modificarChat("\nSe ha recibido una solicitud de chat de voz");
            if(aceptar.exec() == QDialog::Accepted) {
                pTcpConexion->write(acceptarCAProtocolo.toLatin1());
                emit pasarAudio();
            } else {
                pTcpConexion->write(rechazarCAProtocolo.toLatin1());
            }
        } else if(mensaje == acceptarCAProtocolo) {
            // la solicitud ha sido aceptada
            this->modificarChat("\nSe ha aceptado la solicitud de chat de voz");
            emit pasarAudio();
        } else{
            // la solicitud fue rechazada
            DialogAcceptarConexion rechadazo(nullptr);
            rechadazo.setLabelTitulo("Solicitud de cambio a audio rechazada");
            rechadazo.setDatosConexion("El usuario con nombre: " + pTcpConexion->peerName() + " y direccion IP: "
            + pTcpConexion->peerAddress().toString() + " ha denegado tu solicitud pasar a audio la conexion");
            rechadazo.exec();
            this->modificarChat("\nLa solicitud de chat de voz ha sido rechazada");
        }
    }
}

//              Acciones

//              Audio
void MainWindow::solicitarCambioAudio(){
    QString inicioAudio = solicitarCAProtocolo;
    pTcpConexion->write(inicioAudio.toLatin1());
    this->modificarChat("\nSe ha solicitado el inicio de chat de voz");
}

void MainWindow::pasadoAudio(){
    pUdpConexion = new QUdpSocket();
    pUdpConexion->bind(pTcpConexion->peerAddress(), pTcpConexion->peerPort());
    connect(pUdpConexion, SIGNAL(readyRead()), SLOT(datosUdpRecibidos()));
    DialogAcceptarConexion rechadazo(nullptr);
    rechadazo.setLabelTitulo("se ha cambiado a audio");
    rechadazo.setDatosConexion("funcion bien");
    rechadazo.exec();
    this->modificarChat("\nSe ha cambiado a audio");
}

void MainWindow::datosUdpRecibidos(){
    if(pUdpConexion->hasPendingDatagrams()){
        QNetworkDatagram datagrama = pUdpConexion->receiveDatagram();
        // Procesamos el datagrama
    }
}

void MainWindow::activarCaptacionAudio(){

}

void MainWindow::terminadoAudio(){

}
