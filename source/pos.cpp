#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ios>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include "include/transaction.h"

// Explode a string. Works similar to PHP explode and JS String.split

std::vector<std::string> explode(std::string in, const char delim)
{
	std::stringstream buffer;
	std::vector<std::string> explodedVector;

	// Iterate over string and break it into substrings, then add it to explodedVector

	for(int i=0; i<in.size(); i++)
	{
		const char compareCharacter = in[i];

		if(compareCharacter == delim)
		{
			// Delimiter found in string, extract stringstream to a new explodedVector element.

			std::string extractedString{buffer.str()};
			explodedVector.push_back(extractedString);
			buffer.str("");
			std::cout << "Exploded string: \"" << extractedString << "\"" << std::endl;
		}
		else
		{
			// Not currently the delimiter; add current character to buffer.

			buffer << compareCharacter;
		}
	}

	if(buffer.str().size() > 0)
	{
		std::cout << "Flushing buffer to vector..." << std::endl;
		explodedVector.push_back(buffer.str());
	}
	
	return explodedVector;
}

// Check if file exists by checking the response of stat.

bool fileExists(std::string filename)
{
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

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
	

public:
	void addItem(MenuItem item);
	void removeItem(int id);

	void populateMenu()
	{
		
	}

	// Unfortunately, a bug prevents us from using std::string here.
	// Using std::string for label causes garbage to be printed as the Fl_Group
	// label.

	ItemSelector(int x, int y, int w, int h, const char *label)
		: 	Fl_Group(x,y,w,h,label),
			pathInput(x+2,y+4,w-64,26),
			homeButton(x+(w-62),y+4,56,26, "Home"),
			selectorGroup(x+4,y+32,w-8,h-32)
			
	{
		box(FL_FLAT_BOX);
		color(0xffffff00);

		pathInput.box(FL_FLAT_BOX);
		pathInput.color(pathInput.parent()->color() - 0x11111100);
		pathInput.value("MENU://");

		homeButton.box(FL_FLAT_BOX);
		homeButton.color(homeButton.parent()->color() - 0x11111100);

		selectorGroup.end();
		end();
	}

	int handle(int event)
	{
		redraw();
		if(Fl_Group::handle(event)) return 1;
	}
};

class POS
{
private:
	Fl_Window *window;

	// Current Transaction Group

	Fl_Group *currentTransactionGroup;
	Fl_Box *currentTransactionLabel;
	Fl_Scroll *currentTransactionList;

	Fl_Button *cancelTransactionButton;
	Fl_Return_Button *confirmTransactionButton;
	
	// Main View Group

	Fl_Tabs *mainViewTabs;
	Fl_Group *addItemsGroup;
	Fl_Group *previousTransactionsGroup;
	Fl_Group *statisticsGroup;

	// Items Tree
	
	ItemSelector *itemSelector;
	
	Fl_Tree_Item *foodsItem;
	std::vector<Fl_Tree_Item*> foodItems;
	
	Fl_Tree_Item *drinksItem;
	std::vector<Fl_Tree_Item*> drinkItems;
	
	// Application Variables

	std::vector<Transaction> transactions;

	std::string title{"CHHS - Point Of Sales Interface"};

	int left = 20;
	int top = 20;
	int width = 640;
	int height = 480;

	int sidebarWidth = 250;
	int mainViewLeft = sidebarWidth + 2;

	std::string foodFileName{"food.axtf"};
	std::string drinksFileName{"drinks.axtf"};
	

public:
	POS() {
		window = new Fl_Window(left, top, width, height, title.c_str());


		currentTransactionGroup = new Fl_Group(0, 0, sidebarWidth, height);
		{
			currentTransactionGroup->box(FL_UP_BOX);
			currentTransactionLabel = new Fl_Box(2, 2, sidebarWidth - 4, 25, "Current Transaction");

			currentTransactionList = new Fl_Scroll(2, 30, sidebarWidth - 4, height - 90);
			currentTransactionList->type(Fl_Scroll::VERTICAL_ALWAYS);
			currentTransactionList->box(FL_UP_FRAME);
			
			currentTransactionList->end();

			cancelTransactionButton = new Fl_Button(2, height - 58, sidebarWidth - 4, 25, "Cancel Transaction");
			cancelTransactionButton->color(0xff404000);

			confirmTransactionButton = new Fl_Return_Button(2, height - 31, sidebarWidth - 4, 29, "Confirm Transaction");

		}
		currentTransactionGroup->end();

		mainViewTabs = new Fl_Tabs(sidebarWidth + 4, 0, width - sidebarWidth - 4, height);
		{
			addItemsGroup = new Fl_Group(mainViewLeft, 27, width - mainViewLeft, height - 27, "Add Items");
			{
				itemSelector = new ItemSelector(mainViewLeft + 2, 29, width - mainViewLeft - 4, height - 27 - 4, "");

			}
			addItemsGroup->end();

			previousTransactionsGroup = new Fl_Group(mainViewLeft, 27, width - mainViewLeft, height - 27, "Previous Transactions");
			{
			}
			previousTransactionsGroup->end();

			statisticsGroup = new Fl_Group(mainViewLeft, 27, width - mainViewLeft, height - 27, "Statistics");
			{

			}
			statisticsGroup->end();
		}
		mainViewTabs->end();

		window->resizable(addItemsGroup);

		window->end();
	}

	void fetchFood()
	{

		if(!fileExists(foodFileName)) 
		{
			std::cout << "WARN: No food file. No food will be available." << std::endl;
		}

		std::ifstream foodFile;

		foodFile.open(foodFileName);

		while(true)
		{
			std::string foodLine;

			std::getline(foodFile, foodLine);
			
			std::vector<std::string> foodItem{explode(foodLine, ':')};

			if(foodItem.size() < 2)
			{
				std::cout << "WARN: Failed to parse food item \"" << foodLine << "\". This item will be unable to be used in transactions." << std::endl;
				std::string itemLabel{"Food/" + foodLine};

				// TODO: Add to menu
			}
			else
			{
				std::string label{std::string("Food/") + foodItem.at(1)};
				double price = atof(foodItem.at(1).c_str());

				// TODO: Add to menu
			}

			if(foodFile.eof()) break;

		}

		foodFile.close();
	}

	void fetchDrinks()
	{
		
		if(!fileExists(drinksFileName))
		{
			std::cout << "WARN: No drinks file. No drinks will be available." << std::endl;
		}

		std::ifstream drinksFile;

		drinksFile.open(drinksFileName);
		drinksFile.close();
	}

	int show()
	{
		window->show();
		
		// TODO: Determine whether to make fullscreen by default or not.

//		window->fullscreen();
		return Fl::run();
	}
	
	void addTransaction(double amountOwed, double amountReceived, std::string label)
	{
		Transaction nta{amountOwed, amountReceived, label};
		transactions.push_back(nta);
	}
};

int main(int argc, char **argv)
{

	// Make FLTK look nice.

	Fl::scheme("GTK+");

	POS posApp{};
	
	std::string restoreFileName{"transactions.axtf"};

	// if the transactions file exists, restore the transactions. This allows the
	// program to close and re-open without losing data.

	if(fileExists(restoreFileName))
	{

		const int MAX_RESTORE_MESSAGES = 4;
		int transactionsRestored = 0;
		std::cout << "Reading from \"" << restoreFileName << "\"" << std::endl;

		std::ifstream transactionFile;
		transactionFile.open(restoreFileName, std::ios::in);
		while(true)
		{
			// transaction restore file is open, parse as an axtf file 

			std::string tmpString;
			std::getline(transactionFile, tmpString);
			if(transactionsRestored <= MAX_RESTORE_MESSAGES)
				std::cout << "Restoring transaction: " << tmpString << std::endl;

			std::vector<std::string> transactionInfo{explode(tmpString, ':')};

			if(transactionInfo.size() >= 3)
			{
				double amountOwed = atof(transactionInfo.at(0).c_str());
				double amountGiven = atof(transactionInfo.at(1).c_str());
				std::string label = transactionInfo.at(2);
				transactionsRestored++;
			}
			else
			{
				std::cout << "WARNING: Ignoring invalid transaction restored from \"" << restoreFileName << "\"!" << std::endl;
				std::cout << "transactionInfo.size() returns " << transactionInfo.size() << " but expected 3" << std::endl;
				break;
			}

			if(transactionFile.eof()) break;
		}
		transactionFile.close();

		int trunctuatedMessages = 0;

		if(transactionsRestored > MAX_RESTORE_MESSAGES)
		{
			trunctuatedMessages = transactionsRestored - MAX_RESTORE_MESSAGES;
		}

		std::cout << "Successfully restored " << transactionsRestored << " transactions!" << std::endl << trunctuatedMessages << " transaction restored messages were trunctuated" << std::endl;
	}

	return posApp.show();
}
