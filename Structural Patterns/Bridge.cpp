#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

class TimeImp
{
public:
	TimeImp(int hr, int mi)
	: _hr(hr)
	, _mi(mi)
	{
	}
	
	virtual void tell()
	{
		cout << " time is: " << setw(2) << setfill('0') << _hr << _mi << endl;
	}
	
protected:
	int _hr;
	int _mi;
};

class CivilianTimeImp : public TimeImp
{
public:
	CivilianTimeImp(int hr, int mi, bool pm)
	: TimeImp(hr, mi)
	{
		if (pm) {
			strcpy(whichM, "PM");
		}
		else {
			strcpy(whichM, "AM");
		}
	}
	
	virtual void tell()
	{
		cout << "time is " << setw(2) << setfill('0') << _hr << ":" << _mi << whichM << endl;
	}
	
private:
	char whichM[4];
};

class ZuluTimeImp: public TimeImp {
  public:
    ZuluTimeImp(int hr, int mi, int zone): TimeImp(hr, mi) {
        if (zone == 5)
          strcpy(_zone, " Eastern Standard Time");
        else if (zone == 6)
          strcpy(_zone, " Central Standard Time");
    }

    virtual void tell() {
        cout << "time is " << setfill('0') << setw(2) << _hr << ":" << _mi << _zone <<
          endl;
    }
  protected:
    char _zone[30];
};

class Time
{
public:
	virtual ~Time()
	{
		if (_imp != nullptr) {
			cout << " deconstructor ！ " << endl;
			delete _imp;
		}
	}
	
	Time(){}
	Time(int hour, int minute)
	{
		_imp = new TimeImp(hour, minute);
	}
	
	virtual void tell()
	{
		_imp->tell();
	}
	
protected:
	TimeImp* _imp;
};

class CivilianTime : public Time
{
public:
	CivilianTime(int hour, int minute, bool pm)
	{
		_imp = new CivilianTimeImp(hour, minute, pm);
	}
};

class ZuluTime : public Time
{
public:
	ZuluTime(int hour, int minute, int zone)
	{
		_imp = new ZuluTimeImp(hour, minute, zone);
	}
};

int main()
{
	Time *times[3];
	times[0] = new Time(14, 30);
	times[1] = new CivilianTime(2, 30, true);
	times[2] = new ZuluTime(14, 30, 6);
	
	for (auto time : times) {
		time->tell();
		delete time;
	}
	
	return 0;
}
