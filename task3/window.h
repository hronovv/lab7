#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QInputDialog>
#include "QApplication"
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "hashtable.h"

constexpr int kWindowSize = 1600;
constexpr int kSpacing = 25;
constexpr int kMargins = 10;
constexpr int kButtonWidth = 250;
constexpr int kButtonHeight = 0x37;
constexpr int kTextEditHeight = 575;
constexpr int kLineWidth = 3;
constexpr int kTextEditWidth = 400;

class Window : public QWidget {
    Q_OBJECT

public:
    Window();

private:
    QTextEdit* hashtable_output_;
    QTextEdit* random_hashtable_output_;
    GoodHashTable<int, int> hash_table_;
    GoodHashTable<int, int> positive_hash_table_;
    GoodHashTable<int, int> negative_hash_table_;

    void InsertRandomToHashTable();
    void DisplayHashTable();
    void GenerateRandomHashTable();
    void DisplayPositiveNegativeHashTables();
    void InsertElement();
    void SearchElement();
};

#endif // WINDOW_H
