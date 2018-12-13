#include "transaction.h"
#include <iostream>
#include <string>

Transaction::Transaction(double amountOwed, double amountReceived, std::string label)
{
	this->amountOwed = amountOwed;
	this->amountReceived = amountReceived;
	this->label = label;
}

double Transaction::getAmountOwed()
{
	return this->amountOwed;
}

double Transaction::getAmountReceived()
{
	return this->amountReceived;
}

std::string Transaction::getLabel()
{
	return this->label;
}
