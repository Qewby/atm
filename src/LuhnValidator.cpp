#include "LuhnValidator.h"

#include "spdlog/spdlog.h"

using namespace std;

bool LuhnValidator::_validate(const string& number)
{
	int n_digits = number.length();

	int n_sum = 0;
	bool is_second = false;
	for (int i = n_digits - 1; i >= 0; i--)
	{

		int d = number[i] - '0';

		if (is_second == true)
			d = d * 2;

		// We add two digits to handle
		// cases that make two digits after
		// doubling
		n_sum += d / 10;
		n_sum += d % 10;

		is_second = !is_second;
	}
	bool result = n_sum % 10 == 0;
	spdlog::info(number + " luhn algo result = " + to_string(result));
	return result;
}
