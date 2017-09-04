#include <unordered_Set>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct Data {
    string message;
    Data(string m) : message(m) {}
};

class Subject;
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(Subject*, Data&) = 0;
};

class Subject {
public:
    virtual ~Subject() {}
    virtual void registerObserver(Observer*) = 0;
    virtual void removeObserver(Observer*) = 0;
    virtual void notifyAll() = 0;
};

class People :public Observer {
private:
    Subject& subject;

public:
    People(Subject& s) : subject(s) {
        s.registerObserver(this);
    }
    virtual ~People() override {}
    virtual void update(Subject* s, Data& d) override {
        cout << "People class was updated: " << d.message<< endl;
    }
};

class Newspaper : public Subject {
private:
    unordered_set<Observer*> observers;

public:
    virtual ~Newspaper() override {}

    virtual void registerObserver(Observer* o)  override {
        observers.insert(o);
    }

    virtual void removeObserver(Observer* o) override {
        unordered_set<Observer*>::iterator it = observers.find(o);
        if (it != observers.end())
            observers.erase(it);
    }

    virtual void notifyAll() override {
        int index = 0;
        for (auto o : observers) {
            Data d(to_string(++index));
            o->update(this, d);
        }
    }
};

int main() {
    Subject& s = Newspaper();
    Observer& o1 = People(s);
    Observer& o2 = People(s);
    Observer& o3 = People(s);
    s.notifyAll();

    return 0;
}