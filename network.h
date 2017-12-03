#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
class clientClass;
class serverClass;

namespace Ui {
class NetWork;
}

class NetWork : public QWidget
{
    Q_OBJECT

public:
    explicit NetWork(QWidget *parent = 0);
    ~NetWork();

    void onBtnServer();
    void onSBtnWrite();
    void onSRead();
    void onSBtnClose();

    void onBtnClient();
    void onCBtnWrite();
    void onCRead();
    void onCBtnClose();

//private:
    Ui::NetWork *ui;
    serverClass *m_pServer;
    clientClass *m_pClient;

};

class clientClass: public QObject
{
    Q_OBJECT

public:
    explicit clientClass(const QString &, const quint16 &, NetWork *parent = 0);
    ~clientClass();
    NetWork *m_parent;
//private:
    QTcpSocket *tcpsocket;
    QString addr;
    quint16 port;

public slots:

//    void Onsend();
//    void Onerr(QAbstractSocket::SocketError);
//    void Onclose();
};

class serverClass: public QObject
{
    Q_OBJECT
public:
    explicit serverClass(NetWork *parent = 0);
    ~serverClass();
    NetWork *m_parent;
//private:
    QTcpServer *tcpserver;
    QList<QTcpSocket*> ql_psocket;

public slots:
    void Onaccept();
    void Onrecv();
    void Onsend();
    void Onerr(QAbstractSocket::SocketError);
    void Onclose();
};


#endif // NETWORK_H
