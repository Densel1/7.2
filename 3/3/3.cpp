#include <mutex>
#include <iostream>


using namespace std;

class Data
{
public:
    int scalarData;
    std::mutex mutex;

    Data(int scalarData) : scalarData(scalarData), mutex() {}
};

void swap(Data& data1, Data& data2)
{
    // Вариант 1: lock
    
        lock(data1.mutex, data2.mutex);
        int temp = data1.scalarData;
        data1.scalarData = data2.scalarData;
        data2.scalarData = temp;
        data1.mutex.unlock();
        data2.mutex.unlock();
    }

    void swap1(Data & data1, Data & data2)
    // Вариант 2: scoped_lock
    {
        std::scoped_lock lock1(data1.mutex, data2.mutex);

        int temp = data1.scalarData;
        data1.scalarData = data2.scalarData;
        data2.scalarData = temp;
    }

    void swap2(Data& data1, Data& data2)
    // Вариант 3: unique_lock
    {
        unique_lock la(data1.mutex, defer_lock);
        unique_lock lb(data2.mutex, defer_lock);
        int temp = data1.scalarData;
        data1.scalarData = data2.scalarData;
        data2.scalarData = temp;
        lock(la, lb);
    }


int main()
{
    Data data1(1);
    Data data2(2);
    swap(data1, data2);
    cout << "swap1" << endl;
    std::cout << "data1: " << data1.scalarData << std::endl;
    std::cout << "data2: " << data2.scalarData << std::endl;

    swap1(data1, data2);
    cout << "swap2" << endl;
    std::cout << "data1: " << data1.scalarData << std::endl;
    std::cout << "data2: " << data2.scalarData << std::endl;

    swap2(data1, data2);
    cout << "swap3" << endl;
    std::cout << "data1: " << data1.scalarData << std::endl;
    std::cout << "data2: " << data2.scalarData << std::endl;


    return 0;
}