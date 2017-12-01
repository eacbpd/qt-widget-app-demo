#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include <QAction>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void timerEvent(QTimerEvent *event);
    void helpmsg();
    void findinfo();
private:
    Ui::MainWindow *ui;
    int m_timer;
    QLabel *m_timelab;
    QAction *m_action;
};

#endif // MAINWINDOW_H
