#include "String.h"

#include <algorithm>

using namespace std;

bool allDigits(const string& str)
{
	auto isDigit = [](char c) -> bool
	{
		return isdigit(c);
	};
	return std::all_of(str.begin(), str.end(), isDigit);
}
