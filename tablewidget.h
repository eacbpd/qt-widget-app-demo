#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();
    void TableAddItem(const QString fname,const QString lmodify,const int type,const quint64 size);
private:
    Ui::TableWidget *ui;
    QPixmap icofile,icofolder;
};

#endif // TABLEWIDGET1_H
