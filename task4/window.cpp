#include "window.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

Window::Window()
    : hash_table_(1000) {

    QString buttonStyle = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 16px;
            margin: 5px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QPushButton:pressed {
            background-color: #d0d0d0;
            color: #333333;
        }
    )";

    QString textStyle = R"(
        font-size: 17px;
        color: #FFFFFF;
    )";

    QString textEditStyle = R"(
        font-size: 17px;
        background-color: #f9f9f9;
        color: #000000;
        border: 2px solid #000000;
        border-radius: 5px;
    )";
    QVBoxLayout* layout = new QVBoxLayout(this);


    hashtable_output_ = new QTextEdit(this);
    hashtable_output_->setStyleSheet(textEditStyle);
    hashtable_output_->setFixedHeight(kTextEditHeight);

    layout->addWidget(hashtable_output_);


    fillButton_ = new QPushButton("Заполнить таблицу случайными значениями", this);
    layout->addWidget(fillButton_);
    connect(fillButton_, &QPushButton::clicked, this, &Window::FillHashTable);


    measureButton_ = new QPushButton("Измерить время поиска", this);
    layout->addWidget(measureButton_);
    connect(measureButton_, &QPushButton::clicked, this, &Window::MeasureSearchTime);


    chartView_ = new QChartView(this);
    layout->addWidget(chartView_);
}

void Window::FillHashTable() {
    hash_table_.clear();
    for (int i = 0; i < 1000; ++i) {
        int key = QRandomGenerator::global()->bounded(1000);
        int value = QRandomGenerator::global()->bounded(1000);
        hash_table_.insert(key, value);
    }
    DisplayHashTable();
}

void Window::MeasureSearchTime() {
    for (int i = 0; i < 10; ++i) {
        int key = QRandomGenerator::global()->bounded(1000);
        try {
            hash_table_.search(key);
        } catch (const std::exception&) {
        }
    }

    QVector<int> times;
    const int numRequests = 400;
    const int numRepeats = 5;

    for (int i = 0; i < numRequests; ++i) {
        int key = QRandomGenerator::global()->bounded(1000);
        qint64 totalElapsed = 0;


        for (int j = 0; j < numRepeats; ++j) {
            QElapsedTimer timer;
            timer.start();

            try {
                hash_table_.search(key);
            } catch (const std::exception&) {
            }

            totalElapsed += timer.nsecsElapsed();
        }


        times.push_back(static_cast<int>(totalElapsed / numRepeats));
    }


    DisplayChart(times);
}




void Window::DisplayHashTable() {
    hashtable_output_->setText(QString::fromStdString(hash_table_.toString()));
}


void Window::DisplayChart(const QVector<int>& times) {
    QLineSeries* series = new QLineSeries();
    for (int i = 0; i < times.size(); ++i) {
        series->append(i, times[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Время поиска в хеш-таблице");


    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("Номер запроса");
    axisX->setLabelFormat("%d");
    axisX->setTickCount(10);
    axisX->setRange(0, times.size() - 1);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Время (нс)");
    axisY->setLabelFormat("%d");
    axisY->setTickCount(10);
    axisY->setRange(0, *std::max_element(times.begin(), times.end()) + 1);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    chartView_->setChart(chart);
}
