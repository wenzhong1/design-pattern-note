#include <iostream>
#include <vector>

//#define TEST_BEFORE //this MACRO used for testing codes without Design Pattern

using namespace std;

#ifdef TEST_BEFORE

/*
 * this class is used for global class type
 */
class GlobalClass
{
public:
    GlobalClass(int v = 0)
    {
        m_value = v;
    }
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
	
private:
	int m_value;
};

// Default initialization, capsule the variable into a namespace
namespace globalVariable
{
GlobalClass *global_ptr = nullptr;
}

using namespace globalVariable;

void foo(void)
{
	// Initialization on first use
	if (!global_ptr)
		global_ptr = new GlobalClass;
	global_ptr->set_value(1);
	cout << "foo: global_ptr is " << global_ptr->get_value() << '\n';
}

void bar(void)
{
	if (!global_ptr)
		global_ptr = new GlobalClass;
	global_ptr->set_value(2);
	cout << "bar: global_ptr is " << global_ptr->get_value() << '\n';
}

int main()
{
	if (!global_ptr)
		global_ptr = new GlobalClass;
	cout << "main: global_ptr is " << global_ptr->get_value() << '\n';
	foo();
	bar();
}

#else 

/**
 * the class own a static pointer to own type
 * the static method to access the pointer
 * outer can't initialize the class
 */
class GlobalClass
{
private:
	GlobalClass(int v = 0)
    {
        m_value = v;
    }

public:
    static GlobalClass* instance()
	{
		if (_instance == nullptr) {
			_instance = new GlobalClass;
		}
		return _instance;
	}
	
    int get_value()
    {
        return m_value;
    }
	
    void set_value(int v)
    {
        m_value = v;
    }
	
private:
	int m_value;
	static GlobalClass* _instance;
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalClass *GlobalClass::_instance = nullptr;

void foo(void)
{
  GlobalClass::instance()->set_value(1);
  cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void)
{
  GlobalClass::instance()->set_value(2);
  cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}
	
#endif

#ifdef TEST_BEFORE
int main()
{
	if (!global_ptr)
		global_ptr = new GlobalClass;
	cout << "main: global_ptr is " << global_ptr->get_value() << '\n';
	foo();
	bar();
	return 0;
}

#else
int main()
{
	cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
	foo();
	bar();
	return 0;
}
	
#endif

