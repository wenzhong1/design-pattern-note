#include <iostream>
#include <list>
#include <memory>
#include <string>

using namespace std;

class Observer;

class Subject
{
public:
    Subject()
    : _value(0)
    {
    }

    void attach(shared_ptr<Observer> ob)
    {
        _oblist.push_back(ob);
    }

    void setValue(int v)
    {
        _value = v;
        notify();
    }

    int getValue() const
    {
        return _value;
    }

    void notify();
private:
    int _value;
    list<shared_ptr<Observer>> _oblist;
};

class Observer : public enable_shared_from_this<Observer>
{
public:
    Observer(const string& s)
    : _name(s)
    {
    }

    void subscribe(shared_ptr<Subject> sub)
    {
        _sub = sub;
        auto tmp = shared_from_this();
        _sub->attach(tmp);
    }

    virtual void update() = 0;

protected:
    shared_ptr<Subject> _sub;
    string _name;
};

class MikeObserver : public Observer
{
public:
    MikeObserver(const string& str) : Observer(str)
    {
    }

    virtual void update()
    {
        cout << _name << ": " << _sub->getValue() << endl;;
    }

};

void Subject::notify()
{
    for (auto ob : _oblist) {
        ob->update();
    }
}

int main()
{
    auto sub = make_shared<Subject>();
    auto ob1 = make_shared<MikeObserver>("ob1");
    ob1->subscribe(sub);
    auto ob2 = make_shared<MikeObserver>("ob2");
    ob2->subscribe(sub);
    auto ob3 = make_shared<MikeObserver>("ob3");
    ob3->subscribe(sub);

    sub->setValue(100);
    sub->setValue(1000);

    return 0;
}
