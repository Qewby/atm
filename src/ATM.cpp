#include "ATM.h"

#include <iostream>

#include "CardNetwork.h"

using namespace std;

void ATM::run()
{
	while (true)
	{
		string card_num;
		cout << "Insert your card: ";
		cin >> card_num;
		CardNetwork net(card_num);
		if (!net.compatible())
		{
			cout << "Card not supported by ATM" << endl;
			continue;
		}
		auto validator = net.getValidator();
		if (!validator->validate(card_num))
		{
			cout << "Invalid card, please contact your bank" << endl;
			continue;
		}
		cout << "Enter pin code: ";
		string pin_code;
		for (int i = 0; i < 4; ++i)
		{
			char c;
			cin >> c;
			pin_code.append(1, c);
		}
		cout << pin_code << endl;
	}
}
