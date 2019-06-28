#include <QtWidgets/qapplication.h>
#include "gui/currentlyDataWindow.h"
#include "gui/Window.h"


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        QApplication application(argc, argv);
        Window window;
        return QApplication::exec();
    }
    else throw std::runtime_error("program does not support arguments yet");
}