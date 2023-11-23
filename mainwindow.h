#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtCore/qthreadpool.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pauseButton_clicked();

    void updateProgress(int percent);
    void updateEratoProgress(qint64 percent, qint64 i);
    void finishedErato();
    void finished(qint64 result);

    void runningTimeChanged(int seconds);
    void runningTimeChangedErato(int seconds);

    void estimatedTimeChanged(int estmtdTime);
    void estimatedTimeChangedErato(int estmtdTime);


private slots:
    void on_btn_start_clicked();

private:
    Ui::MainWindow *ui;
    QThreadPool threadPool;
};
#endif // MAINWINDOW_H
