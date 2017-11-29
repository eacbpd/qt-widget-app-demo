#include "mytabwidget.h"
#include "ui_mytabwidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTabWidget)
{
    ui->setupUi(this);
}

MyTabWidget::~MyTabWidget()
{
    delete ui;
}
