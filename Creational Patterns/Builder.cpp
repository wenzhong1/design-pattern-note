#include <iostream>
#include <string>
#include <vector>

//#define TEST_BEFORE //this MACRO used for testing codes without Design Pattern

using namespace std;

#ifdef TEST_BEFORE

/**
 *  
 *
 */


#else 

/*
 * The saveType
 */
enum PersistenceType
{
	File,
	Queue,
	Pathway
};

/*
 * the assemble attribute
 */
struct PersistenceAttribute
{
	PersistenceType type;
	string value;
};

class DistrWorkPackage
{
public:
	DistrWorkPackage(const string& client)
	{
		_resPackage += "Distributed Work Package for: ";
		_resPackage += client;
	}
	
	void compack(const PersistenceType pType, const string& type, const string& name)
	{
		if (File == pType) {
			_resPackage += "\n File(" + type + "): ";
		}
		else if (Queue == pType) {
			_resPackage += "\n Queue(" + type + "): ";
		}
		else {
			_resPackage += "\n Pathway(" + type + "): ";
		}
		_resPackage += name;
	}
	
	string getState()
	{
		return _resPackage;
	}
	
private:
	string _resPackage;
};
		

class Builder
{
public:
	virtual void configureFile(const string& name) = 0;
	virtual void configureQueue(const string& name) = 0;
	virtual void configurePathway(const string& name) = 0;
	DistrWorkPackage* getResult()
	{
		return _result;
	}
	
protected:
	DistrWorkPackage* _result;
};

class UnixBuilder : public Builder
{
public:
	UnixBuilder()
	{
		_result = new DistrWorkPackage("Unix");
	}
	
	void configureFile(const string& name)
	{
		_result->compack(File, "flatFile", name);
	}
	void configureQueue(const string& name)
	{
		_result->compack(Queue, "FIFO", name);
	}
	
	void configurePathway(const string& name)
	{
		_result->compack(Pathway, "thread", name);
	}
};

class VmsBuilder : public Builder
{
public:
	VmsBuilder()
	{
		_result = new DistrWorkPackage("Vms");
	}
	
	void configureFile(const string& name)
	{
		_result->compack(File, "ISAM", name);
	}
	void configureQueue(const string& name)
	{
		_result->compack(Queue, "Priority", name);
	}
	
	void configurePathway(const string& name)
	{
		_result->compack(Pathway, "LWP", name);
	}
};

class Reader
{
public:
	void setBuilder(Builder *b)
	{
		_builder = b;
	}
	
	void constructor(vector<PersistenceAttribute> pArr)
	{
		for (PersistenceAttribute persistence : pArr) {
			if (persistence.type == File) {
				_builder->configureFile(persistence.value);
			}
			else if (Queue == persistence.type) {
				_builder->configureQueue(persistence.value);
			}
			else {
				_builder->configurePathway(persistence.value);
			}
		}
	}

private:
	Builder* _builder;
};
	
#endif

#ifdef TEST_BEFORE
int main()
{
	Client *c = new Client;
	cout << "MACRO switch" << endl;
	c->draw();
	return 0;
}

#else
int main()
{
	vector<PersistenceAttribute> input = 
	{
		{
			File, "state.dat"
		}
		, 
		{
			File, "config.sys"
		}
		, 
		{
			Queue, "compute"
		}
		, 
		{
			Queue, "log"
		}
		, 
		{
			Pathway, "authentication"
		}
		, 
		{
			Pathway, "error processing"
		}
	};
	UnixBuilder unixBuider;
	VmsBuilder vmsBuilder;
	Reader reader;
	
	reader.setBuilder(&unixBuider);
	reader.constructor(input);
	cout << unixBuider.getResult()->getState() << endl;
	
	reader.setBuilder(&vmsBuilder);
	reader.constructor(input);
	cout << vmsBuilder.getResult()->getState() << endl;
	
	return 0;
}
	
#endif

