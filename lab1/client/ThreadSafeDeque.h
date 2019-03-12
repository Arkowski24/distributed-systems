//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
#define DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

using std::mutex;
using std::deque;
using std::condition_variable;

template<typename T>
class ThreadSafeDeque {
private:
    deque<T> q = deque<T>();
    mutex qMutex;
    condition_variable qCond;
public:
    void push(T elem) {
        std::unique_lock<mutex> lock(qMutex);
        q.push_back(elem);
        lock.unlock();
        qCond.notify_one();
    }

    T pop() {
        std::unique_lock<mutex> lock(qMutex);
        while (q.empty()) {
            qCond.wait(lock);
        }
        auto elem = q.front();
        q.pop_front();
        lock.unlock();
        return elem;
    }

    void push_front(T elem) {
        std::unique_lock<mutex> lock(qMutex);
        q.push_front(elem);
        lock.unlock();
        qCond.notify_one();
    }

    bool empty() {
        std::unique_lock<mutex> lock(qMutex);
        auto isEmpty = q.empty();
        lock.unlock();
        return isEmpty;
    }
};


#endif //DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
