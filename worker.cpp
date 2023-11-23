#include "worker.h"
#include <QTimer>
Worker::Worker(qint64 target, QObject *parent) : QObject(parent), m_target(target),m_paused(false),m_stopped(false)
{

}

void Worker::run()
{
    qint64 result = 1;
    int prg = 0;
    int elapsedTime = 0;
    int estimatedRemainingTime = 0;

    QElapsedTimer timer;
    timer.start();
    emit disableStartButton();
    for (qint64 i = 2; i <= m_target; i++) {
        // Check if the thread should stop
        if (m_stopped) {
            // Enable the start button when the thread has stopped
            emit enableStartButton();
            return;
        }
        // Do some work here
        result *= i;
        // Emit a signal to update the progress
        prg = i * 100 / m_target;
        emit progress(prg);
        // Wait for a signal to resume the thread if paused
        while (m_paused) {
            QThread::msleep(100);
        }
        // Emit the running time signal.
        elapsedTime = timer.elapsed();
        if (prg != 0) {
            estimatedRemainingTime = (elapsedTime / prg) * (m_target - prg);
        } else {
            estimatedRemainingTime = 0;
        }
        emit runningTimeChanged(elapsedTime / 1000);
        emit estimatedTimeChanged(estimatedRemainingTime);
        QThread::msleep(100);
    }
    // Enable the start button when the thread has finished
    emit enableStartButton();
    emit finished(result);
}
