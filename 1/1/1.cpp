

#include "timer.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>
#include <thread>
#include <windows.h>
#include <mutex>
#include <atomic>


using namespace std;

//atomic<int> que{ 0 };

class spinlock_mutex
{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    spinlock_mutex() = default;
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire));
    }
    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
} sm;



void virtual_client(atomic<int> &q)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(1s);
        q.store(q.load()+1);
        consol_parameter::SetPosition(14, 1);
        cout << " " << q.load() << " ";
    }
}

void virtual_emploe(atomic<int> &q)
{
    for (int i = 0; i < 10; i++) 
    {
        this_thread::sleep_for(2s);
        q.store(q.load()- 1);
        consol_parameter::SetPosition(14, 1);
        cout << " " << q.load() << " ";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    atomic<int> que{ 0 };

    std::cout <<  "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;
    
    cout << "Длина очереди:";
    thread t_c(virtual_client, ref(que));
    thread t_e(virtual_emploe, ref(que));
    t_c.join();
    t_e.join();

    return 0;
}

