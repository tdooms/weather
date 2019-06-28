//============================================================================
// @name        : smallWidget.h
// @author      : Thomas Dooms
// @date        : 6/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

#include <memory>
#include "currentlyDataWidget.h"
#include "../darksky/forecastDownloader.h"
#include "../darksky/forecastParser.h"


class CurrentlyDataWindow : public QMainWindow
{
    Q_OBJECT;
public:
    explicit CurrentlyDataWindow(QWidget* parent = nullptr) noexcept
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);

        ForecastDownloader::downloadWeatherData("weather.json");
        const auto& json = ForecastDownloader::getJsonFromFile("weather.json");
        const auto& [currentData, minutelyForecast, hourlyForecast, dailyForecast] = ForecastParser::parseCompleteForecast(json);

        root = std::make_unique<CurrentlyDataWidget>(currentData, this);

        show();
        setCentralWidget(root.get());
    }

private:
    std::unique_ptr<CurrentlyDataWidget> root;
};