#include "entry.h"
#include "ui_entry.h"

entry::entry(bool d, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::entry)
{
    decide=d;
    ui->setupUi(this);
    ui->code11->setEchoMode(QLineEdit::Password);
    ui->code21->setEchoMode(QLineEdit::Password);
    if(decide == true)
    {
        ui->name1->setEchoMode(QLineEdit::Password);
        this->setWindowTitle("更改密码");
        ui->name->setText("请输入旧密码：");
        ui->code1->setText("请输入新密码");
    }
    connect(ui->sure,SIGNAL(clicked()),this,SLOT(accept()));
}

entry::~entry()
{
    delete ui;
}

void entry::accept()
{
    bool bname,bcode1,bcode2,all;
    QString name1,nothing;
    QString n,ocode;
    bool nothing1;
    QString name=ui->name1->text();
    QString code1=ui->code11->text();
    QString code2=ui->code21->text();
    all=true;
    if(decide == true)
    {
        if( name == 0 )
        {
            ui->name1->setText("请输入旧密码");
            bname=false;
        }
        else
        {
           QFile file1("membernow.file");
           file1.open(QIODevice::ReadOnly);
           QDataStream in(&file1);
           in>>n>>ocode;
           file1.close();
           if(name == ocode)
               bname=true;
           else
               ui->name1->setText("请输入正确的旧密码");
        }
    }
    else
    {
        if( name == 0 )
        {
            ui->name1->setText("用户名不能为空");
            bname=false;
        }
        else
        {
            if( name.length()>15 || name.length()<3 )
            {
                ui->name1->setText("请输入3-15位的用户名");
                bname=false;
            }
            else
                bname=true;
        }
    }
    if( code1 == 0 )
    {
        ui->code11->setText("密码不能为空");
        bcode1=false;
    }
    else
    {
        if( code1.length()>16 || code1.length()<7 )
        {
            ui->code11->setText("请输入7-16位密码");
            bcode1=false;
        }
        else
            bcode1=true;
    }
    if( code2 == 0 || bcode1 ==false )
    {
        ui->code21->setText("请再次输入密码");
        bcode2=false;
    }
    else
    {
        if( code1 != code2 || code2 == "请再次输入密码" )
        {
            ui->code21->setText("两次密码不一致，请重新输入");
            bcode2=false;
        }
        else
            bcode2=true;
    }
    if(decide == true)
    {
        if( bname == true && bcode1 == true && bcode2 == true )
        {
            ocode=ui->code11->text();
            QFile file("nc.file");
            file.open(QIODevice::ReadOnly);
            QDataStream in(&file);
            QString name,code;
            bool nothing;
            List<User> my;
            while(!file.atEnd())
            {
                in>>name>>code>>nothing;
                if( n == name )
                {
                    code=ocode;
                }
                User* u=new User(name,code,nothing);
                my.insertAtBack(*u);
            }
            file.close();
            QFile file4("nc.file");
            file4.open(QIODevice::WriteOnly | QFile::Truncate );
            QDataStream out4(&file4);
            for( int i=0;i<my.getsize();i++ )
            {
                out4<<my[i].name<<my[i].code<<my[i].rem;
            }
            file4.close();
            bool nothing2;
            QFile file2("button.file");
            file2.open(QIODevice::ReadWrite | QFile::Truncate);
            QDataStream in2(&file2);
            in2>>nothing>>nothing2>>name>>code;
            if(name == n)
            {
                code=ocode;
                in2<<nothing<<nothing2<<name<<code;
            }
            file2.close();
            QMessageBox::warning(this,
                                 tr("提示"),
                                 tr("请重新登录"),
                                 QMessageBox::Ok);
            this->close();
            login* l=new login();
            l->setAttribute(Qt::WA_DeleteOnClose);
            l->show();
        }
        else
        {
            ui->name1->setEchoMode(QLineEdit::Normal);
            ui->code11->setEchoMode(QLineEdit::Normal);
            ui->code21->setEchoMode(QLineEdit::Normal);
        }
    }
    else
    {
        QFile file("nc.file");
        file.open(QIODevice::ReadWrite);
        QDataStream inout(&file);
        while(!file.atEnd())
        {
            inout>>name1>>nothing>>nothing1;
            if(ui->name1->text() == name1)
                all=false;
        }
        if( all == false )
        {
            QMessageBox::warning(this,
                                 tr("警告"),
                                 tr("用户已存在"),
                                 QMessageBox::Ok);
            ui->name1->setFocus();
        }
        if( bname == true && bcode1 == true && bcode2 == true && all == true )
        {
            all=false;
            inout<<name<<code1<<all;
            file.close();
            QMessageBox::information( NULL,"提示","注册成功",QMessageBox::Ok );
            QFile file3("membernow.file");
            file3.open( QIODevice::WriteOnly | QFile::Truncate );
            QDataStream out2(&file3);
            out2<<name<<code1;
            file3.close();
            this->close();
            MainWindow* w=new MainWindow();
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->show();
        }
        else
        {
            ui->name1->setEchoMode(QLineEdit::Normal);
            ui->code11->setEchoMode(QLineEdit::Normal);
            ui->code21->setEchoMode(QLineEdit::Normal);
        }
    }
}

void entry::on_cancel_clicked()
{
    if(decide == true)
    {
        this->close();
        MainWindow* m=new MainWindow();
        m->setAttribute(Qt::WA_DeleteOnClose);
        m->show();
    }
    else
    {
        this->close();
        login* l=new login();
        l->setAttribute(Qt::WA_DeleteOnClose);
        l->show();
    }
}

void entry::on_name1_textChanged(const QString &arg1)
{
    this->change();
}

void entry::on_code11_textChanged(const QString &arg1)
{
    this->change();
}

void entry::on_code21_textChanged(const QString &arg1)
{
    this->change();
}

void entry::change()
{
    if(decide == true)
    {
        ui->name1->setEchoMode(QLineEdit::Password);
    }
    ui->code11->setEchoMode(QLineEdit::Password);
    ui->code21->setEchoMode(QLineEdit::Password);
}
