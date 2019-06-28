//============================================================================
// @name        : forecastDownloader.h
// @author      : Thomas Dooms
// @date        : 6/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <fstream>

#include "json/json.h"

struct ForecastDownloader
{
    static void downloadToFile(const std::string& url, const std::string& path)
    {
        CURL* curl = curl_easy_init();
        FILE* fp = fopen(path.c_str(), "wb");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        int result = curl_easy_perform(curl);
        if(result != CURLE_OK) throw std::runtime_error("Could not perform operation, I have no idea what");

        fclose(fp);
        curl_easy_cleanup(curl);
    }

    static void downloadWeatherData(const std::string& path)
    {
        const std::string key  = "c947cb79ca474d2543ab410f5d307507";
        const std::string apicall = "https://api.darksky.net/forecast/" + key + "/51.209690,4.4395194?units=si";

        downloadToFile(apicall, path);
    }

    static nlohmann::json getJsonFromFile(const std::string& path)
    {
        std::ifstream file(path);
        if(not file.is_open()) throw std::runtime_error("could not open file, please check that it is present");
        return nlohmann::json::parse(file);
    }
};
