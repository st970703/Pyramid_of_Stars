#include <QApplication>
#include <QWidget>

#include "ui/pyramidwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *window = createPyramidWindow();
    window->show();

    return QApplication::exec();
}
