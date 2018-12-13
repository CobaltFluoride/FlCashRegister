#include <string>

class Transaction
{
private:
	double amountOwed;
	double amountReceived;
	std::string label;
public:
	Transaction(double amountOwed, double amountReceived, std::string label);

	double getAmountOwed();
	double getAmountReceived();
	std::string getLabel();
};
