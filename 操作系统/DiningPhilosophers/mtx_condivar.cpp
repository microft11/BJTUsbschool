#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int num_philosophers = 5;
std::mutex forks[num_philosophers];
std::condition_variable can_eat[num_philosophers];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;

    while (true) {
        // Think for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Pick up forks
        std::unique_lock<std::mutex> left_lock(forks[left_fork]);
        std::unique_lock<std::mutex> right_lock(forks[right_fork]);

        // Eat
        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Put down forks
        left_lock.unlock();
        right_lock.unlock();

        // Signal neighbors that they can eat
        can_eat[left_fork].notify_one();
        can_eat[right_fork].notify_one();
    }
}

int main() {
    std::thread philosophers[num_philosophers];

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i] = std::thread(philosopher, i);
    }

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].join();
    }

    return 0;
}
