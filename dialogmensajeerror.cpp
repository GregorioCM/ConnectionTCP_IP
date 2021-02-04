#include "dialogmensajeerror.h"
#include "ui_dialogmensajeerror.h"

DialogMensajeError::DialogMensajeError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMensajeError)
{
    ui->setupUi(this);
}

DialogMensajeError::~DialogMensajeError()
{
    delete ui;
}

void DialogMensajeError::setMensajeError(QString _mensajeError){
    ui->plainTextEditMensajeError->setStyleSheet("color: black");
    ui->plainTextEditMensajeError->setPlainText(_mensajeError);
}
