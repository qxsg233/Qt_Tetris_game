#ifndef NEXTBLOCKTABLEWIDGET_H
#define NEXTBLOCKTABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
class NextBlockTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit NextBlockTableWidget(QWidget *parent = nullptr);
    ~NextBlockTableWidget();
    void updateBlock(int state);
private:
    void updateTable(quint16 *data);
private:
    QTableWidgetItem* mp_items[5][5];
};

#endif // NEXTBLOCKTABLEWIDGET_H
