#include "ItemSelector.h"

// Initialize widgets and show UI

/* NOTE: making label a std::string causes a strange bug. The bug causes the
 |label to appear as garbage characters instead of the intended label. We
 | are making label a const char* instead of an std::string for this reason.
 |------------------------------------------------------------------------------
 | TESTS: Using .c_str() is the method that the string was passed to the label
 | parameter/argument.
 |------------------------------------------------------------------------------
 | WORKAROUND: Use const char* instead.
 |------------------------------------------------------------------------------
 | CURRENT STATUS: Not fixing
*/

ItemSelector::ItemSelector(int x, int y, int w, int h, const char *label)
	: 	Fl_Group	(x    , y     , w     , h     , label),
		pathInput	(x + 2, y + 2 , w - 4 , 30    ),
		homeButton	(x + 2, y + 34, w - 4 , 30    , "CATEGORIES"),
		selectorGroup	(x + 5, y + 66, w - 10, h - 71)
{

	// Set up positioning "box" (x, y, width, height)
	
	this->x	= x;
	this->y	= y;
	width	= w;
	height	= h;

	// Set up widgets with appropriate styling and callbacks
	
	box(FL_FLAT_BOX);
	color(0xe0e0ff00);

	pathInput.box(FL_FLAT_BOX);
	pathInput.color(pathInput.parent()->color() - 0x11111100);
	pathInput.value("MENU://");

	homeButton.box(FL_FLAT_BOX);
	homeButton.color(homeButton.parent()->color() - 0x11111100);

	selectorGroup.color(0xffffff00);
	selectorGroup.box(FL_FLAT_BOX);

	// Make sure to end the Fl_Groups. It's very important.

	selectorGroup.end();
	end();

}

// Populate the menu showing an internal folder. Not an actual folder on the
// system.

void ItemSelector::populateMenu(std::string internalPath)
{
	
}

// Add an item to the menuItems vector (std::vector<MenuItem> menuItems)

void ItemSelector::addItem(MenuItem item)
{
	this->menuItems.push_back(item);
}
