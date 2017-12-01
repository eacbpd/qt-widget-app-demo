#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QWidget>

namespace Ui {
class NotePad;
}

class NotePad : public QWidget
{
    Q_OBJECT

public:
    explicit NotePad(QWidget *parent = 0);
    ~NotePad();

private:
    Ui::NotePad *ui;
};

#endif // NOTEPAD_H
