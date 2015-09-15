#include "Bank.h"

using namespace std;


Bank::Bank()
{
	init();
}


Bank::~Bank()
{

}

void Bank::init() {
	newAccId = 0;
}

void Bank::CreateAccount(char* accountName, int balance ) 
{
	accounts[newAccId].init(accountName, newAccId ,balance);
	accounts[newAccId].showAccount();
	newAccId++;
}

void Bank::ShowAllAccounts() {
	int i;
	Account acc;

	for (i = 0; i < newAccId; i++) {
		acc = accounts[i];
		acc.showAccount();
	}
}

void Bank::SetDeposit(int accNum, int money) {
	accounts[accNum].deposite(money);
}

void Bank::WithdrawMoney(int accNum, int money) {
	accounts[accNum].withdraw(money);
}