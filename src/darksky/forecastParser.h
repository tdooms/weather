//============================================================================
// @name        : forecastParser.h
// @author      : Thomas Dooms
// @date        : 6/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "forecastData.h"
#include "json/json.h"



struct ForecastParser
{

    template<typename T>
    void static optional(const nlohmann::json& json, const char* key, std::optional<T>& param)
    {
        if(json.count(key) != 0) param = json.at(key);
    }

    static PrecipitationData parsePrecipitationData(const nlohmann::json& json)
    {
        PrecipitationData result = {};
        optional(json, "nearestStormDistance", result.nearestStormDistance);
        result.precipIntensity      = json["precipIntensity"];
        optional(json, "precipIntensityError", result.precipIntensityError);
        result.precipProbability    = json["precipProbability"];
        optional(json, "precipType", result.precipType);
        return result;
    }
    static DescriptionData parseDescriptionData(const nlohmann::json& json)
    {
        DescriptionData result;
        result.summary     = json["summary"];
        result.icon        = json["icon"];
        return result;
    }
    static WeatherData parseWeatherData(const nlohmann::json& json)
    {
        WeatherData result = {};
        result.summary     = json["summary"];
        result.icon        = json["icon"];
        result.dewPoint    = json["dewPoint"];
        result.humidity    = json["humidity"];
        result.pressure    = json["pressure"];
        result.windSpeed   = json["windSpeed"];
        result.windGust    = json["windGust"];
        result.windBearing = json["windBearing"];
        result.cloudCover  = json["cloudCover"];
        result.uvIndex     = json["uvIndex"];
        result.visibility  = json["visibility"];
        result.ozone       = json["ozone"];
        return result;
    }
    static TemperatureData parseTemperatureData(const nlohmann::json& json)
    {
        TemperatureData result = {};
        result.temperature         = json["temperature"];
        result.apparentTemperature = json["apparentTemperature"];
        return result;
    }
    static DayData parseDayData(const nlohmann::json& json)
    {
        DayData result = {};
        result.sunriseTime                = json["sunriseTime"];
        result.sunsetTime                 = json["sunsetTime"];
        result.moonPhase                  = json["moonPhase"];
        result.precipIntensityMax         = json["precipIntensityMax"];
        result.precipIntensityMaxTime     = json["precipIntensityMaxTime"];
        result.windGustTime               = json["windGustTime"];
        result.uvIndexTime                = json["uvIndexTime"];
        result.temperatureMin             = json["temperatureMin"];
        result.temperatureMinTime         = json["temperatureMinTime"];
        result.temperatureMax             = json["temperatureMax"];
        result.temperatureMaxTime         = json["temperatureMaxTime"];
        result.apparentTemperatureMin     = json["apparentTemperatureMin"];
        result.apparentTemperatureMinTime = json["apparentTemperatureMinTime"];
        result.apparentTemperatureMax     = json["apparentTemperatureMax"];
        result.apparentTemperatureMaxTime = json["apparentTemperatureMaxTime"];
        return result;
    }

    static CurrentlyData parseCurrentlyData(const nlohmann::json& json)
    {
        CurrentlyData result;
        std::get<0>(result) = json["time"];
        std::get<1>(result) = parsePrecipitationData(json);
        std::get<2>(result) = parseTemperatureData(json);
        std::get<3>(result) = parseWeatherData(json);
        return result;
    }
    static MinutelyData parseMinutelyData(const nlohmann::json &json)
    {
        MinutelyData result = {};
        std::get<0>(result) = json["time"];
        std::get<1>(result) = parsePrecipitationData(json);
        return result;
    }
    static HourlyData parseHourlyData(const nlohmann::json& json)
    {
        HourlyData result = {};
        std::get<0>(result) = json["time"];
        std::get<1>(result) = parsePrecipitationData(json);
        std::get<2>(result) = parseTemperatureData(json);
        std::get<3>(result) = parseWeatherData(json);
        return result;
    }
    static DailyData parseDailyData(const nlohmann::json& json)
    {
        DailyData result = {};
        std::get<0>(result) = json["time"];
        std::get<1>(result) = parsePrecipitationData(json);
        std::get<2>(result) = parseWeatherData(json);
        std::get<3>(result) = parseDayData(json);
        return result;
    }

    static MinutelyForecast parseMinutelyForecast(const nlohmann::json& json)
    {
        MinutelyForecast result;
        std::get<0>(result) = parseDescriptionData(json);
        auto& forecast = std::get<1>(result);
        forecast.reserve(json["data"].size());
        for(const auto& elem : json["data"]) forecast.push_back(parseMinutelyData(elem));
        return result;
    }
    static HourlyForecast parseHourlyForecast(const nlohmann::json& json)
    {
        HourlyForecast result;
        std::get<0>(result) = parseDescriptionData(json);
        auto& forecast = std::get<1>(result);
        forecast.reserve(json["data"].size());
        for(const auto& elem : json["data"]) forecast.push_back(parseHourlyData(elem));
        return result;
    }
    static DailyForecast parseDailyForecast(const nlohmann::json& json)
    {
        DailyForecast result;
        std::get<0>(result) = parseDescriptionData(json);
        auto& forecast = std::get<1>(result);
        forecast.reserve(json["data"].size());
        for(const auto& elem : json["data"]) forecast.push_back(parseDailyData(elem));
        return result;
    }

    static CompleteForecast parseCompleteForecast(const nlohmann::json& json)
    {
        CompleteForecast result;
        std::get<0>(result) = parseCurrentlyData(json["currently"]);
        if(json.count("minutely") != 0) std::get<1>(result) = parseMinutelyForecast(json["minutely"]);
        if(json.count("hourly"  ) != 0) std::get<2>(result) = parseHourlyForecast(json["hourly"]);
        if(json.count("daily"   ) != 0) std::get<3>(result) = parseDailyForecast(json["daily"]);
        return result;
    }
};
