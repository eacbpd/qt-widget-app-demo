#include "tablewidget.h"
#include "ui_tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget),
    icofile(":/resource/file.png"),
    icofolder(":/resource/folder.png")
{
    ui->setupUi(this);

    QStringList stringlist;
    stringlist.push_back("FileName");
    stringlist.push_back("LastModify");
    stringlist.push_back("Type");
    stringlist.push_back("Size");
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(stringlist);
    TableAddItem("file1","20171111-111111",0,123412347567);
    TableAddItem("file2","20171111-222222",1,234678);
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::TableAddItem(const QString fname,const QString lmodify,const int type,const quint64 size)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item;
    item = new QTableWidgetItem(fname);
    ui->tableWidget->setItem(row,0,item);

    item = new QTableWidgetItem(lmodify);
    ui->tableWidget->setItem(row,1,item);

    item = new QTableWidgetItem(type==1?icofile:QIcon(),"icon");
    ui->tableWidget->setItem(row,2,item);

    item = new QTableWidgetItem(QString::number(size));
    ui->tableWidget->setItem(row,3,item);
}
