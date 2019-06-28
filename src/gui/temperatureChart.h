//============================================================================
// @name        : chartCreator.h
// @author      : Thomas Dooms
// @date        : 6/26/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <memory>
#include <iostream>
#include <QWidget>
#include <QGridLayout>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

#include "../darksky/forecastData.h"

class TemperatureChart : public QWidget
{
    Q_OBJECT
public:
    TemperatureChart(const HourlyForecast& forecast, QWidget* parent = nullptr) : QWidget(parent)
    {
        layout = std::make_unique<QGridLayout>();

        const auto getParam = [](const HourlyData& data){ return std::get<2>(data).temperature; };
        series = std::make_unique<QtCharts::QLineSeries>();

        for(const auto& hourlyData : std::get<1>(forecast))
        {
            std::cout << std::get<0>(hourlyData) << ' ' << getParam(hourlyData) << '\n';
            series->append(std::get<0>(hourlyData), getParam(hourlyData));
        }

        chart = std::make_unique<QtCharts::QChart>();
        chart->addSeries(series.get());
        chart->legend()->hide();
        chart->setTitle("temperature");

        auto axisX = std::make_unique<QtCharts::QDateTimeAxis>();
        axisX->setTickCount(24);
        axisX->setFormat("H");
        axisX->setTitleText("Hour");
        chart->addAxis(axisX.get(), Qt::AlignBottom);
        series->attachAxis(axisX.get());

        auto axisY = std::make_unique<QtCharts::QValueAxis>();
        axisY->setLabelFormat("%d");
        axisY->setTitleText("temperature");
        chart->addAxis(axisY.get(), Qt::AlignLeft);
        series->attachAxis(axisY.get());

        tempChart = std::make_unique<QtCharts::QChartView>();
        tempChart->setRenderHint(QPainter::Antialiasing);

        setLayout(layout.get());
        layout->addWidget(tempChart.get(), 0, 0, 1, 1);
        layout->addWidget(new QLabel{"hey"}, 0, 1, 1, 1);
    }

private:
    std::unique_ptr<QGridLayout> layout;
    std::unique_ptr<QtCharts::QChart> chart;
    std::unique_ptr<QtCharts::QChartView> tempChart;
    std::unique_ptr<QtCharts::QLineSeries> series;
};
