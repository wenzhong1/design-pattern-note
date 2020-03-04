#include <iostream>

using namespace std;

class Base
{
public:
	virtual ~Base()
	{
		cout << "base dconstructor" << endl;
	}
	virtual void method() = 0;
	
	int _data;
};

class RealClass : public Base
{
public:
	virtual void method()
	{
		cout << "RealClass method" << endl;
	}
};

class NullClass : public Base
{
public:
	virtual void method()
	{
		cout << "NullClass method" << endl;
	}
};

class Visitor
{
public:
	Visitor(int num)
	{
		if (num <= 0) {
			_b = new NullClass;
		}
		else {
			_b = new RealClass;
		}
	}
	
	Base* getB()
	{
		return _b;
	}
	
	~Visitor()
	{
		if (!_b) {
			delete _b;
			_b = nullptr;
		}
	}
	
private:
	Base* _b = nullptr;
};

class Client
{
public:
	Client(int num)
	: _v(new Visitor(num))
	{
	}
	
	Visitor* getV()
	{
		return _v;
	}
	
	~Client()
	{
		if (!_v) {
			delete _v;
			_v = nullptr;
		}
	}
	
private:
	Visitor* _v;
};

int main()
{
	Client d(0);
	Visitor* v = d.getV();
	v->getB()->method();
	return 0;
}