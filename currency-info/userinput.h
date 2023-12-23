#pragma once

#include <iostream>
#include <string>

class UserInput {
public:
	std::string user_currency;
	int user_amount;
	std::string user_API_key;

	void retrieve();
};