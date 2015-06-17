#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qmpPlayPause=false;
    ui->setupUi(this);
    this->setFixedSize(331,506);
    qmpPlayer = new QMediaPlayer;
    ui->slsndvalue->setValue(qmpPlayer->volume()*3/4);
    QFile file("membernow.file");
    file.open( QIODevice::ReadOnly );
    QDataStream in(&file);
    in>>name;
    file.close();
    this->readselectfile();
    ui->membername->setText(name);
    ui->way->addItem("顺序播放");
    ui->way->addItem("单曲循环");
    ui->way->addItem("随机播放");
    QString q_filename=":/1";
    QFile file1(name+"picture.file");
    file1.open(QIODevice::ReadOnly);
    QDataStream in1(&file1);
    while(!file1.atEnd())
    {
        in1>>q_filename;
    }
    if(!q_filename.isNull())
    {
        ui->lstsong->setStyleSheet("background-color:transparent");
        QPixmap pixmap = QPixmap(q_filename).scaled(this->size());
        QPalette palette(this->palette());
        palette.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(palette);
    }
    file1.close();
    connect(qmpPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(qmpPlaying(qint64)));
    connect(qmpPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(qmpDuration(qint64)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::qmpSetVol()
{
    qmpPlayer->setVolume(ui->slsndvalue->value());
}

void MainWindow::qmpSetVal()
{
    qmpPlayer->setPosition(ui->slvalue->value());
}

void MainWindow::qmpPlays()
{
    qmpPlayer->pause();
    qmpPlayPause = false;
    ui->btnplaynpause->setText("▶");
}

void MainWindow::qmpPause()
{
    qmpPlayer->play();
    qmpPlayPause = true;
    ui->btnplaynpause->setText("▌▌");
}

void MainWindow::qmpSettitle()
{
    this->setWindowTitle("MyPlayer - " + ui->lstsong->currentItem()->text());
}

void MainWindow::qmpPlayOrPause()
{
    if(!qmpPlayPause)
        qmpPause();
    else if(qmpPlayPause)
        qmpPlays();
}

void MainWindow::qmpLast()
{
    if(ui->way->currentText() == "顺序播放")
    {
        if(ui->lstsong->currentIndex().row() == 0)
            nums=songlst.size() - 1;
        else
            nums=ui->lstsong->currentIndex().row() - 1;
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
    if(ui->way->currentText() == "单曲循环")
    {
        nums=ui->lstsong->currentIndex().row();
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
    if(ui->way->currentText() == "随机播放")
    {
        srand(time(0));
        nums=(nums+rand())%songlst.size();
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
}

void MainWindow::qmpNext()
{
    if(ui->way->currentText() == "顺序播放")
    {
        if(ui->lstsong->currentIndex().row() == songlst.size() - 1)
            nums=0;
        else
            nums=ui->lstsong->currentIndex().row() + 1;
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
    if(ui->way->currentText() == "单曲循环")
    {
        nums=ui->lstsong->currentIndex().row();
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
    if(ui->way->currentText() == "随机播放")
    {
        srand(time(0));
        nums=(nums+rand())%songlst.size();
        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
}

void MainWindow::qmpPlay()
{
    qmpPlayer->setMedia(QMediaContent(songlst.at(ui->lstsong->currentIndex().row())));
    qmpPause();
    qmpSettitle();
}

void MainWindow::qmpPlaying(qint64 position)
{
    if(position == qmpPlayer->duration())
        qmpNext();
    ui->slvalue->setSliderPosition(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->lbltime->setText(duration.toString("mm:ss"));
}

void MainWindow::qmpDuration(qint64 pos)
{
    ui->slvalue->setRange(0,pos);
}

void MainWindow::qmpSelectFile()
{
    QString n_dir="",q_filename;
    q_filename=QFileDialog::getOpenFileName(this,"打开","","Sounds Files (*.mp3)");
    if(!q_filename.isNull())
    {
       n_dir=q_filename.left(q_filename.lastIndexOf("/"));
    }
    QFile file(name+".file");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString copy="";
    bool decide=true;
    while(!file.atEnd())
    {
        in>>copy;
        if(copy == n_dir)
        {
            decide=false;
            break;
        }
    }
    file.close();
    if(decide == true)
    {
        QFile file1(name+".file");
        file1.open(QIODevice::WriteOnly|QFile::Append);
        QDataStream out(&file1);
        out<<n_dir;
        file1.close();
        ui->txtpath->setText(q_filename);
        ui->txtpath->setEnabled(false);
        QDir qd(n_dir);
        qd.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
        qd.setSorting(QDir::Size|QDir::Reversed);
        QFileInfoList list = qd.entryInfoList();
        for(int i=0;i< list.size();++i)
        {
            if(list.at(i).fileName().right(3) == "mp3")
            {
                songlst += n_dir + "/" + list.at(i).fileName();
                ui->lstsong->addItem(list.at(i).fileName());
            }
        }
    }
    else
    {
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("已经导入过此文件夹"),
                             QMessageBox::Yes);
    }
}

void MainWindow::readselectfile()
{
    QFile file(name+".file");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString n_dir;
    while(!file.atEnd())
    {
        in>>n_dir;
        if(!n_dir.isNull())
        {
           ui->txtpath->setText(n_dir);
           ui->txtpath->setEnabled(false);
           QDir qd(n_dir);
           qd.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
           qd.setSorting(QDir::Size|QDir::Reversed);
           QFileInfoList list = qd.entryInfoList();
           for(int i=0;i< list.size();++i)
           {
               if(list.at(i).fileName().right(3) == "mp3")
               {
                   songlst += n_dir + "/" + list.at(i).fileName();
                   ui->lstsong->addItem(list.at(i).fileName());
               }
           }
        }
    }
    file.close();
}

void MainWindow::paintEvent()
{
    ui->lstsong->setStyleSheet("background-color:transparent");
    QString q_filename;
    q_filename=QFileDialog::getOpenFileName(this,"打开","","IMAGE Files (*.jpg *.png)");
    QPixmap pixmap = QPixmap(q_filename).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    QFile file(name+"picture.file");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<q_filename;
    file.close();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasUrls())
        e->acceptProposedAction();
    else
        e->ignore();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls())
    {
        QList<QUrl> urls = e->mimeData()->urls();
        for(int i=0;i< urls.size();i++)
        {
            if(urls.at(i).toString().right(3) == "mp3")
            {
                QString qstr = urls.at(i).toString().mid(8,urls.at(i).toString().length() - 8);
                songlst += qstr;
                ui->lstsong->addItem(urls.at(i).fileName());
            }
        }
    }
}

void MainWindow::on_exit_clicked()
{
    if(qmpPlayPause)
        qmpPlays();
    this->close();
    login* l=new login();
    l->show();
}

void MainWindow::on_changepicture_clicked()
{
    this->paintEvent();
}

/*void MainWindow::resolve_lrc()
{
    bool decide=false;
    QString lrc_file_name;
    QFile file1(name+".file");
    file1.open(QIODevice::ReadOnly);
    QDataStream in(&file1);
    QString n_dir;
    while(!file.atEnd())
    {
        in>>n_dir;
        if(!n_dir.isNull())
        {
           QDir q(n_dir);
           q.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
           q.setSorting(QDir::Size|QDir::Reversed);
           QFileInfoList list = q.entryInfoList();
           for(int i=0;i< list.size();++i)
           {
               if(ui->lstsong->currentItem()->text()+".lrc" == list.at(i).fileName())
               {
                   lrc_file_name=n_dir+"\\"+ui->lstsong->currentItem()->text()+"lrc";
                   decide=true;
               }
           }
        }
    }
    file1.close();
    QFile file(lrc_file_name);
    QString all_text = QString(file.readAll());
    file.close();
    QStringList lines=all_text.split("\n");
    //这个是时间标签的格式[00:05.54]
    //正则表达式d{2}表示匹配2个数字
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString oneline, lines)
    {
        QString temp = oneline;
        temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
        // 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
        //indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
        //正常情况下pos后面应该对应的是歌词文件
        int pos = rx.indexIn(oneline, 0);
        while (pos != -1)
        { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
            // 插入到lrc_map中
            lrc_map.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
    }
    // 如果lrc_map为空
    if (lrc_map.isEmpty()) {
        lrc->setText(QFileInfo(media_object->currentSource().fileName()).baseName()
                     + tr(" --- 歌词文件内容错误！"));
        return;
    }
}*/

void MainWindow::on_membername_clicked()
{
    this->close();
    user* u=new user();
    u->show();
}
