//
// Created by arekp on 2019-03-10.
//

#ifndef DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
#define DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H

#include <mutex>
#include <deque>

using std::mutex;
using std::deque;

template<typename T>
class ThreadSafeQueue {
private:
    deque<T> queue;
    mutex queueMutex;
public:
    void enqueue(T elem) {
        std::lock_guard<mutex> lock(queueMutex);
        queue.push_back(elem);
    }

    T dequeue() {
        std::lock_guard<mutex> lock(queueMutex);
        auto elem = queue.pop_front();
        return elem;
    }
};


#endif //DISTRIBUTED_SYSTEMS_THREADSAFEQUEUE_H
