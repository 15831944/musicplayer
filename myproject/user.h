#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QProcess>
#include "entry.h"
#include "login.h"
#include "mainwindow.h"

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private slots:
    void on_change_clicked();
    void on_game_clicked();

private:
    Ui::user *ui;
};

#endif // USER_H
