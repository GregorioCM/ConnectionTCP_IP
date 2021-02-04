#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QTcpServer>
#include "mysocket.h"

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
    void on_actionParar_Hilo_triggered();
    void on_actionIniciar_Hilo_triggered();
private:
    Ui::MainWindow *ui;
    bool stopServer;
    //MySocket *pMyServer;
    QTcpServer *pMyServer;
    QTcpSocket *pConexion;
};
#endif // MAINWINDOW_H
