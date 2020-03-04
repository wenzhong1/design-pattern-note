#include <iostream>
#include <string>

using namespace std;

template<typename _Class, typename _RMtype, typename _RFtype>
class Command
{
	using mm_ptr = _RMtype	_Class::*;
	typedef _RFtype (_Class:: *mf_ptr)(); // using mf_ptr = _RFtype (_Class::*)();
public:
	Command(_Class* obj = nullptr, mf_ptr method = nullptr, mm_ptr member = nullptr)
	: _object(obj)
	, _pubMethod(method)
	, _pubMember(member)
	{
	}
	
	void execute()
	{
		cout << "The object id" << _object->*_pubMember << endl;
		if (!_object || !_pubMember || !_pubMethod)
			return;
		(_object->*_pubMethod)();
	}

private:
	_Class* _object;
	mf_ptr	_pubMethod;
	mm_ptr	_pubMember;
};
	
class Person
{
public:
	Person(string name, Command<Person, int, void> c) 
	: mem(100)
	, _cmd(c)
	, _name(name)
	{
	}
	
	void talk()
	{
		cout << _name << " is talking " << endl;
		_cmd.execute();
	}
	
	void passOn()
	{
		cout << _name << " is passing on " << endl;
		_cmd.execute();
	}
	
	void gossip()
	{
		cout << _name << " is gossiping " << endl;
		_cmd.execute();
	}
	
	void listen()
	{
		cout << _name << " is listening " << endl;
		_cmd.execute();
	}
	
public:
	int mem = 0;
	
private:
	Command<Person, int, void> _cmd;
	string _name;
};

int main()
{
	Person MrA("MrA", Command<Person, int, void>());
	
	Person MrB("MrB", Command<Person, int, void>(&MrA, &Person::listen, &Person::mem));
	Person MissA("MissA", Command<Person, int , void>(&MrB, &Person::gossip, &Person::mem));
	Person MissB("MissB", Command<Person, int, void>(&MissA, &Person::passOn, &Person::mem));
	
	MissB.talk();
	
	return 0;
}
