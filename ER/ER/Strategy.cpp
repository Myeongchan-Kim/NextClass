#include "Strategy.h"
#include "Physician.h"

Strategy::Strategy()
{
}


Strategy::~Strategy()
{
}

void Strategy::showStartSelectingLog(Physician* doc)
{
	cout << doc << "'s patient..." << endl;
}