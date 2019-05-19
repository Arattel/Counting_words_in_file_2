//
// Created by arattel on 07.05.19.
//

#ifndef COUNTING_WORDS_IN_FILE_2_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <map>

#pragma once

template<class T>
class ThreadSafeQueue {
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cv;
public:


    void push(T elem) {
        {
            std::lock_guard<std::mutex> lck(mutex);
            queue.push(elem);
        }
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lck(mutex);
        while (queue.empty()) {
            cv.wait(lck);
        }
        T result = queue.front();
        queue.pop();
        return result;
    }

    bool empty() {
        std::lock_guard<std::mutex> lck(mutex);
        return queue.empty();
    }

    std::vector<T> double_pop() {
        std::vector<T> results;
        std::unique_lock<std::mutex> lck(mutex);
        while (queue.size() < 2) {
            cv.wait(lck);
        }
        results.push_back(queue.front());
        queue.pop();
        results.push_back(queue.front());
        queue.pop();
        return results;
    }
};

class StringQueue {
    ThreadSafeQueue<std::string> queue;

public:
    void push(std::string elem) {
        queue.push(elem);
    }


    std::string pop() {
        std::string result = queue.pop();
        if (result == "Dead") {
            queue.push(result);
            return "";
        } else {
            return result;
        }
    }

    bool empty() {
        return queue.empty();
    };
};

class MapQueue {
    ThreadSafeQueue<std::map<std::string, int> > queue;
public:
    void push(std::map<std::string, int> elem) {
        queue.push(elem);
    }

    std::map<std::string, int> pop() {
        std::map<std::string, int> result = queue.pop();
        if (result.empty()) {
            queue.push(result);
            return result;
        } else {
            return result;
        }
    }

    std::vector<std::map<std::string, int>> double_pop() {
        std::vector<std::map<std::string, int>> result = queue.double_pop();
        if (result[1].empty()) {
            queue.push(result[0]);
            queue.push(result[1]);
        } else if (result[0].empty()) {
            queue.push(result[1]);
            queue.push(result[0]);
        }
        return result;
    }

};

#endif //COUNTING_WORDS_IN_FILE_2_QUEUE_H
