#include "currencyretriever.h"


using json = nlohmann::json;

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t total_size = size * nmemb; // Calculate total size of received data(each element * number of elements)
    output->append((char*)contents, total_size); // Appends received data to output string. Append used to add the data to end of existing string
    return total_size; // Return total size of the data received
}



double CurrencyRetriever::retrieve()
{
    std::string currency_input;
    const std::size_t currency_input_size = 3;
    currency_input.reserve(currency_input_size);
    do
    {
        std::cout << "Please provide a currency to convert the rate from EUR. (USD, GBP, CAD, AUD, JPY):\n";

        std::getline(std::cin, currency_input);

        if (currency_input.length() != 3)
        {
            std::cerr << "Please provide a valid currency. For example: EUR, USD, GBP...";
        }

    } while (currency_input.length() > currency_input_size);




    std::string api_key;
    std::string api_endpoint = "http://data.fixer.io/api/latest";
    const std::size_t api_key_size = 50;
    api_key.reserve(api_key_size);

    do
    {
        std::cout << "Please provide your API Key from https://fixer.io :\n";

        std::getline(std::cin, api_key);

        if (api_key.length() > api_key_size)
        {
            std::cerr << "The input is too long. Maximum length is :" << api_key_size << "characters \n";
        }
    } while (api_key.length() > api_key_size);
   

    std::string api_url = api_endpoint + "?access_key=" + api_key;
    

    CURL* curl = curl_easy_init();

    if (curl)
    {
        std::string api_response;
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &api_response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error with API request: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }

        try {
            nlohmann::json response_json = nlohmann::json::parse(api_response);

            bool success = response_json["success"];
            std::string date = response_json["date"];
            std::string base_currency = response_json["base"];
            double rate_user = response_json["rates"][currency_input];

            success ? std::cout << "Date: " + date + "\n" + "Base Currency: " + base_currency + "\n" + "Rate in " + currency_input + ": " + std::to_string(rate_user) + "\n"
                : std::cout << "Success is false!";


        }
        catch (const std::exception e) {
            std::cerr << "Error parsing JSON" << e.what() << "\n";
            return -1;
        }
    }

    return 0;
}