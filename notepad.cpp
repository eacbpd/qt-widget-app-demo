#include "notepad.h"
#include "ui_notepad.h"

NotePad::NotePad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotePad)
{
    ui->setupUi(this);
}

NotePad::~NotePad()
{
    delete ui;
}
