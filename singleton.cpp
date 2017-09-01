#include <mutex>
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
    Singleton() {}
    Singleton(const Singleton&);
    const Singleton& operator=(const Singleton&);

    static Singleton* instance;

public:
    static Singleton* getInstance() {
        // Lazy pattern with double-check lock.
        if (instance == NULL) {
            if (mtx.try_lock()) {
                if (instance == NULL) {
                    instance = new Singleton();
                }

                mtx.unlock();
            }
        }

        return instance;
    }

    int value;
    void setValue(int x) {
        if (mtx.try_lock()) {
            value = x;
        
            mtx.unlock();
        }
    }

    int getValue() {
        return value;
    }
};

// Hungry pattern.
// Singleton* Singleton::instance = new Singleton();

int main(){
    return 0;
}