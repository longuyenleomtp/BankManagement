#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class BankAccount {
private:
	string name;
	long long accountNumber;
	long long balance;
	int code;
public:
	BankAccount() {};
	BankAccount(string name, long long accountNumber, long long balance, int code) {
		this->name = name;
		this->accountNumber = accountNumber;
		this->balance = balance;
		this->code = code;
	}
	string getName() {
		return name;
	}
	long long getAccountNumber() {
		return accountNumber;
	}
	long long getBalance() {
		return balance;
	}
	int getcode() {
		return code;
	}
	void setName(string name) {
		this->name = name;
	}
	void setAccountNumber(long long accountNumber) {
		this->accountNumber = accountNumber;
	}
	void setBalance(long long balance) {
		this->balance = balance;
	}
	void setCode(int code) {
		this->code = code;
	}
	void showAccount() {
		cout << "Account Name: " << name << endl;
		cout << "Account Number: " << accountNumber << endl;
		cout << "Account Balance: " << balance << endl;
		cout << endl;
	}
	void deposit(long long amount) {
		balance += amount;
	}
	void withdraw(long long amount) {
		if (balance >= amount) {
			balance -= amount;
			cout << endl;
			cout << "Withdrawed Successfully!" << endl;
		}
		else {
			cout << "Your balance not enough to withdraw, try again...!" << endl;
		}
	}
};

class BankManagement {
private:
	vector<BankAccount> accounts;
public:
	void addAccount(string name, long long accountNumber, long long balance, int code) {
		accounts.push_back(BankAccount(name, accountNumber, balance, code));
	}
	void showAllAccounts() {
		cout << "All Accounts in System: " << endl;
		for (int i = 0; i < accounts.size(); i++) {
			cout << "Account " << i + 1 << ": " << endl;
			cout << "Account Name: " << accounts[i].getName() << endl;
			cout << "Account Number: " << accounts[i].getAccountNumber() << endl;
			cout << "Account Balance: " << accounts[i].getBalance() << endl;
			cout << endl;
		}
	}
	void searchAccount(long long accountNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getAccountNumber() == accountNumber) {
				cout << endl;
				cout << "Account number " << accountNumber << " had found in the system! " << endl;
				accounts[i].showAccount();
			}
		}
	}
	BankAccount* findAccountToDepositOrWithdraw(long long accountNumber) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].getAccountNumber() == accountNumber) {
				return &accounts[i];
			}
		}
	}
};

int main() {

	BankManagement bank;


	int choice;
	char option;


	do
	{
		cout << "-----------------------BANK MANAGEMENT SYSTEM----------------------------" << endl;
		cout << "--------------------------MENU TO CHOICE---------------------------------" << endl;
		cout << "=====1. Create new Account ============" << endl;
		cout << "=====2. Show All Accounts ============" << endl;
		cout << "=====3. Search Account ============" << endl;
		cout << "=====4. Deposit Money ============" << endl;
		cout << "=====5. Withdraw Money ============" << endl;
		cout << "=====6. Transfer Money ============" << endl;
		cout << "=====7. Exit ============" << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
			case 1: {
				string name;
				long long accountNumber;
				long long balance;
				int code;

				//add information
				cin.ignore();
				cout << "Enter Name: ";
				getline(cin, name);
				cout << "Enter Account Number: ";
				cin >> accountNumber;
				cout << "Enter Initial Balance: ";
				cin >> balance;
				cout << "Enter Your code: ";
				cin >> code;

				//put account into vector accounts
				bank.addAccount(name, accountNumber, balance, code);

				cout << "Add Account Successfully!" << endl;
				break;
			}
				
			case 2: {
				bank.showAllAccounts();
				break;
			}
			
			case 3: {
				long long accountNumber;
				cout << "Enter Account Number you want to search..." << endl;
				cin >> accountNumber;
				bank.searchAccount(accountNumber);
				break;
			}

			case 4: {
				long long accountNumber;
				long long amount;
				int code;
				cout << "Enter Account Number you want to deposit: " << endl;
				cin >> accountNumber;
				BankAccount* account = bank.findAccountToDepositOrWithdraw(accountNumber);
				if (account != NULL) {
					cout << "Enter amount money want to deposit: " << endl;
					cin >> amount;
					cout << "Enter your account's code: " << endl;
					cin >> code;
					if (account->getcode() == code) {
						account->deposit(amount);
						cout << "Deposited money successfully! " << endl;
					}
					else {
						cout << "Your code is incorrect!" << endl;
					}
					
				}
				else {
					cout << "Account number not found in the system, Try again!" << endl;
				}
				break;
			}

			case 5: {
				long long accountNumber;
				long long amount;
				int code;
				cout << "Enter Account Number you want to withdraw: " << endl;
				cin >> accountNumber;
				BankAccount* account = bank.findAccountToDepositOrWithdraw(accountNumber);
				if (account != NULL) {
					cout << "Enter amount money want to withdraw: " << endl;
					cin >> amount;
					cout << "Enter your account's code: " << endl;
					cin >> code;
					if (account->getcode() == code) {
						account->withdraw(amount);
						cout << "Withdrawed money successfully! " << endl;
					}
					else {
						cout << "Your code is incorrect!" << endl;
					}

				}
				else {
					cout << "Account number not found in the system, Try again!" << endl;
				}
				break;
			}

			case 6: {
				long long accountFromNumber, accountToNumber;
				long long amount;
				int code;
				cout << "Enter Account Number you want to send money : " << endl;
				cin >> accountFromNumber;
				BankAccount* accountFrom = bank.findAccountToDepositOrWithdraw(accountFromNumber);

				cout << "Enter Account Number you want to receive money : " << endl;
				cin >> accountToNumber;
				BankAccount* accountTo = bank.findAccountToDepositOrWithdraw(accountToNumber);

				cout << "Enter  Send Account's code: " << endl;
				cin >> code;

				if (accountFrom != NULL) {
					if (accountTo != NULL) {
						if (accountFrom->getcode() == code) {
							cout << "Enter amount money you want to transfer: " << endl;
							cin >> amount;
							accountFrom->withdraw(amount);
							accountTo->deposit(amount);
						}
						else {
							cout << "Your code is incorrect!" << endl;
						}
					}
					else {
						cout << "Account Receive money not found in the system!" << endl;
					}
				}
				else {
					cout << "Account Send money not found in the system!" << endl;
				}

			}
				
		}

		cout << "Do you want continue or exit from system? [Yes/No]" << endl;
		cin >> option;
	} while (option == 'y' || option == 'Y');

	return 0;
}