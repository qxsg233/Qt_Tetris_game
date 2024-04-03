#ifndef TETRISTABLEWIDGET_H
#define TETRISTABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QKeyEvent>
const int TABLE_COLUMN_COUNT = 10;
const int TABLE_ROW_COUNT = 20;

class TetrisTableWidget : public QTableWidget
{
    Q_OBJECT
signals:
    void signal_out_keyPress_up();
    void signal_out_keyPress_down();
    void signal_out_keyPress_left();
    void signal_out_keyPress_right();
public:
    explicit TetrisTableWidget(QWidget *parent = nullptr);
    ~TetrisTableWidget();
    void updateTable(quint16* data);
private:
    void keyPressEvent(QKeyEvent* event);
private:
    QTableWidgetItem* mp_items[TABLE_ROW_COUNT][TABLE_COLUMN_COUNT];
};

#endif // TETRISTABLEWIDGET_H
