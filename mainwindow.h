#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <vector>
// Mis clases
#include "dialogseleccionpuerto.h"
#include "dialogmensajeerror.h"
#include "dialogacceptarconexion.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

Q_SIGNALS:
    void pasarAudio();
    void terminarAudio();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Funciones de la interfaz
    void modificarChat(QString _message);

private slots:
    // Funciones del servidor
    void lanzarServidor();
    void pararServidor();
    void conexionRecibida();
    void desconectar();
    void on_pushButtonSendMessage_clicked();
    void leerMensaje();
    void on_lineEditMessage_returnPressed(){}
    // Acciones de la barra de navegacion
    // Pasar a audio
    void solicitarCambioAudio();
    void pasadoAudio();
    void datosUdpRecibidos();
    void activarCaptacionAudio();
    void terminadoAudio();
private:
    Ui::MainWindow *ui;
    QTcpServer *pMyServer;
    QTcpSocket *pTcpConexion;
    QUdpSocket *pUdpConexion;
    vector<QTcpSocket *> conexionesActivas;
};
#endif // MAINWINDOW_H
