#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include "QInputDialog"
#include <QGridLayout>
#include "QMessageBox"
#include "QComboBox"
#include "QLabel"
#include <QFrame>
#include "QString"
#include <QTextEdit>
#include <QRandomGenerator>
#include <sstream>
#include <optional>
#include <cstdlib>
#include <ctime>x
#include "BinaryTreeWidget.h"

constexpr int kWindowSize = 1600;
constexpr int kSpacing = 10;
constexpr int kMargins = 20;
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
constexpr int kBSTWidgetWidth = 900;
constexpr int kBSTWidgetHeight = 700;
constexpr int kNumberRange = 150;
constexpr int kValueRange = 1000;

class Window : public QWidget {
    Q_OBJECT

public:
    Window();

private:
    BinaryTreeWidget* treeWidget_;
    GoodBST<int, std::string> tree_;

    void InsertTree();
    void RandomTree();
    void DeleteTree();
    void BalanceTree();
    void SearchTree();
    void PreorderTraversal();
    void PostorderTraversal();
    void InorderTraversal();
    void SwapMinMax();
    void Swap();

};
#endif //WINDOW_H
