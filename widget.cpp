#include "widget.h"
#include "ui_widget.h"
#include "tetristablewidget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_start, &QPushButton::clicked, this, &Widget::slot_pushButton_start_onClicked);
    connect(ui->pushButton_down, &QPushButton::clicked, this, &Widget::slot_pushButton_down_onClicked);
    connect(ui->pushButton_left, &QPushButton::clicked, this, &Widget::slot_pushButton_left_onClicked);
    connect(ui->pushButton_right, &QPushButton::clicked, this, &Widget::slot_pushButton_right_onClicked);
    connect(ui->pushButton_revolve, &QPushButton::clicked, this, &Widget::slot_pushButton_revolve_onClicked);
    connect(&m_timer, &QTimer::timeout, this, &Widget::slot_timer_timeout);
    mp_tableValue = new quint16[TABLE_ROW_COUNT]{0};
    mp_tableValue[TABLE_ROW_COUNT-1] = 0x01<<(TABLE_COLUMN_COUNT/2-1);
    // ui->tableWidget->updateTable(mp_tableValue);
    m_actBlock.updateNewBlock();
    ui->tableWidget->updateTable(m_actBlock.blockValue());
    m_timer.start(1000);
}

Widget::~Widget()
{
    delete ui;
    delete[] mp_tableValue;
    mp_tableValue = NULL;
}

void Widget::slot_pushButton_start_onClicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
    }
    else
    {
        m_timer.start(1000);
    }
}

void Widget::slot_pushButton_down_onClicked()
{
    bool nret = m_actBlock.blockDown();
    if(!nret)
    {
        m_staBlock.appendBlock(m_actBlock.blockValue());
        m_actBlock.updateLimit(m_staBlock.blockValue());
        m_actBlock.updateNewBlock();
    }
    StaticBlock::mixBlockTable((quint16*)mp_tableValue, (quint16*)m_actBlock.blockValue(), (quint16*)m_staBlock.blockValue());
    ui->tableWidget->updateTable(mp_tableValue);
}

void Widget::slot_pushButton_left_onClicked()
{
    m_actBlock.blockLeft();
    StaticBlock::mixBlockTable((quint16*)mp_tableValue, (quint16*)m_actBlock.blockValue(), (quint16*)m_staBlock.blockValue());
    ui->tableWidget->updateTable(mp_tableValue);
}

void Widget::slot_pushButton_right_onClicked()
{
    m_actBlock.blockRight();
    StaticBlock::mixBlockTable((quint16*)mp_tableValue, (quint16*)m_actBlock.blockValue(), (quint16*)m_staBlock.blockValue());
    ui->tableWidget->updateTable(mp_tableValue);
}

void Widget::slot_pushButton_revolve_onClicked()
{
    m_actBlock.blockRevolve();
    StaticBlock::mixBlockTable((quint16*)mp_tableValue, (quint16*)m_actBlock.blockValue(), (quint16*)m_staBlock.blockValue());
    ui->tableWidget->updateTable(mp_tableValue);
}

void Widget::slot_timer_timeout()
{
    slot_pushButton_down_onClicked();
}
