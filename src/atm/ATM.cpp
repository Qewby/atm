#include "ATM.h"

#include <iostream>

using namespace std;

void ATM::run()
{
	while (true)
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
			}
			else if (opt == '3')
			{}
			else if (opt == '3')
			{}
			else if (opt == '4')
			{
				end_session = true;
			}
			else
			{
				cout << "Invalid option. Try again" << endl;
			}
		}
		_server->finishSession();
	}
}
