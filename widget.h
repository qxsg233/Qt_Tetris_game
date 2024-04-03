#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "block.h"
#include <QTimer>
#include <QKeyEvent>
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
    void init();
private slots:
    void slot_pushButton_start_onClicked();
    void slot_pushButton_down_onClicked();
    void slot_pushButton_left_onClicked();
    void slot_pushButton_right_onClicked();
    void slot_pushButton_revolve_onClicked();
    void slot_timer_timeout();
private:
    Ui::Widget *ui;
    quint16* mp_tableValue;
    ActiveBlock m_actBlock;
    StaticBlock m_staBlock;
    QTimer m_timer;
    int m_nextBlockState;
};
#endif // WIDGET_H
