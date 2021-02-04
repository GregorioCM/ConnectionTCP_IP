#ifndef DIALOGSELECCIONPUERTO_H
#define DIALOGSELECCIONPUERTO_H

#include <QDialog>

namespace Ui {
class DialogSeleccionPuerto;
}

class DialogSeleccionPuerto : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeleccionPuerto(QWidget *parent = nullptr);
    ~DialogSeleccionPuerto();
    int getPuerto(){ return puerto; }

private slots:
    void verify();

private:
    Ui::DialogSeleccionPuerto *ui;
    int puerto;
};

#endif // DIALOGSELECCIONPUERTO_H
