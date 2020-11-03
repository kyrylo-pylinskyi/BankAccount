#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
/// <summary>
/// class represents simple Bank Account 
/// </summary>
class BankAccount
{
protected:
	// the name of user
	string userName;
	// the name of account
	string accountName;
	// the account number
	int accountNumber;
	// the balance of account
	float balance;
public:

	// default constructor
	BankAccount() : userName(""), accountName(""), accountNumber(0), balance(0)
	{}

	// main constructor
	BankAccount(string userName, string accountName, int accountNumber, float balance = 0) {
		this->userName = userName;
		this->accountName = accountName;
		this->accountNumber = accountNumber;
		this->balance = balance;
	}

	/// <summary>
	/// This method initializes all program parameters
	/// </summary>
	void init()
	{
		cout << "Enter your username -> ";
		cin >> userName;

		cout << "Enter account name -> ";
		cin >> accountName;

		cout << "Enter Unique Account Number -> ";
		cin >> accountNumber;
	};
	// user name seter
	void setUserName(string userName) { this->userName = userName; }
	// user name geter
	string getUserName() { return userName; }

	// acount name seter
	void setAccountName(string accountName) { this->userName = accountName; }
	// acount name geter
	string getAccountName() { return accountName; }

	// acount number seter
	void setAccountNumber(int accountNumber) { this->userName = accountNumber; }
	// acount number geter
	int getAccountNumber() { return accountNumber; }

	// balance seter
	void setBalance(float balance) { this->balance = balance; }
	// balance geter
	float getBalance() { return balance; }

	/// <summary>
	/// Method to Add some money to account balance
	/// </summary>
	/// <param name="amount"> the amount to add to the account </param>
	void Deposit(float amount)
	{
		// check if the amount greater then zero
		while (amount <= 0) {
			cout << "The amount cannot be less than zero. Minimum value 0.1" << endl;
			cout << "Please change the amount." << endl;
			cout << "Amount -> ";
			cin >> amount;
		}
		// add money to balance
		balance += amount;
		// inform
		cout << "Your balance has been updated: " << getBalance() << endl;
	};

	/// <summary>
	/// Method to withdraw money from balance
	/// </summary>
	/// <param name="amount"> the amount to withdraw from the account </param>
	void Withdraw(float amount)
	{
		// check if the amount less then balance
		while (amount > balance)
		{
			cout << "The amount cannot be more than account balance. Your balance: " << getBalance() << endl;
			cout << "Please change the amount." << endl;
			cout << "Amount -> ";
			cin >> amount;
		}
		// reduce balance
		balance -= amount;
		// inform
		cout << "Your balance has been updated: " << getBalance() << endl;
	};
	/// <summary>
	/// Method shows all user's information
	/// </summary>
	void getInfo()
	{
		cout << "Username: " << getUserName() << endl;
		cout << "Account name: " << getAccountName() << endl;
		cout << "Unique Account Number: " << getAccountNumber() << endl;
		cout << "Personal funds: " << getBalance() << endl;
	};

	/// <summary>
	/// Method display's menu of the bank in the consol
	/// </summary>
	void menu()
	{
		cout << "----------------------------" << endl;
		cout << "1. Deposit" << endl;
		cout << "2. Withdraw" << endl;
		cout << "3. Get more information" << endl;
	}

};

/// <summary>
/// Bank account with credit posibilityes
/// </summary>
class BankAccountVIP :protected BankAccount
{
protected:
	// account credit
	float credit;
	// account credit limit
	float creditLimit;
public:
	// default constructor
	BankAccountVIP() : credit(0), creditLimit(0)
	{}

	// main constructor
	BankAccountVIP(string userName, string accountName, int accountNumber, float balance, float credit = 0, float creditLimit = 0) :BankAccount(userName, accountName, accountNumber, balance)
	{
		this->credit = credit;
		this->creditLimit = creditLimit;
	}

	/// <summary>
	/// This method initializes all program parameters
	/// </summary>
	void init()
	{
		BankAccount::init();

		cout << "Enter the maximum credit limit -> ";
		cin >> creditLimit;
	}

	// credit set method
	void setCredit(float credit) { this->credit = credit; }
	// credit get method
	float getCredit() { return credit; }

	// credit limit set method
	void setCreditLimit(float creditLimit)
	{ 
		if (credit < creditLimit) this->creditLimit = creditLimit;
		else cout << "creditLimit can't be more than curent credit" << endl;
	}
	// credit limit get method
	float getCreditLimit() { return creditLimit; }

	/// <summary>
	/// Method to Add some money to account balance
	/// </summary>
	/// <param name="amount"> the amount to add to the account </param>
	void Deposit(float amount)
	{
		// check if amount positive
		while (amount <= 0)
		{
			cout << "The amount cannot be less than zero. Minimum value 0.1" << endl;
			cout << "Please change the amount." << endl;
			cout << "Amount -> ";
			cin >> amount;
		}

		// reduce money from credit
		credit -= amount;
		if (credit < 0)
		{
			// set money to balance
			balance += -1 * credit;
			// set credit to zero 
			credit = 0;
		}
		// inform
		cout << "Your balance has been updated: " << getBalance() << endl;
		cout << "Your credit has been updated: " << getCredit() << endl;
	}
	
	/// <summary>
	/// Method to withdraw money from balance
	/// </summary>
	/// <param name="amount"> the amount to withdraw from the account </param>
	void Withdraw(float amount)
	{
		// correct balance
		if (credit > 0 && balance > 0) {
			credit -= balance;
			if (credit < 0) {
				balance = credit * (-1);
				credit = 0;
			}
			// inform
			cout << "Your balance has been updated: " << getBalance() << endl;
			cout << "Your credit has been updated: " << getCredit() << endl;
		}
		
		// check does the amount to withdraw correct
		while (credit - balance + amount > creditLimit)
		{
			cout << "The amount cannot be more than credit limit.\nYour balance: " << getBalance() << "\nYour Credit: " << getCredit() << "\nYour Credit Limit: " << getCreditLimit() << endl;
			cout << "Please change the amount." << endl;
			cout << "Amount -> ";
			cin >> amount;
		}

		// add money to user credit field
		if(credit > 0) {
			credit += amount;
		}

		// reduse money from acount balance
		if (balance > 0) {
			balance -= amount;
			if (balance < 0) {
				credit = balance * (-1);
				balance = 0;
			}
		}

		// inform
		cout << "Your balance has been updated: " << getBalance() << endl;
		cout << "Your credit has been updated: " << getCredit() << endl;
	};

	// VIP account menu
	void menu()
	{
		BankAccount::menu();
		cout << "4. Change the credit limit" << endl;
		cout << "5. Exit" << endl;
		cout << "----------------------------" << endl;

	};

	/// <summary>
	/// Shows information about user
	/// </summary>
	void getInfo()
	{
		BankAccount::getInfo();
		cout << "Current credit: " << getCredit() << endl;
		cout << "Maximum credit limit: " << getCreditLimit() << endl;
	};

};

//MAIN
int main()
{
	bool loop;
	int variant;
	float amount;
	BankAccount user;
	BankAccountVIP userVIP;

	cout << "Welcome to the BankAccount24 application!" << endl;
	cout << "Please select the type of your account:" << endl;
	cout << "1. Basic Account" << endl << "2. Premium Account" << endl;
	cout << "Selection -> ";
	cin >> variant;

	// program interface loop 
	while (true) {
		switch (variant) {
			// default account
		case 1:
			
			user.init();
			loop = true;
			while (loop) {
				int variant;

				user.menu();
				cout << "4. Exit" << endl;
				cout << "Select an operation -> ";
				cin >> variant;

				switch (variant) {
				case 1:
					cout << "Select Amount -> ";
					cin >> amount;
					user.Deposit(amount);
					break;
				case 2:
					cout << "Select Amount -> ";
					cin >> amount;
					user.Withdraw(amount);
					break;
				case 3:
					user.getInfo();
					break;
				case 4:
					loop = false;
					break;
				}
			}

			break;
			// VIP acount
		case 2:
			userVIP.init();
			loop = true;
			while (loop) {
				int variant;

				userVIP.menu();
				cout << "Select an operation -> ";
				cin >> variant;

				switch (variant) {
				case 1:
					cout << "Select Amount -> ";
					cin >> amount;
					userVIP.Deposit(amount);
					break;
				case 2:
					cout << "Select Amount -> ";
					cin >> amount;
					userVIP.Withdraw(amount);
					break;
				case 3:
					userVIP.getInfo();
					break;
				case 4:
					cout << "Select Amount -> ";
					cin >> amount;
					userVIP.setCreditLimit(amount);
					break;
				case 5:
					loop = false;
					break;
				}			
			}
			break;
		}
		cout << "Thank you. Have a nice day!" << endl;
		cout << "If you want to continue, then select the type of your account" << endl;
		cout << "1. Basic Account" << endl << "2. Premium Account" << endl;
		cout << "Selection -> ";
		cin >> variant;
	}

	return 0;
}