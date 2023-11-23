#include "secworker.h"
Secworker::Secworker(qint64 target, QObject *parent) : QObject(parent), m_target(target)
{

}

void Secworker::run()
{
    // Initialize a boolean array of size N+1
    bool isPrime[m_target+1];
    memset(isPrime, true, sizeof(isPrime));
    QElapsedTimer timer;
    timer.start();

    int prg = 0;
    int elapsedTime = 0;
    int estimatedRemainingTime = 0;

    qint64 primeCount = 0;

    // Perform the sieve algorithm
    for (qint64 p = 2; p*p <= m_target; p++) {
        if (isPrime[p]) {
            primeCount++;
            for (qint64 i = p*p; i <= m_target; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // Emit the primes
    for (qint64 p = 2; p <= m_target; p++) {
        // Wait for a signal to resume the thread if paused
        while (m_paused) {
            QThread::msleep(100);
        }

        // Check if the thread should stop
        if (m_stopped) {
            return;
        }

        if (isPrime[p]) {
            primeCount++;
            prg = primeCount * 100 / m_target;
            elapsedTime = timer.elapsed();
            emit progressErato(p, prg);
            emit runningTimeChangedErato(elapsedTime / 1000);
            estimatedRemainingTime = (elapsedTime * (m_target - primeCount)) / (primeCount * 100);
            emit estimatedTimeChangedErato(estimatedRemainingTime);
            QThread::msleep(100);
        } else {
            prg = primeCount * 100 / m_target;
            elapsedTime = timer.elapsed();
            emit runningTimeChangedErato(elapsedTime / 1000);
            estimatedRemainingTime = (elapsedTime * (m_target - primeCount)) / (primeCount * 100);
            emit estimatedTimeChangedErato(estimatedRemainingTime);
            QThread::msleep(100);
        }
    }

    emit finishedErato();
}

