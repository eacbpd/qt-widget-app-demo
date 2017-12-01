#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class StackedWidget;
}

class StackedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = 0);
    ~StackedWidget();
    void changepage();
    void pushButton1_clicked(bool checked);
    void toolButton_clicked();
private:
    Ui::StackedWidget *ui;
};

#endif // STACKEDWIDGET_H
