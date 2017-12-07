#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QHeaderView>
#include <QVariant>
#include <QTableWidgetItem>
TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget),
    icom(":/resource/headm.png"),
    icow(":/resource/headw.png"),
    logPath("./tableData")
{
    ui->setupUi(this);

    QStringList stringlist;
    stringlist.push_back("Name");
    stringlist.push_back("Birtydays");
    stringlist.push_back("Gender");
    stringlist.push_back("QQ");
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(stringlist);


    QHeaderView *headerGoods = ui->tableWidget->horizontalHeader();
    //SortIndicator为水平标题栏文字旁边的三角指示器
    headerGoods->setSortIndicator(0, Qt::AscendingOrder);
    headerGoods->setSortIndicatorShown(true);
    connect(headerGoods, SIGNAL(sectionClicked(int)), ui->tableWidget, SLOT (sortByColumn(int)));

    connect(ui->btnAdd,&QPushButton::clicked,this,&TableWidget::newBlankItem);
    connect(ui->btnDel,&QPushButton::clicked,this,&TableWidget::delCurrentItem);
    connect(ui->btnFresh,&QPushButton::clicked,this,&TableWidget::freshTable);
    connect(ui->btnSave,&QPushButton::clicked,this,&TableWidget::saveTable);
    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&TableWidget::filterChanged);
    loadTable();
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::loadTable()
{
    std::ifstream ifs;
    ifs.open(logPath.c_str());
    People peo;
    ifs>>peo;
    while(ifs)
    {
        TableAddItem(peo.name,peo.birthday,peo.gender,peo.qq);
        ifs>>peo;
    }
    ifs.close();
}

void TableWidget::newBlankItem()
{
    TableAddItem("","","","");
}

void TableWidget::delCurrentItem()
{
    QList<QTableWidgetItem *> qlqt = ui->tableWidget->selectedItems();
    QList<int> qlr;
    for(auto &r:qlqt)
    {
        if(qlr.size()==0)qlr.push_back(r->row());
        for(auto &a:qlr)
        {
            if(r->row() !=a)
            {
                qlr.push_back(r->row());
            }
        }
    }
    if(qlr.size()==0)
    {
        QMessageBox::information(this,"错误","请指定删除位置");
        return;
    }
    QList<int>::reverse_iterator it = qlr.rbegin();
    for(;it!=qlr.rend();++it)
        ui->tableWidget->removeRow(*it);
}

void TableWidget::freshTable()
{
    int row = ui->tableWidget->rowCount();
    for(int i=0;i!=row;++i)
        ui->tableWidget->removeRow(0);
    loadTable();
}

void TableWidget::saveTable()
{
    std::ofstream ofs;
    ofs.open(logPath.c_str(),std::ios_base::out|std::ios_base::trunc);
    int rowCount = ui->tableWidget->rowCount();
    for(int i=0;i!=rowCount;++i)
    {
        std::string name = ui->tableWidget->item(i,0)->text().toStdString();
        std::string birthday = ui->tableWidget->item(i,1)->text().toStdString();
        std::string gender = ui->tableWidget->item(i,2)->data(Qt::DisplayRole).toString().toStdString();
        std::string qq = ui->tableWidget->item(i,3)->text().toStdString();
        ofs<< (name.length()==0?"null":name) << ' ';
        ofs<< (birthday.length()==0?"null":birthday) << ' ';
        ofs<< (gender.length()==0?"null":gender) << ' ';
        ofs<< (qq.length()==0?"null":qq) << ' ';
        ofs<< '\n';
    }
    ofs.close();

}

void TableWidget::filterChanged()
{
    QString str = ui->lineEdit->text();
    //QList<QTableWidgetItem *> qlqt = ui->tableWidget->findItems(str,Qt::MatchContains);
    const QVariant qv(str);
    if(str.length()>0)
    {
      //  ui->tableWidget->model()->match(ui->tableWidget->model(),Qt::DisplayRole,qv);

    }
}

void TableWidget::TableAddItem(const QString &name,const QString &birthday,const QString &gender,const QString &qq)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item;
    item = new QTableWidgetItem(name);
    ui->tableWidget->setItem(row,0,item);

    item = new QTableWidgetItem(birthday);
    ui->tableWidget->setItem(row,1,item);

    item = new QTableWidgetItem(gender=="male"?QIcon(icom):QIcon(icow),gender=="male"?"male":"female");
    ui->tableWidget->setItem(row,2,item);

    item = new QTableWidgetItem(qq);
    ui->tableWidget->setItem(row,3,item);
}
