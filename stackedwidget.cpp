#include "stackedwidget.h"
#include "ui_stackedwidget.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedWidget)
{
    ui->setupUi(this);

    ui->comboBox->addItem("laji",1);
    ui->comboBox->addItem("lese",2);
    ui->comboBox->addItem("rubbish",2);
    ui->checkBox->setChecked(true);

    connect(ui->pushButton,&QPushButton::clicked,this,&StackedWidget::changepage);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&StackedWidget::changepage);
    connect(ui->pushButton,&QPushButton::clicked,this,&StackedWidget::pushButton1_clicked);
    connect(ui->toolButton,&QPushButton::clicked,this,&StackedWidget::toolButton_clicked);
}

StackedWidget::~StackedWidget()
{
    delete ui;
}

void StackedWidget::changepage()
{
    bool b = ui->page->isVisible();
    ui->page->setVisible(!b);
    ui->page_2->setVisible(b);
    //setCurrentIndex(0)
}

void StackedWidget::pushButton1_clicked(bool checked)
{
    int i=0;
    while(ui->comboBox->itemText(i)!=QString(""))
    {
        qDebug() << ui->comboBox->itemData(i).toString();
        ++i;
    }
}

void StackedWidget::toolButton_clicked()
{
    QMessageBox::information(this,"you have new message","look at me"/*,QMessageBox::StandardButton::Ok*/);
}
