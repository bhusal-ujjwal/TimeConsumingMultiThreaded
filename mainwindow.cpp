#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QThreadPool>
#include "worker.h"
#include "secworker.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
Worker* thread1;
Secworker* thread2;

void MainWindow::on_btn_start_clicked()
{
    // Create a thread pool with a maximum of two threads
    QThreadPool* pool = QThreadPool::globalInstance();
    pool->setMaxThreadCount(2);

    // Create two worker threads and submit them to the pool
    thread1 = new Worker(ui->le_iterative->text().toLongLong());
    thread2 = new Secworker(ui->le_eratosthene->text().toLongLong());
    connect(thread1, &Worker::progress, this, &MainWindow::updateProgress);
    connect(thread1, &Worker::finished, this, &MainWindow::finished);
    connect(thread1, &Worker::runningTimeChanged, this, &MainWindow::runningTimeChanged);
    connect(thread1, &Worker::estimatedTimeChanged, this, &MainWindow::estimatedTimeChanged);
    connect(ui->btn_pause, &QPushButton::clicked, this, &MainWindow::on_pauseButton_clicked);
    connect(ui->btn_stop, &QPushButton::clicked, thread1, &Worker::stop);

    connect(thread2, &Secworker::progressErato, this, &MainWindow::updateEratoProgress);
    connect(thread2, &Secworker::finishedErato, this, &MainWindow::finishedErato);
    connect(thread2, &Secworker::runningTimeChangedErato, this, &MainWindow::runningTimeChangedErato);
    connect(thread2, &Secworker::estimatedTimeChangedErato, this, &MainWindow::estimatedTimeChangedErato);
    connect(ui->btn_stop, &QPushButton::clicked, thread2, &Secworker::stop);
    pool->start(thread1);
    pool->start(thread2);

}

void MainWindow::updateProgress(int percent){
    //Update the progress bar
    ui->progressBar->setValue(percent);
}

void MainWindow::finished(qint64 result){
    ui->le_iterative->setText(QString::number(result));

}

void MainWindow::updateEratoProgress(qint64 percent, qint64 i){
    //Update the progress bar
    ui->progressBar_2->setValue(i);
    //also output the primes
    ui->plainTextEdit->appendPlainText(QString::number(percent));
}

void MainWindow::finishedErato(){
    qDebug()<< "Thread two has finished";

}

void MainWindow::runningTimeChanged(int seconds){
    ui->lbl_running_iterative->setText(QString("Running time: %1 seconds").arg(seconds));
}

void MainWindow::runningTimeChangedErato(int seconds){
    ui->lbl_running_eratosthene->setText(QString("Running time: %1 seconds").arg(seconds));
}

void MainWindow::estimatedTimeChanged(int estmtdTime){
  ui->lbl_esti_iterative->setText(QString("Estimated time remaining: %1 milli secs").arg(estmtdTime));
}


void MainWindow::estimatedTimeChangedErato(int estmtdTimePrime){
  ui->lbl_esti_eratosthene->setText(QString("Estimated time remaining: %1 seconds").arg(estmtdTimePrime));
}

void MainWindow::on_pauseButton_clicked(){
    thread1->pause();
    thread2->pause();
}
