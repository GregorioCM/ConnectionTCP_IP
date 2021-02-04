#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stopServer = false;
    pMyServer = nullptr;
    pConexion = nullptr;
    connect(ui->actionLanzarServidor, SIGNAL(triggered()), SLOT(lanzarServidor()));
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
    pConexion = pMyServer->nextPendingConnection();
    connect(pConexion, SIGNAL(readyRead()), SLOT(leerMensaje()));
    connect(pConexion, SIGNAL(disconnected()), SLOT(desconectar()));
    QHostAddress direcionConexion = pConexion->peerAddress();
    QString mensajeConexion;
    if(ui->textBrowserChat->toPlainText() != 0){
        QString separacion = "\n----------------------------------------------------------------";
        this->modificarChat(separacion);
        mensajeConexion = "\nCliente: " + pConexion->peerName() + "\tCon IP: " + direcionConexion.toString();
    } else {
        mensajeConexion = "Cliente: " + pConexion->peerName() + "\tCon IP: " + direcionConexion.toString();
    }
    this->modificarChat(mensajeConexion);
}

void MainWindow::desconectar(){
    QHostAddress direccion = pConexion->peerAddress();
    QString mensajeDesconexion = "\n\nCliente con nombre: " + pConexion->peerName() + " \ty IP: " + direccion.toString()
            + " se ha desconectado.";
    this->modificarChat(mensajeDesconexion);
    pConexion->deleteLater();
    pConexion = nullptr;
}

void MainWindow::on_pushButtonSendMessage_clicked()
{
    QString mensaje = ui->lineEditMessage->text();
    pConexion->write(mensaje.toLatin1());
    if(ui->textBrowserChat->toPlainText() == 0){
        mensaje = " Mensaje enviado a " + pConexion->peerName() + " \tMensaje: " + mensaje;
    } else {
        mensaje = "\nMensaje enviado a " + pConexion->peerName() + "\tMensaje: " + mensaje;
        QString separacion = "\n----------------------------------------------------------------";
        this->modificarChat(separacion);
    }
    this->modificarChat(mensaje);
    ui->lineEditMessage->setText("");
}

void MainWindow::leerMensaje(){;
    QByteArray datas = pConexion->readAll();
    QHostAddress address = pConexion->peerAddress();
    QString mensaje;
    if(ui->textBrowserChat->toPlainText() == 0){
        mensaje = "Cliente: " + address.toString() + "\tMensaje: " + QString(datas);
    } else {
        mensaje = "\nCliente: " + address.toString() + "\tMensaje: " + QString(datas);
        QString separacion = "\n----------------------------------------------------------------";
        this->modificarChat(separacion);
    }
    this->modificarChat(mensaje);
}

//              Acciones


