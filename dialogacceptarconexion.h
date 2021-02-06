#ifndef DIALOGACCEPTARCONEXION_H
#define DIALOGACCEPTARCONEXION_H

#include <QDialog>

namespace Ui {
class DialogAcceptarConexion;
}

class DialogAcceptarConexion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAcceptarConexion(QWidget *parent = nullptr);
    ~DialogAcceptarConexion();

    void setDatosConexion(QString _datos);
    void setLabelTitulo(QString _titulo);
private:
    Ui::DialogAcceptarConexion *ui;
};

#endif // DIALOGACCEPTARCONEXION_H
