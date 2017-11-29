#ifndef MYLISTDELEGATE_H
#define MYLISTDELEGATE_H

#include <QIcon>
#include <QObject>
#include <QPainter>
#include <QLineEdit>
#include <QStyledItemDelegate>

class MyListDelegate : public QStyledItemDelegate
{

public:
    explicit MyListDelegate(QObject *parent = 0);
    ~MyListDelegate();

private:
    void paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;


    QPixmap icoM,icoF;
signals:

public slots:
};

#endif // MYLISTDELEGATE_H
