#include "Bank.h"
#include "Account.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main() {

	Bank wooriBank;

	wooriBank.init();
	wooriBank.CreateAccount("Paul", 3000);
	wooriBank.CreateAccount("Mc");

	wooriBank.SetDeposit(0, 2000);
	wooriBank.SetDeposit(1, 1000);

	wooriBank.ShowAllAccounts();
	
	return 0;
}