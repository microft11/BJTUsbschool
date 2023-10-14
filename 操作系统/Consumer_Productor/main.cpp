#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

// 共享缓冲区
std::queue<int> buffer;
const int buffer_size = 5;
std::mutex mtx;
std::condition_variable buffer_empty, buffer_full;

// 生产者函数
void producer(int id) {
    while (true) {
        int item = rand() % 100; //模拟产生的物品
        {
            std::unique_lock<std::mutex> lock(mtx);
            // 创建了一个 unique_lock 对象 lock，并使用互斥锁 mtx 进行初始化。
            // 这是为了确保在进入作用域时锁住互斥锁，并在退出作用域时自动释放锁。
            if (buffer.size() >= buffer_size) {   //检查是否满
                std::cout << "Producer " << id << " waiting, buffer is full." << std::endl;
                buffer_full.wait(lock);
                //当条件满足时，生产者线程会等待在 wait 函数内，直到被其他线程唤醒。
            }
            buffer.push(item);
            std::cout << "Producer " << id << " produced " << item << std::endl;
            buffer_empty.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 消费者函数
void consumer(int id) {
    while (true) {
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (buffer.empty()) {
                std::cout << "Consumer " << id << " waiting, buffer is empty." << std::endl;
                buffer_empty.wait(lock);
            }
            item = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " consumed " << item << std::endl;
            buffer_full.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    // 创建两个生产者线程和两个消费者线程
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 1; i <= 2; i++) {
        producers.push_back(std::thread(producer, i));
        consumers.push_back(std::thread(consumer, i));
    }

    // 启动所有线程
    for (auto& producer_thread : producers) {
        producer_thread.join();
    }
    for (auto& consumer_thread : consumers) {
        consumer_thread.join();
    }

    return 0;
}
