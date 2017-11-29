#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QWidget>

namespace Ui {
class MyTabWidget;
}

class MyTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTabWidget(QWidget *parent = 0);
    ~MyTabWidget();

private:
    Ui::MyTabWidget *ui;
};

#endif // MYTABWIDGET_H
