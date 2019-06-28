//============================================================================
// @name        : Window.cpp
// @author      : Thomas Dooms
// @date        : 6/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "Window.h"
#include "../darksky/forecastDownloader.h"
#include "../darksky/forecastParser.h"


Window::Window(QWidget* parent) noexcept : QMainWindow(parent)
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    ForecastDownloader::downloadWeatherData("weather.json");
    const auto& json = ForecastDownloader::getJsonFromFile("weather.json");
    const auto& [currentData, minutelyForecast, hourlyForecast, dailyForecast] = ForecastParser::parseCompleteForecast(json);

    root             = std::make_unique<QWidget>(this);
    layout           = std::make_unique<QGridLayout>();
    weatherWidget    = std::make_unique<CurrentlyDataWidget>(currentData, this);
    temperatureChart = std::make_unique<TemperatureChart>(hourlyForecast.value(), this);

    show();
    setCentralWidget(root.get());
    setWindowTitle("weather");
    root->setLayout(layout.get());

    layout->addWidget(weatherWidget.get(), 0, 0, 1, 1);
    layout->addWidget(temperatureChart.get(), 1, 0, 1, 1);
}