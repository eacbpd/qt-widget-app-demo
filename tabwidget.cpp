#include "tabwidget.h"
#include "ui_tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&TabWidget::fileexist);
    connect(ui->btnsearch,&QPushButton::clicked,this,&TabWidget::getfilename);
    connect(ui->btnopen,&QPushButton::clicked,this,&TabWidget::openfile);
    connect(ui->btnadd,&QPushButton::clicked,this,&TabWidget::btnadd);
    connect(ui->btndel,&QPushButton::clicked,this,&TabWidget::btndel);
}

TabWidget::~TabWidget()
{
    delete ui;
}


void TabWidget::getfilename()
{
    QString filename = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(filename);
}
void TabWidget::fileexist()
{
    if(0== access( ui->lineEdit->text().toStdString().c_str(),0))
        ui->btnopen->setEnabled(true);
    else
        ui->btnopen->setEnabled(false);
}

void TabWidget::openfile()
{
    ifstream ifs;
    char str[1024];
    ifs.open(ui->lineEdit->text().toStdString().c_str(),ios::in);

    ifs.read(str,sizeof(str));
    while(ifs.gcount()!=0)
    {
    ui->textBrowser->append(str);
    ifs.read(str,sizeof(str));
    }
    ifs.close();
}

void TabWidget::btnadd()
{
    //ui->tabWidget->insertTab(0,new StackedWidget(),"新加入的");
}

void TabWidget::btndel()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}



