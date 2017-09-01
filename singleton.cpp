#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

class Singleton {
private:
    static mutex mtx;
    class Guard {
    public:
        ~Guard() {
            if (Singleton::instance) {
                delete Singleton::instance;
            }
        }
    };
    static Guard guard;

private:
    Singleton() : value(0) {}
    Singleton(const Singleton&);
    const Singleton& operator=(const Singleton&);

    static Singleton* instance;

public:
    static Singleton* getInstance() {
        // Lazy pattern with double-check lock.
        if (instance == NULL) {
            mtx.lock();

            if (instance == NULL) {
                instance = new Singleton();
            }

            mtx.unlock();
        }

        return instance;
    }

    int value;
    void updateValue() {
        //mtx.lock();

        // Do sth in critical section.
        this_thread::sleep_for(chrono::milliseconds(50));
        value++;
        cout << value << endl;

        //mtx.unlock();
    }

    int getValue() {
        return value;
    }
};
mutex Singleton::mtx;
Singleton* Singleton::instance = NULL;

// Hungry pattern.
// Singleton* Singleton::instance = new Singleton();

void storeValue(Singleton* s) {
    if (s != NULL) {
        s->updateValue();
    }
}

int main() {
    Singleton* s = Singleton::getInstance();

    vector<thread*> threads(50);

    for (int i = 0; i < 50; ++i)
        threads[i] = new thread(storeValue, s);

    for (auto t : threads)
        t->join();

    return 0;
}