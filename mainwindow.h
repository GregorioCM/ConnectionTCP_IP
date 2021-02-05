#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Funciones de la interfaz
    void modificarChat(QString _message);
    // Funciones del servidor
    void lanzarServidor();
    void pararServidor();
    void conexionRecibida();
    void desconectar();
    void on_pushButtonSendMessage_clicked();
    void leerMensaje();
    void on_lineEditMessage_returnPressed(){}
    // Acciones de la barra de navegacion
private:
    Ui::MainWindow *ui;
    QTcpServer *pMyServer;
    QTcpSocket *pConexion;
    vector<QTcpSocket *> conexionesActivas;
};
#endif // MAINWINDOW_H
