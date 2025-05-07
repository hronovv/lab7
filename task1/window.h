#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include "QInputDialog"
#include <QGridLayout>
#include "bits/stdc++.h"
#include "QMessageBox"
#include "QComboBox"
#include "QLabel"
#include <QFrame>
#include "QString"
#include <QTextEdit>
#include <QRandomGenerator>
#include <sstream>
#include <optional>
#include "queue.h"


constexpr int kWindowSize = 1600;
constexpr int kSpacing = 25;
constexpr int kMargins = 10;
constexpr int kButtonWidth = 0xc8;
constexpr int kButtonHeight = 0x37;
constexpr int kBits = 21;
constexpr int kIntMax = 2147483647;
constexpr int kLineWidth = 3;
constexpr int kTextEditHeight = 575;
constexpr int kTextEditWidth = 400;
constexpr int kLowestAmount = 10;
constexpr int kHighestAmount = 16;
constexpr int kRangeInt = 100;

class Window : public QWidget {
    Q_OBJECT

    public:

    Window();

private:
    QTextEdit* queue_output_;
    QTextEdit* queue_random_output_;
    GoodQueue<int> my_queue_;
    GoodQueue<int> my_random_queue_;


    void PushQueue();
    void PopQueue();
    void FrontQueue();
    void BackQueue();
    void SizeQueue();
    void EmptyQueue();
    void PrintQueue();
    void PrintRandomQueue();
    void GenerateRandomQueue();
    void MinToFrontQueue();
};


#endif //WINDOW_H
