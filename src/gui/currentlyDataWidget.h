//============================================================================
// @name        : weatherWidget.h
// @author      : Thomas Dooms
// @date        : 6/24/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================


#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

#include <memory>
#include <array>
#include <cmath>
#include <QtWidgets/QHBoxLayout>

#include "../darksky/forecastData.h"
#include "../darksky/iconManager.h"

class CurrentlyDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CurrentlyDataWidget(const CurrentlyData& currentlyData, QWidget* parent = nullptr) : QWidget(parent)
    {
        const std::string iconPath = "res/icons/";
        const auto& [time, precipitationData, temperatureData, weatherData] = currentlyData;

        layout = std::make_unique<QGridLayout>();
        font = std::make_unique<QFont>();
        font->setPointSize(16);

        sections[0] = std::make_unique<QLabel>("Temperature");
        sections[1] = std::make_unique<QLabel>("Feels like");
        sections[2] = std::make_unique<QLabel>("Clouds");
        sections[3] = std::make_unique<QLabel>("Wind");
        sections[4] = std::make_unique<QLabel>("Pressure");

        values[0] = std::make_unique<QLabel>(QString::number(temperatureData.temperature) + " °C");
        values[1] = std::make_unique<QLabel>(QString::number(temperatureData.apparentTemperature) + " °C");
        values[2] = std::make_unique<QLabel>(QString::number(weatherData.cloudCover * 100) + "%");
        values[3] = std::make_unique<QLabel>(QString::number(weatherData.windSpeed * 3.6) + " km/h");
        values[4] = std::make_unique<QLabel>(QString::number(std::floor(weatherData.pressure)) + " hPa");

        icons[0] = std::make_unique<QLabel>();
        icons[1] = std::make_unique<QLabel>();

        auto icon0 = QIcon({QString::fromStdString(IconManager::getPath(weatherData.icon))});
        auto icon1 = QIcon({QString::fromStdString(IconManager::getPath("wind"))});

        icons[0]->setPixmap(icon0.pixmap(QSize(200, 200)));
        icons[1]->setPixmap(icon1.pixmap(QSize(200, 200)));

        separator = std::make_unique<QFrame>();
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);

        description = std::make_unique<QLabel>(QString::fromStdString(weatherData.summary));

        setLayout(layout.get());
        layout->addWidget(sections[0].get(), 1, 1, 1, 1);
        layout->addWidget(sections[1].get(), 2, 1, 1, 1);
        layout->addWidget(sections[2].get(), 4, 1, 1, 1);
        layout->addWidget(sections[3].get(), 5, 1, 1, 1);
        layout->addWidget(sections[4].get(), 6, 1, 1, 1);

        layout->addWidget(values[0].get(), 1, 2, 1, 1);
        layout->addWidget(values[1].get(), 2, 2, 1, 1);
        layout->addWidget(values[2].get(), 4, 2, 1, 1);
        layout->addWidget(values[3].get(), 5, 2, 1, 1);
        layout->addWidget(values[4].get(), 6, 2, 1, 1);

        layout->addWidget(icons[0].get(), 0, 0, 3, 1);
        layout->addWidget(icons[1].get(), 4, 0, 3, 1);

        layout->addWidget(separator.get(), 3, 0, 1, 3);
        layout->addWidget(description.get(), 0, 1, 1, 2);

        description->setFont(*font);
        for(const auto& elem : sections)
        {
            elem->setFont(*font);
            layout->QLayout::setAlignment(elem.get(), Qt::AlignLeft );
        }
        for(const auto& elem : values)
        {
            elem->setFont(*font);
            layout->QLayout::setAlignment(elem.get(), Qt::AlignRight);
        }
    }
private:
    std::array<std::unique_ptr<QLabel>, 2> icons;
    std::array<std::unique_ptr<QLabel>, 5> sections;
    std::array<std::unique_ptr<QLabel>, 5> values;

    std::unique_ptr<QFrame> separator;
    std::unique_ptr<QLabel> description;

    std::unique_ptr<QGridLayout> layout;

    std::unique_ptr<QFont> font;
};

