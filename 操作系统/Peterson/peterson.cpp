#include <iostream>
#include <thread>
using namespace std;

const int NUM = 50000;
int count = 0;
bool flag[2] = {true, false};
int turn;

void threadA() 
{
    for (int i = 0; i < NUM; ++i)
    {
        flag[0] = true;
        turn  = 1;
        // __sync_synchronize();
        __asm__ __volatile__ ("mfence":::"memory");
        while (flag[1] && turn == 1);

        count ++;  

        flag[0] = false;
    }
}

void threadB() 
{
    for (int i = 0; i < NUM; ++i)
    {
        flag[1] = true;
        turn  = 1;
        // __sync_synchronize();
        __asm__ __volatile__ ("mfence":::"memory");
        while (flag[1] && turn == 0);

        count ++;  

        flag[1] = false;
    }
}

int main()
{
    thread t0(threadA) t1(threadB);
    t0.join();
    t1.join();

    cout <<"count is expected to be " << NUM + NUM << ",count = " << count <<endl;
    return 0;
}