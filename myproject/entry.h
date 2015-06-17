#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include "login.h"
#include "mainwindow.h"
#include "user.h"
#include "list.h"

namespace Ui {
class entry;
}

class entry : public QWidget
{
    Q_OBJECT

public:
    explicit entry(bool d = false,QWidget *parent = 0);
    ~entry();
    bool decide;

private slots:
    virtual void accept();
    void on_cancel_clicked();
    void on_name1_textChanged(const QString &arg1);
    void on_code11_textChanged(const QString &arg1);
    void on_code21_textChanged(const QString &arg1);
    void change();

private:
    Ui::entry *ui;
};

#endif // ENTRY_H
