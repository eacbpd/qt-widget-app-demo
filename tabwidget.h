#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <fstream>
//#include <iostream>
#include <unistd.h>
using namespace std;
namespace Ui {
class TabWidget;
}

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = 0);
    ~TabWidget();
    void getfilename();
    void fileexist();
    void openfile();
    void btnadd();
    void btndel();
private:
    Ui::TabWidget *ui;
};

#endif // TABWIDGET_H
