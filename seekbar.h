#ifndef SEEKBAR_H
#define SEEKBAR_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QPushButton>
#include <QBitmap>
#include <QDebug>

namespace Ui {
class SeekBar;
}

class SeekBar : public QWidget
{
    Q_OBJECT

public:
    explicit SeekBar(QWidget *parent = 0);
    ~SeekBar();

    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    void onFullScreen();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::SeekBar *ui;
    QWidget *m_parent;
    bool m_focus;
    bool m_press;
    double m_percent;
    double m_tipValue;

};

#endif // SEEKBAR_H
