#pragma once
#include <iostream>
#include <cstring>

using namespace std;

namespace ACCOUNT_CONST{
	enum {
		MAX_NAME_LEN = 255
	};
}

class Account
{
private:
	char accountName[ACCOUNT_CONST::MAX_NAME_LEN];
	int accountNum;
	int balance;
	
public:
	Account();
	~Account();

	void init(char* accountName, int accountNumber, int balance);
	void deposite(int money);
	int withdraw(int money);
	void showAccount();
};

