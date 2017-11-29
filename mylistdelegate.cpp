#include "mylistdelegate.h"

MyListDelegate::MyListDelegate(QObject *parent) : QStyledItemDelegate(parent),
    icoM(":/resource/headm.png"),
    icoF(":/resource/headw.png")
{

}

MyListDelegate::~MyListDelegate()
{

}

void MyListDelegate::paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const
{
    QRect rect = option.rect;
    rect.adjust(2,2,-2,-2);
    QString str = "name:";
            str += index.data(Qt::DisplayRole).toString();
    QString age = "age :";
            age += index.data(Qt::UserRole+1).toString();
    bool gender = index.data(Qt::UserRole+2).toBool();

    painter->drawPixmap(rect.x(),rect.y(),64,64,gender?icoM:icoF);//head
    painter->drawText(rect.x()+70,rect.y()+20,age);//age
    painter->drawText(rect.x()+70,rect.y()+40,str);//name

    if(option.state&(QStyle::State_Selected|QStyle::State_HasFocus))
    {
        painter->setBrush(QColor(0,0,0x88,0x11));
        painter->drawRoundRect(rect,0,0);
        painter->setBrush(Qt::NoBrush);
    }
}

QSize MyListDelegate::sizeHint(const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option,index);
    size.setHeight(70);
    return size;
}

QWidget * MyListDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    return new QLineEdit(parent);
}

void MyListDelegate::updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void MyListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *qle = (QLineEdit *)editor;
    qle->setText(index.data(Qt::DisplayRole).toString());
}

void MyListDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QLineEdit *qle = (QLineEdit *)editor;
    model->setData(index,qle->text(),Qt::DisplayRole);
    //index.data(Qt::DisplayRole).setValue(qle->text());
}
