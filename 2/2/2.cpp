

#include "timer.h"
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <stack>
#include <algorithm>
#include <atomic>
#include <stdlib.h>

using namespace std;



mutex m;
int N = 4;
const int thousendT = 1000 * 3700;

vector<int> V1(thousendT);

stack<int> s;

once_flag flag;


class MyClass
{
    double myTimer = 0;

public:
    MyClass(int id, int length)
    {
        this->id = id;
        this->length = length; // количество потоков

        lock_guard lk(m);
        consol_parameter::SetPosition(0, id);        
        cout << id;
        consol_parameter::SetPosition(4, id);
        cout << this_thread::get_id();
        this_thread::sleep_for(100ms);
    }

    MyClass() :MyClass(0, 1000) {

    }
    void setLength(int l)
    {
        length = l;
    }
    void calc(int a)
    {
        auto start_time = chrono::high_resolution_clock::now();
        myFunc();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> time = end - start_time;
        myTimer += time.count();
        draw();
        counter++;
    }



private:
    int counter = 0;
    int barCounter=0;
    int old_counter=0;
    void myFunc()
    {
        lock_guard lk(m);
        V1.push_back(rand());
    }
    void draw()
    {
        int delitel = 19;
        if (counter - old_counter > thousendT /  delitel )
        {
            lock_guard lk(m);
            barCounter++;
            consol_parameter::SetPosition(10 + barCounter, id);
            cout << c;
            old_counter = counter;
            if (barCounter == delitel - 1) {
                consol_parameter::SetPosition(15 + delitel, id);
                cout << (myTimer / 1000) << "s";
            }
        }
    }
    int id;
    int length;
    atomic<char> c = 23;
};


void drawBarProgress(int i, int N1)
{
    MyClass m2(i,N1);
    for(int l = 0; l<thousendT;++l)
    m2.calc(l);

}

void task()
{

    thread* t = new thread[N];
    for (int i = 0; i < N; ++i)
    {
        t[i] = thread(drawBarProgress, i, N);
    }

    for (int i = 0; i < N; ++i)
        t[i].join();
    consol_parameter::SetPosition(0, 6);
}


int main()
{
    setlocale(LC_ALL, "Russian");

    task();

}
