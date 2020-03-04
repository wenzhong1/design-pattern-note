#include <iostream>

using namespace std;

class State;

class Machine
{
public:
	Machine();
	
	void on();
	
	void off();
	
	void setState(State* s)
	{
		_state = s;
	}
	
private:
	State* _state;
};

class State
{
public:
	State()
	{}
	
	virtual void on(Machine* m)
	{
		cout << "Already on" << endl;
	}
	
	virtual void off(Machine* m)
	{
		cout << "Already off" << endl;
	}
	
};

class ON : public State
{
public:
	ON()
	{
	}
	
	virtual void off(Machine* m) override;
};

class OFF : public State
{
public:
	OFF()
	{}
	
	virtual void on(Machine* m) override;
	
};

void Machine::on()
{
	_state->on(this);
}

void Machine::off()
{
	_state->off(this);
}

void ON::off(Machine* m)
{
	m->setState(new OFF);
	delete this;
}

void OFF::on(Machine* m)
{
	m->setState(new ON);
	delete this;
}

Machine::Machine()
{
	_state = new OFF();
}

int main()
{
	void (Machine::*mfs[])() = {&Machine::on, &Machine::off};
	Machine m;
	(m.*mfs[0])();
	(m.*mfs[1])();
	
	return 0;
}