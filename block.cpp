#include "block.h"
#include "tetristablewidget.h"
#include <QDebug>

#define BIT_CLEAR   (0b0000001111111111)

ActiveBlock::ActiveBlock()
{
    mp_blockValue = new quint16[TABLE_ROW_COUNT]{0};
    mp_limitValue = new quint16[TABLE_ROW_COUNT]{0};
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        mp_blockValue[i] = 0x00;
        mp_limitValue[i] = 0x00;
    }
    // qDebug()<<QString("%1").arg(BIT_CLEAR, 16, 2, QLatin1Char('0'))<<sizeof(quint16);
}

ActiveBlock::~ActiveBlock()
{
    delete[] mp_blockValue;
    mp_blockValue = NULL;
    delete[] mp_limitValue;
    mp_limitValue = NULL;
}

void ActiveBlock::updateNewBlock()
{
    m_pos.x = TABLE_COLUMN_COUNT/2-1;
    m_pos.y = TABLE_ROW_COUNT-1;
    m_pos.state = 36;
    updateBlockValue();
}

bool ActiveBlock::blockDown()
{
    if(checkPostion(m_pos.x, m_pos.y-1, m_pos.state))
    {
        m_pos.y = m_pos.y - 1;
        updateBlockValue();
        return true;
    }
    else
    {
        // updateNewBlock();
        return false;
    }
}

void ActiveBlock::blockLeft()
{
    if(checkPostion(m_pos.x+1, m_pos.y, m_pos.state))
    {
        m_pos.x = m_pos.x + 1;
        updateBlockValue();
    }
}

void ActiveBlock::blockRight()
{
    if(checkPostion(m_pos.x-1, m_pos.y, m_pos.state))
    {
        m_pos.x = m_pos.x - 1;
        updateBlockValue();
    }
}

void ActiveBlock::blockRevolve()
{
    int rem = (m_pos.state+1)%4;
    int state = 0;
    if(rem==0)
        state = -3;
    else
        state = 1;
    qDebug()<<m_pos.state<<state;
    if(checkPostion(m_pos.x, m_pos.y, m_pos.state + state))
    {
        m_pos.state = m_pos.state + state;
        updateBlockValue();
    }
}

quint16 *ActiveBlock::blockValue()
{
    return mp_blockValue;
}

void ActiveBlock::updateLimit(quint16 *limitTable)
{
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        mp_limitValue[i] = limitTable[i];
    }
}

void ActiveBlock::printValue()
{
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        qDebug()<<QString("%1").arg(mp_blockValue[i], 10, 2);
    }
}

void ActiveBlock::updateBlockValue()
{
    int xMove = m_pos.x-(TABLE_COLUMN_COUNT/2-1);
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        if(i<=m_pos.y+2&&i>=m_pos.y-2)
        {
            int yMove = i-m_pos.y + 2;
            if(xMove>=0)
            {
                mp_blockValue[i] = (blockTable[m_pos.state][yMove]<<xMove);
            }
            else
            {
                mp_blockValue[i] = blockTable[m_pos.state][yMove]>>(-xMove);
            }
        }
        else
        {
            mp_blockValue[i] = 0x0;
        }
    }
}

bool ActiveBlock::checkPostion(int x, int y, int state)
{
    //检测x轴
    int xMove = x-(TABLE_COLUMN_COUNT/2-1);
    if(xMove>=0)//左移
    {
        for(int i=0; i<blockCheckCount; i++)
        {
            quint16 oldv = blockTable[state][i]<<xMove;
            if(oldv>= (quint16)0x01<<TABLE_COLUMN_COUNT)
                return false;
        }//检测左边界
    }
    else//右移
    {
        for(int i=0; i<blockCheckCount; i++)
        {
            xMove = -xMove;
            quint16 oldv = blockTable[state][i];
            if((oldv&(1<<(xMove-1))) != 0)
                return false;
        }//检测右边界
    }

    //检测y轴
    for(int i=0; i<blockCheckCount; i++)
    {
        quint16 oldv = blockTable[state][i];
        // qDebug()<<i<<QString("0b%1").arg(oldv, 16, 2, QLatin1Char('0'));
        if(oldv>0)
        {
            if(y-(blockCheckCount/2-i)<0)
                return false;
        }//检测底边界
    }

    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        // qDebug()<<i<<m_pos.y;
        if(mp_limitValue[i]!=0)
        {
            for(int j=0; j<blockCheckCount; j++)
            {
                int y = m_pos.y + (j - blockCheckCount/2)-1;
                if(y==i)
                {
                    quint16 temp = blockTable[m_pos.state][j];
                    if(xMove>=0)
                        temp = (BIT_CLEAR)&(temp<<(xMove));
                    else
                        temp = (BIT_CLEAR)&(temp>>(-xMove-1));
                    if((temp&mp_limitValue[i]) != 0)
                    {
                        qDebug()<<QString("test 0b%1 0b%2 i=%3,j=%4").arg(temp, 16, 2, QLatin1Char('0')).arg(mp_limitValue[i], 16, 2, QLatin1Char('0')).arg(i).arg(j);
                        return false;
                    }

                }
            }
        }
    }

    return true;
}

StaticBlock::StaticBlock()
{
    mp_blockValue = new quint16[TABLE_ROW_COUNT]{0};
}

StaticBlock::~StaticBlock()
{
    delete[] mp_blockValue;
    mp_blockValue = NULL;
}

quint16 *StaticBlock::blockValue()
{
    return mp_blockValue;
}

void StaticBlock::appendBlock(quint16 *blockValue)
{
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        if(blockValue[i] == 0)
            continue;
        mp_blockValue[i] = mp_blockValue[i]|blockValue[i];
    }
}

void StaticBlock::mixBlockTable(quint16 *srcTable, quint16 *actTable, quint16 *staTable)
{
    for(int i=0; i<TABLE_ROW_COUNT; i++)
    {
        srcTable[i] = actTable[i]|staTable[i];
    }
}
