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
    connect(ui->btnsave,&QPushButton::clicked,this,&TabWidget::savefile);
    connect(ui->btnadd,&QPushButton::clicked,this,&TabWidget::btnadd);
    connect(ui->btndel,&QPushButton::clicked,this,&TabWidget::btndel);
}

TabWidget::~TabWidget()
{
    delete ui;
}


void TabWidget::getfilename()
{
    QString filepath = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(filepath);
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
    ifstream ifs(ui->lineEdit->text().toStdString().c_str());
    char str[0x1000];

    ifs.getline(str,sizeof(str));
    while(ifs)//ifs.gcount()!=0//
    {
    ui->textBrowser->append(str);
    ifs.getline(str,sizeof(str));//read(str,sizeof(str));
    }
    //ifs.close();
}

void TabWidget::savefile()
{
    QString filepath = QFileDialog::getSaveFileName(this,"保存文件");
    if(filepath.size()==0)return;

//    string text=ui->plainTextEdit->toPlainText().toStdString();
//    FILE *fp=fopen(m_filepath.toStdString().c_str(),"wb");
//    fwrite(text.c_str(),1,text.size(),fp);
//    fclose(fp);

    ofstream ofs;
    ofs.open(filepath.toStdString().c_str());
    ofs<<ui->textBrowser->toPlainText().toStdString();
    ofs.close();
}

void TabWidget::btnadd()
{
    ui->tabWidget->addTab(new QTabWidget/*StackedWidget()*/,"新加入的");
    //ui->tabWidget->insertTab(0,new QTabWidget/*StackedWidget()*/,"新加入的");
}

void TabWidget::btndel()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}



