#include "widget.h"
#include "ui_widget.h"
#include "tetristablewidget.h"
#include <QMessageBox>
#include <QRandomGenerator>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_nextBlockState = (QRandomGenerator::global()->bounded(10))*4;
    ui->tableWidget_next->updateBlock(m_nextBlockState);
    connect(ui->pushButton_start, &QPushButton::clicked, this, &Widget::slot_pushButton_start_onClicked);
    connect(ui->pushButton_down, &QPushButton::clicked, this, &Widget::slot_pushButton_down_onClicked);
    connect(ui->pushButton_left, &QPushButton::clicked, this, &Widget::slot_pushButton_left_onClicked);
    connect(ui->pushButton_right, &QPushButton::clicked, this, &Widget::slot_pushButton_right_onClicked);
    connect(ui->pushButton_revolve, &QPushButton::clicked, this, &Widget::slot_pushButton_revolve_onClicked);
    connect(ui->tableWidget, &TetrisTableWidget::signal_out_keyPress_up, this, &Widget::slot_pushButton_revolve_onClicked);
    connect(ui->tableWidget, &TetrisTableWidget::signal_out_keyPress_down, this, &Widget::slot_pushButton_down_onClicked);
    connect(ui->tableWidget, &TetrisTableWidget::signal_out_keyPress_left, this, &Widget::slot_pushButton_left_onClicked);
    connect(ui->tableWidget, &TetrisTableWidget::signal_out_keyPress_right, this, &Widget::slot_pushButton_right_onClicked);
    connect(&m_timer, &QTimer::timeout, this, &Widget::slot_timer_timeout);
    mp_tableValue = new quint16[TABLE_ROW_COUNT]{0};
    mp_tableValue[TABLE_ROW_COUNT-1] = 0x01<<(TABLE_COLUMN_COUNT/2-1);
    init();
    // ui->tableWidget->updateTable(mp_tableValue);
    // m_actBlock.updateNewBlock();
    // ui->tableWidget->updateTable(m_actBlock.blockValue());
    // m_timer.start(1000);
}

Widget::~Widget()
{
    delete ui;
    delete[] mp_tableValue;
    mp_tableValue = NULL;
}

void Widget::init()
{
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        mp_tableValue[i] = 0x0000;
    }
    m_actBlock.init();
    m_staBlock.init();
    ui->lineEdit_point->setText(QString::number(0));
}

void Widget::slot_pushButton_start_onClicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
        ui->pushButton_start->setText(tr("start"));
    }
    else
    {
        init();
        m_actBlock.updateNewBlock(m_nextBlockState);
        m_nextBlockState = (QRandomGenerator::global()->bounded(10))*4;
        ui->tableWidget_next->updateBlock(m_nextBlockState);
        StaticBlock::mixBlockTable(mp_tableValue, m_actBlock.blockValue(), m_staBlock.blockValue());
        ui->tableWidget->updateTable(mp_tableValue);
        ui->pushButton_start->setText(tr("over"));
        m_timer.start(1000);
    }
    ui->tableWidget->setFocus();
}

void Widget::slot_pushButton_down_onClicked()
{
    if(!m_timer.isActive())
    {
        slot_pushButton_start_onClicked();
        return;
    }
    bool nret = m_actBlock.blockDown();
    if(!nret)
    {
        nret = m_staBlock.appendBlock(m_actBlock.blockValue());
        ui->lineEdit_point->setText(QString::number(m_staBlock.point()));
        if(nret)
        {
            m_timer.stop();
            QMessageBox::information(NULL, tr("Tip"), tr("game over"));
        }
        m_actBlock.updateLimit(m_staBlock.blockValue());
        m_actBlock.updateNewBlock(m_nextBlockState);
        m_nextBlockState = (QRandomGenerator::global()->bounded(10))*4;
        ui->tableWidget_next->updateBlock(m_nextBlockState);
    }
    StaticBlock::mixBlockTable((quint16*)mp_tableValue, (quint16*)m_actBlock.blockValue(), (quint16*)m_staBlock.blockValue());
    ui->tableWidget->updateTable(mp_tableValue);
    ui->tableWidget->setFocus();
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

