#include <iostream>

using namespace std;

// the lowest base class

class Widget
{
public:
	virtual void draw() = 0;
};

class TextField : public Widget
{
public:
	TextField(int w, int h)
	: width(w)
	, height(h)
	{
	}
	
	virtual void draw()
	{
		cout << "TextField: " << width << '\t' << height << endl;
	}
	
private:
	int width, height;
};

class Decorator : public Widget
{
public:
	Decorator(Widget* w)
	: _w(w)
	{
	}
	
	virtual void draw()
	{
		_w->draw();
	}
	
private:
	Widget* _w;
};

class BorderDecorator : public Decorator
{
public:
	BorderDecorator(Widget* w)
	: Decorator(w)
	{
	}
	
	virtual void draw()
	{
		Decorator::draw();
		cout << "BorderDecorator..." << endl;
	}
};

class ScrollDecorator : public Decorator
{
public:
	ScrollDecorator(Widget* w)
	: Decorator(w)
	{
	}
	
	virtual void draw()
	{
		Decorator::draw();
		cout << "ScrollDecorator..." << endl;
	}
};

int main()
{
	Widget* w = new ScrollDecorator(new ScrollDecorator(\
	new BorderDecorator(new TextField(100,30))));
	w->draw();
	
	return 0;
}