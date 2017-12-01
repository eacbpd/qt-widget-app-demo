#include "painter.h"
#include "ui_painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent),
    ispressed(false),
    isrecording(true),
    isshowcircle(false),
    m_PaintStatus(0),
    ui(new Ui::Painter)
{
    ui->setupUi(this);
    m_timer=startTimer(1000);

    ui->radioButton_1->setChecked(true);
    connect(ui->radioButton_1,&QRadioButton::clicked,[this]{m_PaintStatus=0;CleanScreen();});
    connect(ui->radioButton_2,&QRadioButton::clicked,[this]{m_PaintStatus=1;CleanScreen();});
    connect(ui->radioButton_3,&QRadioButton::clicked,[this]{m_PaintStatus=2;CleanScreen();});
}

Painter::~Painter()
{
    delete ui;
}

void Painter::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==m_timer)
    {
        isshowcircle=!isshowcircle;
        update();
    }
}

void Painter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //background
    QRect target(0,0,this->width(),this->height());
    QRect source(0,0,300,250);
    //painter.drawPixmap(target,QPixmap("/media/e/xxx.jpg"),source);

    //bling circle
    if(isrecording)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(isshowcircle?QColor(0,0,0,0):QColor(0x0,0xff,0x0,0x77)));
        painter.drawEllipse(0,0,20,20);
    }

    //mouse operator
    QPen pen(QColor(0,0,255));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(6);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(0,0,0)));
    switch(m_PaintStatus)
    {
    case 0:
        for(int i=0;i<qvqp.size()-1;++i)
        {
            QPoint &p1=qvqp[i];
            QPoint &p2=qvqp[i+1];
            painter.drawLine(p1,p2);
        }
        //    painter.drawLines(qvqp);
        break;
    case 1:
        if(ispressed)
        {
            painter.drawLine(m_endp.x(),0,m_endp.x(),this->height());
            painter.drawLine(0,m_endp.y(),this->width(),m_endp.y());
        }
        painter.drawRect(m_startp.x(),m_startp.y(),
                         m_endp.x()-m_startp.x(),m_endp.y()-m_startp.y());
        break;
    case 2:
    {
        int x = origin().x();
        int y = origin().y();
        painter.drawLine(0,y,this->width(),y);
        painter.drawLine(x,0,x,this->height());
        QPoint start = QPoint();
        for(int i=0;i!=360;++i)
        {
            double angle=3.14*i/180;
            int j=(sin(angle)*100);
            QPoint current(i,j);
            painter.drawLine(towindow(start),towindow(current));
            start=current;
        }
        start = QPoint();
        for(int i=0;i!=-360;--i)
        {
            double angle=3.14*i/180;
            int j=(sin(angle)*100);
            QPoint current(i,j);
            painter.drawLine(towindow(start),towindow(current));
            start=current;
        }
    }
        break;
    default:
        break;
    }
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    ispressed=true;
    switch(m_PaintStatus)
    {
    case 0:
        qvqp.clear();
        break;
    case 1:
        m_endp=event->pos();
        m_startp=event->pos();
        break;
    case 2:
        break;
    default:
        break;
    }

}

void Painter::mouseMoveEvent(QMouseEvent *event)
{
    if(ispressed)
    {
        switch(m_PaintStatus)
        {
        case 0:
            qvqp.push_back(event->pos());
            update();
            break;
        case 1:
            m_endp=event->pos();
            update();
            break;
        case 2:
            break;
        default:
            break;
        }
    }
}

void Painter::mouseReleaseEvent(QMouseEvent *event)
{
    ispressed=false;
    update();
}

void Painter::mouseDoubleClickEvent(QMouseEvent *event)
{
    isrecording = !isrecording;
}

QPoint Painter::origin()const
{
    return this->frameGeometry().center();
}

QPoint Painter::towindow(QPoint &qp)const
{
    return qp+origin();
}

QPoint Painter::fromwindow(QPoint &qp)const
{
    return qp-origin();
}

void Painter::CleanScreen()
{
    qvqp.clear();
    m_endp=QPoint();
    m_startp=QPoint();
    update();
}
