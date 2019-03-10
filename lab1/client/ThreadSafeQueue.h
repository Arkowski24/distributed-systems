//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
#define DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>

using std::mutex;
using std::queue;
using std::condition_variable;

template<typename T>
class ThreadSafeQueue {
private:
    queue<T> q = queue<T>();
    mutex qMutex;
    condition_variable qCond;
public:
    void push(T elem) {
        std::unique_lock<mutex> lock(qMutex);
        q.push(elem);
        lock.unlock();
        qCond.notify_one();
    }

    T pop() {
        std::unique_lock<mutex> lock(qMutex);
        while (q.empty()) {
            qCond.wait(lock);
        }
        auto elem = q.front();
        q.pop();
        lock.unlock();
        return elem;
    }

    bool empty() {
        std::unique_lock<mutex> lock(qMutex);
        auto isEmpty = q.empty();
        lock.unlock();
        return isEmpty;
    }
};


#endif //DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
