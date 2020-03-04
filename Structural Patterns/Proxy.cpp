#include <iostream>
#include <string>

using namespace std;

class Subject
{
public:
	virtual void execute() = 0;
};

class RealSubject : public Subject
{
public:
	RealSubject(string s)
	{
		_str = s;
	}
	
	virtual void execute()
	{
		cout << "!!!" << _str << endl;
	}
	
private:
	string _str;
};

class ProxySubject : public Subject
{
public:
	ProxySubject(string s)
	{
		int num = s.find_first_of(' ');
		first = s.substr(0, num);
		s = s.substr(num + 1);
		num = s.find_first_of(' ');
		second = s.substr(0, num);
		s = s.substr(num + 1);
		num = s.find_first_of(' ');
		third = s.substr(0, num);
		s = s.substr(num + 1);
		
		pRealSub = new RealSubject(s);
	}
	
	~ProxySubject()
	{
		delete pRealSub;
	}
	
	RealSubject *operator->()
	{
		cout << first << "***" << second << ' ';
		return pRealSub;
	}
	
	virtual void execute()
	{
		cout << first << "###" << third << ' ';
		pRealSub->execute();
	}

private:
	string first, second, third;
	RealSubject* pRealSub;
};

int main()
{
	ProxySubject* obj = new ProxySubject(string("the quick brown fox jumped over the dog"));
	(*obj)->execute();
	//obj.execute();
};