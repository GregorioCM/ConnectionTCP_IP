#include "dialogseleccionpuerto.h"
#include "ui_dialogseleccionpuerto.h"

DialogSeleccionPuerto::DialogSeleccionPuerto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeleccionPuerto)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(verify()));
    connect(ui->lineEditPuerto, SIGNAL(returnPressed()), ui->buttonBox, SLOT(accepted()));
}

DialogSeleccionPuerto::~DialogSeleccionPuerto()
{
    delete ui;
}

void DialogSeleccionPuerto::verify(){
    if(ui->lineEditPuerto->text().toStdString() != ""){
        puerto = ui->lineEditPuerto->text().toInt();
    } else {
        puerto = -1;
    }
    accept();
}
