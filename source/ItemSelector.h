#include <string>
#include <vector>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Group.H>

class MenuItem
{
public:
	enum Type
	{
		CATEGORY,
		ITEM,
	};

	std::string getName()
	{
		return this->name;
	}

private:
	int id;
	int stock;
	double price;
	
	std::string name;
	std::string description;

	MenuItem::Type itemType;

	// MenuItem::children is only used when the type is MenuItem::Type.CATEGORY

	std::vector<MenuItem> children;

};

class ItemSelector : public Fl_Group
{
private:
	std::vector<MenuItem> menuItems;
	std::string currentPath;

	// Widgets in this widget
	
	// I figured out how to make these not pointers, so we can do better coding habits for C++ from now on.
	// The main class below needs an entire rewrite to not use pointers.

	Fl_Input pathInput;
	Fl_Button homeButton;
	Fl_Group selectorGroup;

	// Variables for positioning main (parent) and child elements.
	
	int x, y;
	int width, height;

public:
	void addItem(MenuItem item);
	void removeItem(int id);

	void populateMenu(std::string internalPath);

	// Unfortunately, a bug prevents us from using std::string here.
	// Using std::string for label causes garbage to be printed as the Fl_Group
	// label.

	ItemSelector(int x, int y, int w, int h, const char *label);

			
	int handle(int event)
	{
		redraw();
		if(Fl_Group::handle(event)) return 1;
	}
};


