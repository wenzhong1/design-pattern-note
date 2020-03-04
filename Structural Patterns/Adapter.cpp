#include <iostream>
#include <vector>

using namespace std;

// specify the new interface
class ExecuteInterface
{
public:
	virtual ~ExecuteInterface(){};
	virtual void execute() = 0;
};

// design a "Wrapper/Adapter" class
template <typename Type>
class ExecuteAdapter : public ExecuteInterface
{
public:
	ExecuteAdapter(Type *obj, void(Type::*m)())
	{
		_object = obj;
		_method = m;
	}
	~ExecuteAdapter()
	{
		delete _object;
	}
	
	// the adapter/wrapper "maps" the new to the legacy implementation
	void execute()
	{
		(_object->*_method)();
	}

private:
	Type *_object;
	
	void(Type::*_method)();
};

// the old: three totally incompatible classes
// no commom base class
class Fea
{
public:
	~Fea()
	{
		cout << "Fea deconstructor " << endl;
	}
	void doWork()
	{
		cout << "Fea: doWork!" << endl;
	}
};

class Feye
{
public:
	~Feye()
	{
		cout << "Feye deconstructor " << endl;
	}
	
	void doWork()
	{
		cout << "Feye: doWork!" << endl;
	}
};

class Phea
{
public:
	~Phea()
	{
		cout << "Phea deconstructor" << endl;
	}
	void doWork()
	{
		cout << "Phea: doWork!" << endl;
	}
};

// the new is returned

ExecuteInterface** initialize()
{
	ExecuteInterface **array = new ExecuteInterface*[3];
	
	// the old is below
	array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doWork);
	array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doWork);
	array[2] = new ExecuteAdapter<Phea>(new Phea(), &Phea::doWork);
	
	return array;
}

int main()
{
	ExecuteInterface** objects = initialize();
	for (int i = 0; i < 3; ++i) {
		objects[i]->execute();
	}
	
	// clients use the new 
	for (int i = 0; i < 3; ++i) {
		delete objects[i];
	}
	
	delete objects;
	
	return 0;
}
