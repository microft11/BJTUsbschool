#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

std::map<std::string, int> semaphores;
std::mutex mtx;
std::condition_variable cv;

// 鍒濆鍖栦俊鍙烽噺
void initSemaphore(const std::string& identifier, int initialCount) {
    std::lock_guard<std::mutex> lock(mtx);
    semaphores[identifier] = initialCount;
}

// Swait鍘熻
void Swait(const std::string& identifier, int threadId) {
    std::unique_lock<std::mutex> lock(mtx);
    
    while (semaphores[identifier] <= 0) {
        std::cout << "Thread " << threadId << " is waiting for semaphore " << identifier << "." << std::endl;
        cv.wait(lock);
    }

    semaphores[identifier]--;
}

// Ssignal鍘熻
void Ssignal(const std::string& identifier) {
    std::lock_guard<std::mutex> lock(mtx);
    semaphores[identifier]++;
    std::cout << "Semaphore " << identifier << " is signaled." << std::endl;
    cv.notify_all();
}

int main() {
    // 鍒濆鍖栦俊鍙烽噺闆嗗悎
    initSemaphore("S1", 1);
    initSemaphore("S2", 2);
    // 鍙互娣诲姞鏇村鐨勪俊鍙烽噺

    // 鍒涘缓绾跨▼
    std::thread t1([&]() {
        Swait("S1", 1); // 绾跨▼1绛夊緟S1
        // 鎵ц闇€瑕佷俊鍙烽噺S1鐨勬搷浣?
        Ssignal("S1"); // 閲婃斁淇″彿閲廠1
    });

    std::thread t2([&]() {
        Swait("S2", 2); // 绾跨▼2绛夊緟S2
        // 鎵ц闇€瑕佷俊鍙烽噺S2鐨勬搷浣?
        Ssignal("S2"); // 閲婃斁淇″彿閲廠2
    });

    t1.join();
    t2.join();

    return 0;
}