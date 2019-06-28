//============================================================================
// @name        : minuteData.h
// @author      : Thomas Dooms
// @date        : 6/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#pragma once

#include <string>
#include <vector>
struct DescriptionData
{
    std::string summary;
    std::string icon;
};
struct PrecipitationData
{
    std::optional<double> nearestStormDistance;
    double precipIntensity;
    std::optional<double> precipIntensityError;
    double precipProbability;
    std::optional<std::string> precipType;
};
struct TemperatureData
{
    double temperature;
    double apparentTemperature;
};
struct WeatherData
{
    std::string summary;
    std::string icon;
    double dewPoint;
    double humidity;
    double pressure;
    double windSpeed;
    double windGust;
    double windBearing;
    double cloudCover;
    double uvIndex;
    double visibility;
    double ozone;
};

struct DayData
{
    uint64_t sunriseTime;
    uint64_t sunsetTime;
    double moonPhase;

    double precipIntensityMax;
    double precipIntensityMaxTime;
    uint64_t windGustTime;
    uint64_t uvIndexTime;

    double temperatureMin;
    uint64_t temperatureMinTime;
    double temperatureMax;
    uint64_t temperatureMaxTime;

    double apparentTemperatureMin;
    uint64_t apparentTemperatureMinTime;
    double apparentTemperatureMax;
    uint64_t apparentTemperatureMaxTime;
};

// uint64_t is for time;
using CurrentlyData = std::tuple<uint64_t, PrecipitationData, TemperatureData, WeatherData>;
using MinutelyData  = std::tuple<uint64_t, PrecipitationData>;
using HourlyData    = std::tuple<uint64_t, PrecipitationData, TemperatureData, WeatherData>;
using DailyData     = std::tuple<uint64_t, PrecipitationData, WeatherData, DayData>;

// summary, icon, data
using MinutelyForecast = std::tuple<DescriptionData, std::vector<MinutelyData>>;
using HourlyForecast   = std::tuple<DescriptionData, std::vector<HourlyData>>;
using DailyForecast    = std::tuple<DescriptionData, std::vector<DailyData>>;

using CompleteForecast = std::tuple<CurrentlyData, std::optional<MinutelyForecast> , std::optional<HourlyForecast> , std::optional<DailyForecast>>;
