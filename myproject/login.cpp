#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->code1->setEchoMode(QLineEdit::Password);
    connect(ui->loginbutton,SIGNAL(clicked()),this,SLOT(accept()));
    QFile file1("button.file");
    file1.open(QIODevice::ReadOnly);
    QDataStream in1(&file1);
    bool au;
    bool reme=false;
    in1>>au>>reme;
    if( reme == true )
    {
        ui->autologin->setCheckState( Qt::Unchecked );
        ui->remeber->setCheckState( Qt::Checked );
        QString namecopy,codecopy;
        in1>>namecopy>>codecopy;
        file1.close();
        ui->name1->setText(namecopy);
        ui->code1->setText(codecopy);
    }
    if( reme == false )
    {
        file1.close();
        ui->autologin->setCheckState( Qt::Unchecked );
        ui->remeber->setCheckState( Qt::Unchecked );
    }
}

login::~login()
{
    delete ui;
}

void login::accept()
{
    int i=0;
    bool decide=false;
    QFile file("nc.file");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString name,code;
    bool nothing;
    List<User> my;
    while(!file.atEnd())
    {
        in>>name>>code>>nothing;
        User* u=new User(name,code,nothing);
        my.insertAtBack(*u);
        if( ui->name1->text() == name && ui->code1->text() == code )
        {
            decide=true;
        }
        if(decide == false)
        {
            i++;
        }
    }
    file.close();
    if( decide == true )
    {
        name=ui->name1->text();
        code=ui->code1->text();
        bool au=ui->autologin->isChecked();
        bool reme=ui->remeber->isChecked();
        QFile file1("button.file");
        file1.open( QIODevice::WriteOnly | QFile::Truncate );
        QDataStream out1(&file1);
        if( au && !reme )
        {
            file1.close();
            QMessageBox::warning(this,
                                 tr("警告"),
                                 tr("选择自动登录请同时选择记住密码！"),
                                 QMessageBox::Yes);
        }
        else
        {
            out1<<au<<reme<<name<<code;
            file1.close();
            my[i].rem=reme;
            QFile file4("nc.file");
            file4.open(QIODevice::WriteOnly | QFile::Truncate );
            QDataStream out4(&file4);
            for( int i=0;i<my.getsize();i++ )
            {
                out4<<my[i].name<<my[i].code<<my[i].rem;
            }
            file4.close();
            QFile file3("membernow.file");
            file3.open( QIODevice::WriteOnly | QFile::Truncate );
            QDataStream out2(&file3);
            out2<<name<<code;
            file3.close();
            this->close();
            MainWindow* w=new MainWindow();
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->show();
        }
    }
    else
    {
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("用户名或密码错误！"),
                             QMessageBox::Yes);
        ui->name1->setFocus();
    }
}

void login::on_entrybutton_clicked()
{
    entry* e=new entry();
    this->close();
    e->setAttribute(Qt::WA_DeleteOnClose);
    e->show();
}

void login::on_name1_textChanged(const QString &arg1)
{
    QFile file("nc.file");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString name,code;
    bool reme=false;
    while(!file.atEnd())
    {
        in>>name>>code>>reme;
        if(ui->name1->text() == name && reme == true)
        {
            ui->code1->setText(code);
            break;
        }
    }
}
