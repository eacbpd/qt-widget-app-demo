#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QDir>

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = 0);
    ~TreeWidget();
    QTreeWidgetItem *TreeAddItem(const QString fname,const QString lmodify,const int type,const quint64 size,QTreeWidgetItem *parent=nullptr);
private:
    Ui::TreeWidget *ui;
    QPixmap icofile,icofolder;
};

#endif // TREEWIDGET_H
