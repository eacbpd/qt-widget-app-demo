#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>
namespace Ui {
class Painter;
}

class Painter : public QWidget
{
    Q_OBJECT

public:
    explicit Painter(QWidget *parent = 0);
    ~Painter();
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    void CleanScreen();
    QPoint origin()const;
    QPoint towindow(QPoint &)const;
    QPoint fromwindow(QPoint &)const;
    bool ispressed;
    bool isrecording;
    bool isshowcircle;

private:
    QPoint m_startp;
    QPoint m_endp;
    int m_timer;
    uchar m_PaintStatus;
    QVector<QPoint> qvqp;
    Ui::Painter *ui;
};

#endif // PAINTER_H


