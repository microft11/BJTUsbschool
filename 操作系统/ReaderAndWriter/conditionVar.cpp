#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex writeMutex;
std::mutex readMutex;
std::condition_variable writeTurnstile;
std::condition_variable readTurnstile;
int readers = 0;

void reader() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(readMutex);
            readers++;
            if (readers == 1) {
                writeMutex.lock();
            }
        }

        // 读取资源
        std::cout << "Reader is reading" << std::endl;

        {
            std::unique_lock<std::mutex> lock(readMutex);
            readers--;
            if (readers == 0) {
                writeMutex.unlock();
            }
        }

        // 等待写者完成
        std::unique_lock<std::mutex> lock(writeMutex);
        writeTurnstile.wait(lock);
    }
}

void writer() {
    while (true) {
        // 写入资源
        std::cout << "Writer is writing" << std::endl;

        // 通知等待的读者或写者
        writeTurnstile.notify_all();
        readTurnstile.notify_all();

        // 等待其他写者完成
        std::unique_lock<std::mutex> lock(writeMutex);
        writeTurnstile.wait(lock);
    }
}

int main() {
    const int readersCount = 3;
    const int writersCount = 2;
    std::thread readers[readersCount];
    std::thread writers[writersCount];

    for (int i = 0; i < writersCount; i++) {
        writers[i] = std::thread(writer);
    }

    for (int i = 0; i < readersCount; i++) {
        readers[i] = std::thread(reader);
    }

    for (int i = 0; i < writersCount; i++) {
        writers[i].join();
    }

    for (int i = 0; i < readersCount; i++) {
        readers[i].join();
    }

    return 0;
}
