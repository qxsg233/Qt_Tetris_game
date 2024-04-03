#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "block.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void slot_pushButton_down_onClicked();
    void slot_pushButton_left_onClicked();
    void slot_pushButton_right_onClicked();
    void slot_pushButton_revolve_onClicked();
private:
    Ui::Widget *ui;
    quint16* mp_tableValue;
    ActiveBlock m_actBlock;
};
#endif // WIDGET_H
