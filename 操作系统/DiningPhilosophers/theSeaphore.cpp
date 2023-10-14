#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

/*信号量的性质：信号量是一个用于线程同步的原语。
它有一个整数值，可以用来控制多个线程的访问。
sem_t 的值可以为正整数、零或负整数，它的行为取决于其值：

当值为正整数时，表示有可用资源，线程可以获取资源，且值会减一。
当值为零时，线程会被阻塞，直到有资源可用。
当值为负整数时，表示等待的线程数，线程获取资源后值会增加。*/

const int num_philosophers = 5;
sem_t forks[num_philosophers];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;

    while (true) {
        // Think for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Attempt to pick up forks
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        // Eat
        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Put down forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main() {
    std::thread philosophers[num_philosophers];

    for (int i = 0; i < num_philosophers; i++) {
        sem_init(&forks[i], 0, 1); // Initialize forks
    }/*第一个参数 &forks[i] 是一个指向叉子信号量的指针。这表示我们要初始化第 i 只叉子的信号量。
第二个参数 0 表示在多线程环境下使用该信号量。这个参数在本例中始终是0。
第三个参数 1 表示初始化信号量的初始值。在这里，叉子的初始值被设置为1，表示每只叉子一开始是可用的。*/

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i] = std::thread(philosopher, i);
    }

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].join();
    }

    return 0;
}
