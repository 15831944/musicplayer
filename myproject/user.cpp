#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}

user::~user()
{
    delete ui;
}

void user::on_change_clicked()
{
    this->close();
    entry* e=new entry(true);
    e->setAttribute(Qt::WA_DeleteOnClose);
    e->show();
}

void user::on_game_clicked()
{
    QProcess::startDetached("D:\\workspace\\myproject\\racecar.exe",QStringList());
}
