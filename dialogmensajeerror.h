#ifndef DIALOGMENSAJEERROR_H
#define DIALOGMENSAJEERROR_H

#include <QDialog>

namespace Ui {
class DialogMensajeError;
}

class DialogMensajeError : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMensajeError(QWidget *parent = nullptr);
    ~DialogMensajeError();
    void setMensajeError(QString _mensajeError);

private:
    Ui::DialogMensajeError *ui;
};

#endif // DIALOGMENSAJEERROR_H
