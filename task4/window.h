#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include "QApplication"
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QElapsedTimer>
#include "hashtable.h"

constexpr int kWindowSize = 1600;
constexpr int kSpacing = 25;
constexpr int kMargins = 10;
constexpr int kButtonWidth = 250;
constexpr int kButtonHeight = 0x37;
constexpr int kTextEditHeight = 200;
constexpr int kLineWidth = 3;
constexpr int kTextEditWidth = 400;

class Window : public QWidget {
    Q_OBJECT

public:
    Window();

private:
    QTextEdit* hashtable_output_;
    GoodHashTable<int, int> hash_table_;
    QPushButton* fillButton_;
    QPushButton* measureButton_;
    QChartView* chartView_;

    void FillHashTable();
    void MeasureSearchTime();
    void DisplayHashTable();
    void DisplayChart(const QVector<int>& times);
};

#endif // WINDOW_H
