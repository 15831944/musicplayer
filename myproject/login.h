#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include "entry.h"
#include "mainwindow.h"
#include "user.h"
#include "list.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    virtual void accept();
    void on_entrybutton_clicked();
    void on_name1_textChanged(const QString &arg1);

private:
    Ui::login *ui;
};

#endif // LOGIN_H
