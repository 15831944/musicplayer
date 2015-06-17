#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QComboBox>
#include <ctime>
#include <cstdlib>
#include "qpainter.h"
#include "entry.h"
#include "login.h"
#include "user.h"
#include "list.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void qmpSetVol();
    void qmpSetVal();
    void qmpPlays();
    void qmpPause();
    void qmpSettitle();
    void qmpPlayOrPause();
    void qmpLast();
    void qmpNext();
    void qmpPlay();
    void qmpPlaying(qint64 position);
    void qmpDuration(qint64 pos);
    void qmpSelectFile();
    void readselectfile();
    void on_exit_clicked();
    void paintEvent();
    void on_changepicture_clicked();
    //void resolve_lrc();
    void on_membername_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private:
    Ui::MainWindow *ui;
    bool qmpPlayPause;
    QString name;
    int nums;
    QMediaPlayer* qmpPlayer;
    QStringList songlst;
    QString songname;
};

#endif // MAINWINDOW_H
