#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = startTimer(1000);

    m_timelab = new QLabel();
    m_timelab->setMinimumWidth(100);
    m_timelab->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addWidget(m_timelab);

    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(helpmsg()));
    QLineEdit *qle = new QLineEdit;
    //qle->setMaximumSize(QSize(100,20));
    ui->mainToolBar->insertWidget(ui->actionHelp,qle);

    //ui->statusBar->showMessage("loging...",5000);
    //ui->mainToolBar->hide();
    connect(ui->actionHelp,&QAction::triggered,this,&MainWindow::helpmsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==m_timer)
    {
        QTime time = QTime::currentTime();
        m_timelab->setText(time.toString("h:m:s ap"));
    }
}

void MainWindow::helpmsg()
{
    QMessageBox::information(this,"you have new message","look at me"/*,QMessageBox::StandardButton::Ok*/);
}
