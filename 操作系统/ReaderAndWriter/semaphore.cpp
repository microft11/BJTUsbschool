#include <iostream>
#include <thread>
#include <semaphore.h>

sem_t read_sem, write_sem;
int readers = 0;

void reader() {
    while (true) {
        sem_wait(&read_sem);
        {
            readers++;
            if (readers == 1) {
                sem_wait(&write_sem);
            }
        }
        sem_post(&read_sem);

        // 读取资源
        std::cout << "Reader is reading" << std::endl;

        sem_wait(&read_sem);
        {
            readers--;
            if (readers == 0) {
                sem_post(&write_sem);
            }
        }
        sem_post(&read_sem);
    }
}

void writer() {
    while (true) {
        sem_wait(&write_sem);

        // 写入资源
        std::cout << "Writer is writing" << std::endl;

        sem_post(&write_sem);
    }
}

int main() {
    const int readersCount = 3;
    const int writersCount = 2;
    std::thread readers[readersCount];
    std::thread writers[writersCount];

    sem_init(&read_sem, 0, 1);
    sem_init(&write_sem, 0, 1);

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

    sem_destroy(&read_sem);
    sem_destroy(&write_sem);

    return 0;
}
