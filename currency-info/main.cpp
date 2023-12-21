// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "currencyretriever.h"
#include "userinput.h"

int main()
{
     std::cout << "Welcome to my Currency Retriever Program!\n";

    CurrencyRetriever currencyretriever;
    UserInput userInput;

    userInput.retrieve();

    double result = currencyretriever.retrieve(userInput);

    if(result !=0)
    {
        std::cerr << "Error in retrieving currency data. Exiting...\n";
        return 1;
    }

    std::cout << "Currency data retrieved successfully!\n";

    std::cout << "Press a key to close this window.";
    std::cin.get();

    return 0;
}
