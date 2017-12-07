#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <fstream>
#include <QMessageBox>
#include <QList>
#include <QDebug>
namespace Ui {
class TableWidget;
}

class People:public QObject
{
    Q_OBJECT
public:
    QString name;
    QString birthday;
    QString gender;
    QString qq;
    People(){}
    People(const QString &n,const QString &b,const QString &g,const QString &q)
    {
        name=n;
        birthday=b;
        gender=g;
        qq=q;
    }
    friend std::ofstream& operator <<(std::ofstream &ofs,const People &peo)
    {
        ofs<<peo.name.toStdString()<<' ';
        ofs<<peo.birthday.toStdString()<<' ';
        ofs<<peo.gender.toStdString()<<' ';
        ofs<<peo.qq.toStdString()<<'\n';
    }
    friend std::ifstream& operator >>(std::ifstream &ifs,People &peo)
    {
        std::string n,b,g,q;
        ifs>>n>>b>>g>>q;

        peo.name = QString(n.c_str());
        peo.birthday = QString(b.c_str());
        peo.gender = QString(g.c_str());
        peo.qq = QString(q.c_str());
    }
};

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();
    void loadTable();
    void newBlankItem();
    void delCurrentItem();
    void freshTable();
    void saveTable();
    void filterChanged();
    void TableAddItem(const QString &name,const QString &birthday,const QString &gender,const QString &qq);
private:
    Ui::TableWidget *ui;
    QPixmap icom,icow;
    std::string logPath;
};

#endif // TABLEWIDGET1_H
