#include "network.h"
#include "ui_network.h"

NetWork::NetWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetWork)
{
    ui->setupUi(this);
    ui->editAddr->setText("127.0.0.1");
    ui->editPort->setText("17904");
    connect(ui->btnServer,&QPushButton::clicked,this,&NetWork::onBtnServer);
    connect(ui->btnClient,&QPushButton::clicked,this,&NetWork::onBtnClient);

    connect(ui->btnExit,&QPushButton::clicked,this,&NetWork::onCBtnClose);
    connect(ui->btnClose,&QPushButton::clicked,this,&NetWork::onSBtnClose);
}
NetWork::~NetWork()
{
    delete ui;
}

void NetWork::onBtnServer()
{
    m_pServer = new serverClass();
    connect(ui->btnNotice,&QPushButton::clicked,this,&NetWork::onSBtnWrite);
    //connect(m_pServer->tcpserver,&QTcpServer::newConnection,)
    connect(ui->btnClose,&QPushButton::clicked,this,&NetWork::onSBtnClose);
    ui->stackedWidget->setCurrentIndex(2);
}
void NetWork::onSBtnWrite()
{
    for(auto &a:m_pServer->ql_psocket)
        a->write(ui->sInputEdit->toPlainText().toStdString().c_str());
}
void NetWork::onSRead()
{

}
void NetWork::onSBtnClose()
{
    delete m_pServer;
    ui->stackedWidget->setCurrentIndex(0);
}


void NetWork::onBtnClient()
{
    m_pClient = new clientClass(ui->editAddr->text(),quint16(ui->editPort->text().toShort()));
    //connect(ui->btnSend,&QPushButton::clicked,m_pClient,&clientClass::Onsend);

    //readyRead()表示服务端发送数据过来即发动信号，接着revData()进行处理。
    connect(m_pClient->tcpsocket,&QTcpSocket::readyRead,this,&NetWork::onCRead);

    ui->stackedWidget->setCurrentIndex(1);
}
void NetWork::onCBtnWrite()
{

}
void NetWork::onCRead()
{
    QString str = m_pClient->tcpsocket->readAll();
    ui->cDisplayEdit->append(str);
    qDebug()<< str;
}
void NetWork::onCBtnClose()
{
    delete m_pClient;
    ui->stackedWidget->setCurrentIndex(0);
}





serverClass::serverClass(NetWork *parent):m_parent(parent)
{
    tcpserver = new QTcpServer(this);

    if(!tcpserver->listen(QHostAddress::Any,17904))
    {
        qDebug()<<tcpserver->errorString();
        //close();
        return;
    }
    //newConnection()用于当有客户端访问时发出信号，Onaccept()信号处理函数
    connect(tcpserver,&QTcpServer::newConnection,this,&serverClass::Onaccept);

    //当tcpSocket在接受客户端连接时出现错误时，displayError(QAbstractSocket::SocketError)进行错误提醒并关闭tcpSocket。
    //connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

//    //send message
//    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Onsend()));

//    //close
//    connect(this,SIGNAL(destroyed(QObject*)),this,SLOT(Onclose()));
}

serverClass::~serverClass()
{
    delete tcpserver;
}

void serverClass::Onaccept()
{
    QTcpSocket *psocket = tcpserver->nextPendingConnection();
    ql_psocket.push_back(psocket);
    //recv message
    connect(psocket,&QTcpSocket::readyRead,this,&serverClass::Onrecv);
}

void serverClass::Onsend(/*const QString &str*/)
{

//    std::string const str = static_cast<QTextEdit>
//            (parent()->findChild("sInputEdit")).toPlainText().toStdString();
    for(auto &a:ql_psocket)
//        a->write(str.c_str());
        a->write("notice from server");
}
void serverClass::Onrecv()
{

}
void serverClass::Onerr(QAbstractSocket::SocketError)
{
    //qDebug()<<tcpsocket->errorString();
    //tcpsocket->close();
}

void serverClass::Onclose()
{
    for(auto &a:ql_psocket);
        //a->write(ui->lineEdit->text().toStdString().c_str());
}













clientClass::clientClass(const QString &a,const quint16 &p,NetWork *parent) :addr(a),port(p),m_parent(parent)
{
    tcpsocket = new QTcpSocket(this);
    //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）
    tcpsocket->abort();//assert closed
    tcpsocket->connectToHost(addr,port);//connect

    //connect(tcpsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Onerr(QAbstractSocket::SocketError)));
}

clientClass::~clientClass()
{
    delete tcpsocket;
}


//void DlgClient::Onsend()
//{

//}

//void DlgClient::Onerr(QAbstractSocket::SocketError)
//{
//    qDebug()<<tcpsocket->errorString();
//    tcpsocket->close();
//}

//void DlgClient::Onclose()
//{

//}
