#include "ATM.h"

#include <iostream>

#include "spdlog/spdlog.h"

using namespace std;

void ATM::run()
{
	while (true)
	{
		try
		{
			string card_num;
			cout << "Insert your card: ";
			cin >> card_num;
			auto valid_status = _server->validate(ReadedCardInfo{ card_num });
			switch (valid_status)
			{
			case ValidStatus::NotCompatibleNetwork:
			case ValidStatus::InvalidCardInfo:
				cout << "You card not supported by ATM" << endl;
				continue;
			}
			bool session_start = false;
			for (int attemp = 2; attemp >= 0; --attemp)
			{
				cout << "Enter pin code: ";
				string pin_code;
				for (int i = 0; i < 4; ++i)
				{
					char c;
					cin >> c;
					pin_code.append(1, c);
				}
				if (_server->authenticate(ReadedCardInfo{ card_num }, pin_code))
				{
					session_start = true;
					break;
				}
				else
				{
					cout << "Invalid PIN code. You have " << attemp << " attempts." << endl;
				}
			}
			if (session_start)
			{
				cout << "Logged success" << endl;
			}
			else
			{
				cout << "You card is blocked" << endl;
				continue;
			}

			bool end_session = false;
			while (!end_session)
			{
				cout << "Options: " << endl;
				cout << "1. Get balance" << endl;
				cout << "2. Withdraw money" << endl;
				cout << "3. Change PIN" << endl;
				cout << "4. End session" << endl;
				cout << "Enter option number: " << endl;
				char opt;
				cin >> opt;
				if (opt == '1')
				{
					uint64_t balance = _server->getBalance();
					uint64_t integer = balance / 100;
					unsigned int fract = balance % 100;
					cout << "Balance: " << integer << '.' << fract << endl;
				}
				else if (opt == '2')
				{
					withdraw();
				}
				else if (opt == '3')
				{
					changePin();
				}
				else if (opt == '4')
				{
					end_session = true;
				}
				else
				{
					cout << "Invalid option. Try again" << endl;
				}
			}
		}
		catch (const exception& e)
		{
			spdlog::error(e.what());
			cout << "Error occured" << endl;
		}
		_server->finishSession();
	}
}

void ATM::changePin()
{
	cout << "Enter new PIN: ";
	string pin;
	for (int i = 0; i < 4; ++i)
	{
		char c;
		cin >> c;
		pin.append(1, c);
	}
	cout << "Enter new PIN again: ";
	string copy_pin;
	for (int i = 0; i < 4; ++i)
	{
		char c;
		cin >> c;
		copy_pin.append(1, c);
	}
	if (pin == copy_pin)
	{
		if (_server->changePinCode(pin))
		{
			cout << "Changed successfully" << endl;
		}
		else
		{
			cout << "Error occurred" << endl;
		}
	}
	else
	{
		cout << "PIN not match" << endl;
		return;
	}
}

void ATM::withdraw()
{
	cout << "Enter amount: " << endl;
	string s_amount;
	cin >> s_amount;
	if (stol(s_amount) <= 0)
	{
		cout << "Invalid amount" << endl;
		return;
	}
	::uint64_t amount = stoul(s_amount) * 100;
	spdlog::info("withdraw");
	spdlog::info(amount);
	if (!_server->canWithdraw(amount))
	{
		cout << "Not enough money" << endl;
		return;
	}
	cout << "Amount: " << amount / 100 << endl;
	cout << "Fee: " << _server->getWithdrawalFee(amount) / 100 << endl;
	cout << "Are you sure to withdraw? y/n" << endl;
	char c;
	cin >> c;
	if (c != 'y')
	{
		cout << "Canceled" << endl;
		return;
	}

	if (_server->withdraw(amount))
	{
		cout << "Withdraw successfully" << endl;
	}
	else
	{
		cout << "Withdraw failed" << endl;
	}
}
