#include <iostream>
#include <vector>


using namespace std;

class Component
{
public:
	virtual void tranverse() = 0;
	
protected:
	int _value;
};

class ScalarComponent : public Component
{
public:
	ScalarComponent(int value)
	{
		_value = value;
	}
	
	virtual void tranverse()
	{
		cout << "Scalar value: " << _value << endl;
	}
};

class Composite : public Component
{
public:
	Composite(int v)
	{
		_value = v;
	}
	
	void addEle(Component* c)
	{
		_components.push_back(c);
	}
	
	virtual void tranverse()
	{
		for (auto e : _components) {
			e->tranverse();
		}
	}
	
private:
	vector<Component*> _components;
};


int main()
{
	ScalarComponent* sc1 = new ScalarComponent(0);
	ScalarComponent* sc2 = new ScalarComponent(1);
	ScalarComponent* sc3 = new ScalarComponent(2);
	ScalarComponent* sc4 = new ScalarComponent(3);
	Composite* cm1 = new Composite(4);
	Composite* cm2 = new Composite(5);
	
	cm1->addEle(cm2);
	cm1->addEle(sc1);
	cm1->addEle(sc2);
	cm2->addEle(sc3);
	cm2->addEle(sc4);
	
	cm1->tranverse();
	
	return 0;
}