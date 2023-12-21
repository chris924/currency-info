#include "userinput.h"


void UserInput::retrieve()
{

    const std::size_t currency_input_size = 3;
    user_currency.reserve(currency_input_size);
    std::cout << "Please provide a currency to convert the rate from EUR. (USD, GBP, CAD, AUD, JPY):\n";
    do
    {

        std::getline(std::cin, user_currency);

        if (user_currency.length() != 3)
        {
            std::cerr << "Please provide a valid currency. For example: EUR, USD, GBP...";
        }

    } while (user_currency.length() != currency_input_size);



   
    
    const std::size_t api_key_size = 50;
    user_API_key.reserve(api_key_size);
    std::cout << "Please provide your API Key from https://fixer.io :\n";
    do
    {


        std::getline(std::cin, user_API_key);

        if (user_API_key.length() > api_key_size)
        {
            std::cerr << "The input is too long. Maximum length is :" << api_key_size << "characters \n";
            std::cout << "Provide a valid API key.\n";
        }
    } while (user_API_key.length() > api_key_size);

}