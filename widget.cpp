#include "widget.h"
#include "ui_widget.h"
#include "tetristablewidget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mp_tableValue = new quint16[TABLE_ROW_COUNT]{0};
    ui->tableWidget->updateTable(mp_tableValue);
}

Widget::~Widget()
{
    delete ui;
    delete[] mp_tableValue;
    mp_tableValue = NULL;
}
