#include "mainTest.h"

using namespace std;

void HappyBirthday(int i) {
	cout << "Happy birthday!" << i << endl;
}

int main()
{
	Strategy* stra = new FCFS();
	TestModule* t = new TestModule(stra);
	t->Run();

	cout << " ********************************* " << endl;
	cout << "  Happy BirthDay Professor Park!!" << endl;
	cout << " ********************************* " << endl;
	return 0;
}