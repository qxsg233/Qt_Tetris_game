#include "nextblocktablewidget.h"
#include <QHeaderView>
#include <QDebug>
#include <QBrush>
#include "block.h"
NextBlockTableWidget::NextBlockTableWidget(QWidget *parent)
    : QTableWidget{parent}
{
    this->setRowCount(5);
    this->setColumnCount(5);
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
    for(int i=0; i<5; i++)
    {
        this->setRowHeight(i, cellWidth);
        for(int j=0; j<5; j++)
        {
            mp_items[i][j] = new QTableWidgetItem();
            this->setItem(5-i-1, 5-j-1, mp_items[i][j]);
        }
    }
}

NextBlockTableWidget::~NextBlockTableWidget()
{
    this->clear();
}

void NextBlockTableWidget::updateBlock(int state)
{
    quint16 temp[5]{0};
    for(int i=0; i<5; i++)
    {
        temp[i] = blockTable[state][i]>>2;
    }
    updateTable(temp);
}

void NextBlockTableWidget::updateTable(quint16 *data)
{
    if(!data)
        return;
    for(int i=0; i<5; i++)
    {
        quint16 tempValue = data[i];
        for(int j=0; j<5; j++)
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
