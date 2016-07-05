#include "mainTest.h"

using namespace std;

void HappyBirthday(int i) {
	cout << "Happy birthday!" << i << endl;
}

int main()
{
	Strategy* stra = nullptr;
	int userInput = 0;

	while (stra == nullptr){
		cout << "Patient from File : " << endl;
		cout << "Select stragtegy number.\n 1.FCFS  2.ParkFirst with FCFS \n >";
		cin >> userInput;
		if (userInput == 1)
			stra = new FCFS();
		else if (userInput == 2)
			stra = new ParkFirstFCFS();
	}

	TestModule* t = new TestModule(stra);
	t->Run();

	cout << " ********************************* " << endl;
	cout << "  Happy BirthDay Professor Park!!" << endl;
	cout << " ********************************* " << endl;
	return 0;
}