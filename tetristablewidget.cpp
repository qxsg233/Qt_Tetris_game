#include "tetristablewidget.h"
#include <QHeaderView>
#include <QDebug>
#include <QBrush>
TetrisTableWidget::TetrisTableWidget(QWidget *parent)
    : QTableWidget{parent}
{
    this->setRowCount(TABLE_ROW_COUNT);
    this->setColumnCount(TABLE_COLUMN_COUNT);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::NoSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setShowGrid(true);// 设置网格线可见
    this->setGridStyle(Qt::SolidLine);// 设置网格样式
    // 这会根据QTableWidget的大小自动调整列宽和行高
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int column = 0; column < this->columnCount(); ++column) {
        this->setColumnWidth(column, this->width() / this->columnCount());
    }
    this->resizeColumnsToContents();
    int cellWidth = this->columnWidth(0);
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        this->setRowHeight(i, cellWidth);
        for(int j=0; j<TABLE_COLUMN_COUNT; j++)
        {
            mp_items[i][j] = new QTableWidgetItem();
            this->setItem(TABLE_ROW_COUNT-i-1, TABLE_COLUMN_COUNT-j-1, mp_items[i][j]);
        }
    }
}

TetrisTableWidget::~TetrisTableWidget()
{
    this->clear();
}

void TetrisTableWidget::updateTable(quint16 *data)
{
    if(!data)
        return;
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        quint16 tempValue = data[i];
        for(int j=0; j<TABLE_COLUMN_COUNT; j++)
        {
            quint16 temp = 0x01;
            temp = temp<<j;
            temp = tempValue&temp;
            if(temp==0)
            {
                mp_items[i][j]->setBackground(QBrush(QColor(255,255,255)));
            }
            else
            {
                mp_items[i][j]->setBackground(QBrush(QColor(122, 58, 35)));
            }
        }
    }
}
