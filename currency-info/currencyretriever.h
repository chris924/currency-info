
#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "userinput.h"



class CurrencyRetriever {
public:
	double retrieve(const UserInput& userInput);
};