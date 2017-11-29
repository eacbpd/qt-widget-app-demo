#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QString>
#include <QDebug>
#include <QMenu>
#include "mylistdelegate.h"
namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = 0);
    ~ListWidget();
    void OnSwitchButton();
    void OnDbClickItem(QListWidgetItem *item);
    void OnDelItem();
    void OnAddItem();
    void OnListContextMenu(const QPoint &pos);
private:
    Ui::ListWidget *ui;
};

#endif // LISTWIDGET_H
