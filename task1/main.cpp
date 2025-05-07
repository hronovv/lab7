#include "window.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto* window = new Window();
    window->setWindowTitle("Queue, hopefully.");
    window->resize(kWindowSize, kWindowSize);
    window->show();
    return a.exec();
}
