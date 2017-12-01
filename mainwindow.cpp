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

    //ui->statusBar->showMessage("loging...",5000);
    //ui->mainToolBar->hide();
    connect(ui->actionHelp,&QAction::triggered,this,&MainWindow::helpmsg);

    QLineEdit *qle = new QLineEdit;
    //qle->setMaximumSize(QSize(100,20));
    m_action = ui->mainToolBar->addWidget(qle);
    //m_action->setVisible(false);
    connect(qle,&QLineEdit::textChanged,m_action,&QAction::trigger);
    connect(m_action,&QAction::triggered,this,&MainWindow::findinfo);
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

void MainWindow::findinfo()
{

}
