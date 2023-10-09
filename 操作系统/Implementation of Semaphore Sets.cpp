#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

std::map<std::string, int> semaphores;
std::mutex mtx;
std::condition_variable cv;

// 初始化信号量
void initSemaphore(const std::string& identifier, int initialCount) {
    std::lock_guard<std::mutex> lock(mtx);
    semaphores[identifier] = initialCount;
}

// Swait原语
void Swait(const std::string& identifier, int threadId) {
    std::unique_lock<std::mutex> lock(mtx);
    
    while (semaphores[identifier] <= 0) {
        std::cout << "Thread " << threadId << " is waiting for semaphore " << identifier << "." << std::endl;
        cv.wait(lock);
    }

    semaphores[identifier]--;
}

// Ssignal原语
void Ssignal(const std::string& identifier) {
    std::lock_guard<std::mutex> lock(mtx);
    semaphores[identifier]++;
    std::cout << "Semaphore " << identifier << " is signaled." << std::endl;
    cv.notify_all();
}

int main() {
    // 初始化信号量集合
    initSemaphore("S1", 1);
    initSemaphore("S2", 2);
    // 可以添加更多的信号量

    // 创建线程
    std::thread t1([&]() {
        Swait("S1", 1); // 线程1等待S1
        // 执行需要信号量S1的操作
        Ssignal("S1"); // 释放信号量S1
    });

    std::thread t2([&]() {
        Swait("S2", 2); // 线程2等待S2
        // 执行需要信号量S2的操作
        Ssignal("S2"); // 释放信号量S2
    });

    t1.join();
    t2.join();

    return 0;
}
