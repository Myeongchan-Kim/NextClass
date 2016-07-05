#pragma once
#include "Account.h"

using namespace std;

namespace BANK_CONST 
{
	enum {
		MAX_ACCOUNTS = 255
	};
}

class Bank
{

private:
	Account accounts[BANK_CONST::MAX_ACCOUNTS];
	int newAccId; //새로 생성될 계좌의 번호

public:
	Bank();
	~Bank();

	void init();
	void CreateAccount(char* accountName, int balance =0);
	void SetDeposit(int accNum, int money);
	void WithdrawMoney(int accNum, int money);
	void ShowAllAccounts();
};

