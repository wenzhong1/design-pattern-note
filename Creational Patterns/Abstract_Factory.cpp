#include <iostream>

#define PLATFORMS 1
#define TEST_BEFORE

using namespace std;

#ifdef TEST_BEFORE

/**
 * Abstract base product
 */
class Widget
{
public:
	virtual void draw() = 0;
};

/**
 * Concrete product family 1.
 */
class LinuxButton : public Widget
{
public:
	void draw()
	{
		cout << "LinuxButton" << endl;
	}
};

class LinuxMenu : public Widget
{
public:
	void draw()
	{
		cout << "LinuxMenu" << endl;
	}
};

/**
 *Concrete product family 2.
 */
class WindowsButton : public Widget
{
public:
	void draw()
	{
		cout << "WindowsButton" << endl;
	}
};

class WindowsMenu : public Widget
{
public:
	void draw()
	{
		cout << "WindowsMenu" << endl;
	}
};

/**
 * Here's a client, which uses concrete products directly.
 * It's code will full of nasty MACRO switch statements
 * which check the product type 
 */
class Client
{
public:
	void draw()
	{
#ifdef PLATFORMS
	#if PLATFORMS == 1
		Widget *w = new LinuxButton;
	#else
		WIdget *w = new WindowsButton;
	#endif
#else
#error PLATFORMS is not defined
#endif
	w->draw();
	display_window_one();
	display_window_two();
	}
	
	void display_window_one()
	{
#ifdef PLATFORMS
	#if PLATFORMS == 1
		Widget *w[] = {
			new LinuxButton,
			new LinuxMenu
		};
	#else
		Widget *w[] = {
			new WindowsButton,
			new WindowsMenu
		};
	#endif
#else 
#error PLATFORMS is not defined
#endif
		w[0]->draw();
		w[1]->draw();
	}
	
	void display_window_two()
	{
#ifdef PLATFORMS
	#if PLATFORMS == 1
		Widget *w[] = {
			new LinuxMenu,
			new LinuxButton
		};
	#else
		Widget *w[] = {
			new WindowsMenu;
			new WindowsButton;
		};
	#endif
#else 
#error PLATFORMS is not defined
#endif
		w[0]->draw();
		w[1]->draw();
	}
};

#else 

/**
 * Abstract base product. It should define an interface 
 * which will be common to all products. Clients will 
 * work with products through this interface, so it 
 * should be sufficient to use all products.
 */
class Widget
{
public:
	virtual void draw() = 0;
};

/**
 * Concrete product family 1.
 */
class LinuxButton : public Widget
{
public:
	void draw()
	{
		cout << "LinuxButton" << endl;
	}
};

class LinuxMenu : public Widget
{
public:
	void draw()
	{
		cout << "LinuxMenu" << endl;
	}
};

/**
 *Concrete product family 2.
 */
class WindowsButton : public Widget
{
public:
	void draw()
	{
		cout << "WindowsButton" << endl;
	}
};

class WindowsMenu : public Widget
{
public:
	void draw()
	{
		cout << "WindowsMenu" << endl;
	}
};

/**
 * Abstract factory defines method to create all 
 * related product.
 */
class Factory
{
public:
	virtual Widget* create_button() = 0;
	virtual Widget* create_menu() = 0;
};

/**
 * Each concrete factory corresponds to one product
 * family. It creates all possible products of
 * one kind.
 */
class LinuxFactory : public Factory
{
	Widget *create_button()
	{
		return new LinuxButton;
	}
	
	Widget *create_menu()
	{
		return new LinuxMenu;
	}
};

class WindowsFactory : public Factory
{
public:
	Widget *create_button()
	{
		return new WindowsButton;
	}
	
	Widget *create_menu()
	{
		return new WindowsMenu;
	}
};

/**
 * Client receives a factory object from its creator.
 * 
 * All clients work with factories through abstract
 * interface. They don't know concrete classes of factories.
 * Because of this, you can interchange concrete factories without breaking clients.
 */
class Client
{
private:
	Factory *factory;
	
public:
	Client(Factory *f)
	{
		factory = f;
	}
	
	void draw()
	{
		Widget *w = factory->create_button();
		w->draw();
		display_window_one();
		display_window_two();
	}
	
	void display_window_one()
	{
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};
		w[0]->draw();
		w[1]->draw();
	}
	
	void display_window_two()
	{
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};
		w[0]->draw();
		w[1]->draw();
	}
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
	Factory *f = new WindowsFactory;
	Client *c = new Client(f);
	cout << "Abstract Function" << endl;
	c->draw();
	return 0;
}
	
#endif

