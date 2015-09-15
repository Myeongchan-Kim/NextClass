#include "Account.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;


Account::Account()
{
}


Account::~Account()
{
}

void Account::init(char * givenAccountName, int givenAccountNumber, int givenBalance) {
	strcpy_s(accountName, givenAccountName);
	accountNum = givenAccountNumber;
	balance = givenBalance;
}

void Account::showAccount() {
	cout << "Account number: " << accountNum << ", AccountName: " << accountName << ", balance: "<< balance << endl;
}

void Account::deposite(int money) {
	balance += money;
}

int Account::withdraw(int money) {
	balance -= money;
	return money;
}