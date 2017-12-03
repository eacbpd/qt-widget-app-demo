#include "seekbar.h"
#include "ui_seekbar.h"

SeekBar::SeekBar(QWidget *parent) :
    QWidget(parent),m_parent(parent),
    ui(new Ui::SeekBar),
    m_focus(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);//tips
    setMouseTracking(true);//mouse tracking
    connect(ui->btnFull,&QPushButton::clicked,this,&SeekBar::onFullScreen);
}

void SeekBar::onFullScreen()
{
    if(Qt::Widget==m_parent->windowType())
    {
        m_parent->setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
        m_parent->showFullScreen();
    }
    else
    {
        m_parent->setWindowFlags (Qt::Widget);
        m_parent->showNormal();
    }
}
void SeekBar::keyPressEvent(QKeyEvent *keyset)
{
    if(keyset->key()==Qt::Key_Escape){
        m_parent->setWindowFlags (Qt::Widget);
        m_parent->showNormal ();
    }
}
SeekBar::~SeekBar()
{
    delete ui;
}

void SeekBar::enterEvent(QEvent *event)
{
    m_focus = true;
    update();
    setCursor(Qt::PointingHandCursor);
}
void SeekBar::leaveEvent(QEvent *event)
{
    m_focus = false;
    update();
    setCursor(Qt::ArrowCursor);
}
void SeekBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brushback(QColor(0x88,0x88,0x88));
    QBrush brushbar(QColor(0x0,0x0,0xff));
    QPen penback(QColor(0x0,0x0,0x0));
    QPen penprogress(QColor(0xff,0xff,0xff));
    int iline=2,iround=6;
    if(m_focus)
    {
        iline=4,iround=10;
    }
    penback.setWidth(iline);
    penprogress.setWidth(iline);

    int percent=m_percent*(this->width());
    if(m_focus)
    {
        //tipsregion rect
        QRect textRect(m_tipValue*(this->width())-20,0,40,20);
        //painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255,255,255,128));
        painter.drawRect(textRect);//painter.setRenderHint(QPainter::Antialiasing);
        //show text,area
        QFont font = painter.font();
        font.setPixelSize(14);
        painter.setFont(font);
        painter.setPen(QColor(0x33,0x33,0x33));
        painter.drawText(textRect,Qt::AlignCenter,QString::number(int(m_tipValue*100))+"%");
    }

    //validregion rect
    painter.setBrush(brushback);
    painter.drawRect(0,20,this->width(),this->height()-20);
    //under line
    painter.setPen(penback);
    painter.drawLine(0,35,this->width(),35);
    //progress line
    painter.setPen(penprogress);
    painter.drawLine(0,35,percent,35);
    //trackbar
    painter.setBrush(brushbar);
    painter.drawEllipse(QPoint(percent,35),iround,iround);
}
void SeekBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_press=true;
        m_percent = (double)event->x()/this->width();
        update();
    }
}
void SeekBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_press)
        m_press=false;
}
void SeekBar::mouseMoveEvent(QMouseEvent *event)
{
    double d = (double)event->x()/this->width();
    if(m_press)
        m_percent = d;
    m_tipValue = d;
    update();
}



