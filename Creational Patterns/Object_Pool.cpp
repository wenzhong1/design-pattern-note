#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Resource
{
public:
	Resource(int value = 0) : _value(value) 
	{
	}
	
	int getValue() const
	{
		return _value;
	}
	
	void setValue(int v)  
	{
		_value = v;
	}
	
	void reset()
	{
		setValue(0);
	}
	
private:
	int _value = 0;
};

/*
 * This is a singleton
 */
class ObjectPool
{
private:
	ObjectPool();
	ObjectPool(int size, int capacity) : _size(size), _capacity(capacity)
	{
	}
	ObjectPool(const ObjectPool&);
	ObjectPool& operator=(const ObjectPool&);
	
public:
	static ObjectPool* getInstance()
	{
		 if (_instance == nullptr) {
			 _instance = new ObjectPool(0, 3);
		 }
		 return _instance;
	}
	
	Resource* getResource()
	{
		if (_resources.empty()) {
			if (_size < _capacity) {
				++_size;
				return new Resource;
			}
			else {
				cout << "objects' number reaches the capacity!" << endl;
				return nullptr;
			}
		}
		else {
			auto tmp = _resources.front();
			_resources.pop_front();
			--_size;
			return tmp;
		}
	}
	
	void restoreResource(Resource* r)
	{
		if (!r) {
			cout << " the resource is null" << endl;
		}
		else {
			r->reset();
			_resources.push_back(r);
		}
	}
private:
	static ObjectPool* _instance;
	list<Resource*> _resources;
	int _size;
	int _capacity;
};

ObjectPool* ObjectPool::_instance = nullptr;

int main()
{
	ObjectPool* pool = ObjectPool::getInstance();
	vector<Resource*> rVec;
	
	for (int i = 0; i < 5; ++i) {
		rVec.push_back(pool->getResource());
	}
	for (auto r : rVec) {
		pool->restoreResource(r);
	}
	
	return 0;
}