//============================================================================
// @name        : Window.h
// @author      : Thomas Dooms
// @date        : 6/24/19
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
#include "temperatureChart.h"

class Window : public QMainWindow
{
    Q_OBJECT;
public:
    explicit Window(QWidget* parent = nullptr) noexcept;

private:
    std::unique_ptr<QGridLayout> layout;
    std::unique_ptr<QWidget> root;

    std::unique_ptr<CurrentlyDataWidget> weatherWidget;
    std::unique_ptr<TemperatureChart> temperatureChart;
};



