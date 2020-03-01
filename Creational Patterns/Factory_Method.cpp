#include <iostream>
#include <vector>

#define TEST_BEFORE //this MACRO used for testing codes without Design Pattern

using namespace std;

#ifdef TEST_BEFORE

// use a abstract base class to realize polymophic without abstract method

/**
 * abstrat base class
 */
class Stooge
{
public:
	virtual void slap_stick() = 0;
};

class Larry : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Larry: poke eyes" << endl;
	}
};

class Moe : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Moe: slap head" << endl;
	}
};

class Curly :public Stooge
{
public:
	void slap_stick()
	{
		cout << "Curly: suffer abuse" << endl;
	}
};

#else 

/**
 * abstrat base class
 * contain a Factory Method
 */
class Stooge
{
public:
	// Factory Method
	static Stooge* make_stooge(int roleIndex);
	virtual void slap_stick() = 0;
};

class Larry : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Larry: poke eyes" << endl;
	}
};

class Moe : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Moe: slap head" << endl;
	}
};

class Curly :public Stooge
{
public:
	void slap_stick()
	{
		cout << "Curly: suffer abuse" << endl;
	}
};

Stooge* Stooge::make_stooge(int roleIndex)
{
	if (roleIndex == 1) {
		return new Larry;
	}
	else if (roleIndex == 2) {
		return new Moe;
	}
	else if (roleIndex == 3) {
		return new Curly;
	}
	else {
		cout <<"the int value exceed the range of receivable values[1-3]: " << roleIndex << endl;
		exit(1);
	}
}
	
#endif

#ifdef TEST_BEFORE
int main()
{
	vector<Stooge*> roles;
	for (int i = 0; i < 5; ++i) {
		if (i % 3 == 0) {
			roles.push_back(new Larry);
		}
		else if (i % 3 == 1) {
			roles.push_back(new Moe);
		}
		else {
			roles.push_back(new Curly);
		}
	}
	
	for (auto role : roles) {
		role->slap_stick();
	}
	for (auto role : roles) {
		delete role;
	}
	return 0;
}

#else
int main()
{
	vector<Stooge*> roles;
	for (int i = 1; i < 4; ++i) {
		roles.push_back(Stooge::make_stooge(i));
	}
	
	for (auto role : roles) {
		role->slap_stick();
	}
	for (auto role : roles) {
		delete role;
	}
	
	return 0;
}
	
#endif

