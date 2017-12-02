#include "treewidget.h"
#include "ui_treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget),
    icofile(":/resource/file.png"),
    icofolder(":/resource/folder.png")
{
    ui->setupUi(this);

    QDir dir("/home/e");
    QStringList filterlist;
    //filterlist<<"*.txt";        //1 select *.txt
    //filterlist.append("*.log"); //2
    filterlist.push_back("*");    //3
    QStringList filelist = dir.entryList(/*filterlist*/);
    for(int i=0;i<filelist.size();++i)
    {
        QString file = filelist[i];
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setData(1,Qt::DisplayRole,file);
        ui->treeWidget->addTopLevelItem(item);
        QCheckBox *checkbox = new QCheckBox();
        ui->treeWidget->setItemWidget(item,0,checkbox);
    }


//    ui->treeWidget->setColumnCount(5);
//    ui->treeWidget->setColumnWidth(0,80);
//    ui->treeWidget->setColumnWidth(1,140);
//    ui->treeWidget->setColumnWidth(2,80);
//    ui->treeWidget->setColumnWidth(3,140);
//    QStringList stringlist;
//    stringlist.push_back("FileName");
//    stringlist.push_back("LastModify");
//    stringlist.push_back("Type");
//    stringlist.push_back("Size");
//    stringlist.push_back("Other");
//    ui->treeWidget->setHeaderLabels(stringlist);
//    TreeAddItem("file1","20171111-111111",0,123412347567);
//    TreeAddItem("file2","20171111-222222",1,234678);
//    QTreeWidgetItem *item = TreeAddItem("file3","20171111-111111",0,5688923475);
//    TreeAddItem("file3Chile","20171111-222222",1,56667822,item);

}

TreeWidget::~TreeWidget()
{
    delete ui;
}

QTreeWidgetItem *TreeWidget::TreeAddItem(const QString fname,
                         const QString lmodify,
                         const int type,
                         const quint64 size,
                         QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,fname);
    item->setText(1,lmodify);
    if(type==1)
        item->setIcon(2,icofile);
    item->setText(3,QString::number(size));
    if(parent!=nullptr)
        parent->addChild(item);
    ui->treeWidget->addTopLevelItem(item);//first:add

    QCheckBox *checkbox = new QCheckBox(ui->treeWidget);//second:set extra checkbox
    ui->treeWidget->setItemWidget(item,4,checkbox);
    return item;
}
