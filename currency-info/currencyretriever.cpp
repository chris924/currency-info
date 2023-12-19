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

    std::string api_key = "YOUR_API_KEY";
    std::string api_endpoint = "http://data.fixer.io/api/latest";

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
            double rate_USD = response_json["rates"]["USD"];

            success ? std::cout << "Date: " + date + "\n" + "Base Currency: " + base_currency + "\n" + "Rate in USD: " + std::to_string(rate_USD) + "\n"
                : std::cout << "Success is false!";


        }
        catch (const std::exception e) {
            std::cerr << "Error parsing JSON" << e.what() << "\n";
            return -1;
        }
    }

    return 0;
}