#include "listwidget.h"
#include "ui_listwidget.h"

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    QIcon icon(":/resource/user.png");
    for(int i=0;i!=10;++i)
    {
        QListWidgetItem *item = new QListWidgetItem(icon,QString::number(i));
        item->setData(Qt::ToolTipRole,i*100);//[*]tips
        item->setData(Qt::DisplayRole,i*10);//[*]main text
        item->setData(Qt::UserRole+1,i);//[*age]
        item->setData(Qt::UserRole+2,i%2==0?false:true);//[*gender]
        item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable);//edit able !!!!!!!!!!!!!!
        ui->listWidget->addItem(item);
    }

    //    QAbstractItemModel *model = ui->listWidget->model();
    //    model->insertRow(0);
    //    model->setData(model->index(0,0),"icon",Qt::DisplayRole);
    //    model->setData(model->index(0,0),icon,Qt::DecorationRole);
    //    model->setData(model->index(0,0),1,Qt::UserRole);
    //    model->insertColumn(2,model->index(0,0));

    ui->listWidget->setItemDelegate(new MyListDelegate(this));//maybe not must to Inherits

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);//mouse rightbutton
    connect(ui->listWidget,&QListWidget::customContextMenuRequested,this,&ListWidget::OnListContextMenu);
    connect(ui->btn_change,&QPushButton::clicked,this,&ListWidget::OnSwitchButton);
    connect(ui->btn_remove,&QPushButton::clicked,this,&ListWidget::OnDelItem);
    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&ListWidget::OnDbClickItem);

    connect(ui->actionDel,&QAction::triggered,this,&ListWidget::OnDelItem);
    connect(ui->actionNew,&QAction::triggered,this,&ListWidget::OnAddItem);
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::OnSwitchButton()
{
    if(ui->listWidget->viewMode()==QListView::ListMode)
        ui->listWidget->setViewMode(QListView::IconMode);
    else
        ui->listWidget->setViewMode(QListView::ListMode);
}

void ListWidget::OnDbClickItem(QListWidgetItem *item)
{
    //QMessageBox::information(this,"msg",item->text());
    qDebug()<<item->data(Qt::ToolTipRole).toInt()
           <<item->data(Qt::DisplayRole)
          <<item->data(Qt::DecorationRole);
}

void ListWidget::OnDelItem()
{
    QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}

void ListWidget::OnAddItem()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::ToolTipRole,"i am new item");
    item->setData(Qt::DisplayRole,"i am new item");
    ui->listWidget->addItem(item);
}

void ListWidget::OnListContextMenu(const QPoint &pos)
{
    QListWidgetItem *selected = ui->listWidget->itemAt(pos);
    QMenu menu;
    menu.addAction(ui->actionNew);
    if(selected!=NULL)//there is no item at this pos
    {
        menu.addAction(ui->actionDel);
    }
    //menu.exec(this->mapToGlobal(QPoint(0,0))+ui->listWidget->pos()+pos);
    menu.exec(this->mapToGlobal(pos));
}
