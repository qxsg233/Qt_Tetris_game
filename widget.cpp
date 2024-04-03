#include "widget.h"
#include "ui_widget.h"
#include "tetristablewidget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_down, &QPushButton::clicked, this, &Widget::slot_pushButton_down_onClicked);
    connect(ui->pushButton_left, &QPushButton::clicked, this, &Widget::slot_pushButton_left_onClicked);
    connect(ui->pushButton_right, &QPushButton::clicked, this, &Widget::slot_pushButton_right_onClicked);
    connect(ui->pushButton_revolve, &QPushButton::clicked, this, &Widget::slot_pushButton_revolve_onClicked);
    mp_tableValue = new quint16[TABLE_ROW_COUNT]{0};
    mp_tableValue[TABLE_ROW_COUNT-1] = 0x01<<(TABLE_COLUMN_COUNT/2-1);
    // ui->tableWidget->updateTable(mp_tableValue);
    m_actBlock.updateNewBlock();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
}

Widget::~Widget()
{
    delete ui;
    delete[] mp_tableValue;
    mp_tableValue = NULL;
}

void Widget::slot_pushButton_down_onClicked()
{
    m_actBlock.blockDown();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
}

void Widget::slot_pushButton_left_onClicked()
{
    m_actBlock.blockLeft();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
}

void Widget::slot_pushButton_right_onClicked()
{
    m_actBlock.blockRight();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
}

void Widget::slot_pushButton_revolve_onClicked()
{
    m_actBlock.blockRevolve();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
}
