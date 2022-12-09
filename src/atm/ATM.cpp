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
		}

		_server->finishSession();
	}
}
