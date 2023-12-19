
#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>



class CurrencyRetriever {
public:
	double retrieve();
};