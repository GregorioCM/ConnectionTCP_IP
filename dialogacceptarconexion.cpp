#include "dialogacceptarconexion.h"
#include "ui_dialogacceptarconexion.h"

DialogAcceptarConexion::DialogAcceptarConexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAcceptarConexion)
{
    ui->setupUi(this);
}

DialogAcceptarConexion::~DialogAcceptarConexion()
{
    delete ui;
}

void DialogAcceptarConexion::setDatosConexion(QString _datos){
    ui->plainTextEditDatos->setStyleSheet("color: black");
    ui->plainTextEditDatos->setPlainText(_datos);
}
