#include <iostream>

using namespace std;

class Memento
{
public:
	Memento(int val)
	{
		_state = val;
	}
private:
	friend class Number;
	int _state;
};

class Number
{
public:
	Number(int val)
	{
		_value = val;
	}
	
	void doubleValue()
	{
		_value = 2 * _value;
	}
	
	void half()
	{
		_value = _value / 2;
	}
	
	int getValue()
	{
		return _value;
	}
	
	Memento* createMemento()
	{
		return new Memento(_value);
	}
	
	void reinstateMemento(Memento* mem)
	{
		_value = mem->_state;
	}
	
private:
	int _value;
};

class Command
{
public:
	typedef void(Number::*Action)();
	
	Command(Number *receiver, Action action)
	{
		_receiver = receiver;
		_action = action;
	}
	
	virtual void execute()
	{
		if (_numCommands == 20) {
			cout << " reach the capacity  " << endl;
			return ;
		}
		_mementoList[_numCommands] = _receiver->createMemento();
		_commandList[_numCommands] = this;
		if (_numCommands > _highWater) {
			_highWater = _numCommands;
		}
		
		_numCommands++;
		(_receiver->*_action)();
	}
	
	static void undo()
	{
		if (_numCommands == 0) {
			cout << "*** Attempt to run off the end! ***" << endl;
			return ;
		}
		
		_commandList[_numCommands - 1]->_receiver->reinstateMemento(\
		_mementoList[_numCommands - 1]);
		_numCommands--;
	}
	
	static void redo()
	{
		if (_numCommands == 20 || _numCommands == 0) {
			return;
		}
		if (_numCommands > _highWater) {
			cout << "*** Attemp to run off the end!! ***" << endl;
			return;
		}
		(_commandList[_numCommands - 1]->_receiver->*(_commandList[_numCommands - 1]->_action))();
		_numCommands++;
	}
	
protected:
	Number* _receiver;
	Action	_action;
	static Command* _commandList[20];
	static Memento* _mementoList[20];
	static int      _numCommands;
	static int 		_highWater;
};

Command* Command::_commandList[];
Memento* Command::_mementoList[];
int Command::_numCommands = 0;
int Command::_highWater = 0;

int main()
{
	int i;
	cout << "Integer: " << endl;
	cin >>i;
	Number *object = new Number(i);
	
	Command* commands[3];
	commands[1] = new Command(object, &Number::doubleValue);
	commands[2] = new Command(object, &Number::half);
	
	cout << "Exit[0], DoubleValue[1], HalfValue[2], Undo[3], Redo[4]: ";
	cin >> i;
	
	while (i) {
		if (i == 3) {
			Command::undo();
		}
		else if (i == 4) {
			Command::redo();
		}
		else if (i == 1 || i == 2) {
			commands[i]->execute();
		}
		
		cout << "  " << object->getValue() << endl;
		cout << "Exit[0], DoubleValue[1], HalfValue[2], Undo[3], Redo[4]: ";
		cin >> i;
	}
	return 0;
}
	