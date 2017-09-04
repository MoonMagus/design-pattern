#include <iostream>
using namespace std;

class Component {
public:
    virtual void print() = 0;
};

class Decorator : public Component {
public:
    virtual void speak() = 0;
};

class concreteComponent : public Component {
public:
    virtual void print() override {
        cout << "I am component and will call print(): 'Component'" << endl;
    }
};

class concreteDecorator : public Decorator {
private:
    Component& component;

public:
    concreteDecorator(Component& c) : component(c) {}

    virtual void print() override {
        component.print();
    }

    virtual void speak() override {
        cout << "I am decorator and will call speak(): 'Decorator'" << endl;
    }
};


int main() {
    Component& c = concreteComponent();
    Decorator& d = concreteDecorator(c);
    d.print();
    d.speak();

    return 0;
}