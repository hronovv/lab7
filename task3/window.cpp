#include "window.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

Window::Window() {
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

    // Заголовок
    auto* top_text_label = new QLabel("This program works with a hash table with random keys", this);
    top_text_label->setStyleSheet("font-size: 17px; color: #FFFFFF; text-align: center; background-color: #333333; "
    "font-weight: bold;");
    top_text_label->setAlignment(Qt::AlignCenter);

    // Разделитель
    auto* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setLineWidth(kLineWidth);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Кнопки
    auto* generate_button = new QPushButton("Random HashTable", this);
    generate_button->setFixedSize(kButtonWidth, kButtonHeight);
    generate_button->setStyleSheet(buttonStyle);
    connect(generate_button, &QPushButton::clicked, this, &Window::GenerateRandomHashTable);

    auto* display_button = new QPushButton("Display", this);
    display_button->setFixedSize(kButtonWidth, kButtonHeight);
    display_button->setStyleSheet(buttonStyle);
    connect(display_button, &QPushButton::clicked, this, &Window::DisplayHashTable);

    auto* separate_button = new QPushButton("Positive/Negative Tables", this);
    separate_button->setFixedSize(kButtonWidth, kButtonHeight);
    separate_button->setStyleSheet(buttonStyle);
    connect(separate_button, &QPushButton::clicked, this, &Window::DisplayPositiveNegativeHashTables);

    auto* insert_button = new QPushButton("Insert Element", this);
    insert_button->setFixedSize(kButtonWidth, kButtonHeight);
    insert_button->setStyleSheet(buttonStyle);
    connect(insert_button, &QPushButton::clicked, this, &Window::InsertElement);

    auto* search_button = new QPushButton("Search Element", this);
    search_button->setFixedSize(kButtonWidth, kButtonHeight);
    search_button->setStyleSheet(buttonStyle);
    connect(search_button, &QPushButton::clicked, this, &Window::SearchElement);



    // Горизонтальный layout для кнопок
    auto* button_layout = new QHBoxLayout();
    button_layout->addWidget(generate_button);
    button_layout->addWidget(display_button);
    button_layout->addWidget(separate_button);
    button_layout->addWidget(insert_button);
    button_layout->addWidget(search_button);
    button_layout->setAlignment(Qt::AlignHCenter);

    // Основной вертикальный layout
    auto* main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins, kMargins, kMargins, kMargins);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);


    auto text_edit_layout = new QHBoxLayout();
    hashtable_output_ = new QTextEdit(this);
    hashtable_output_->setReadOnly(true);
    hashtable_output_->setStyleSheet(textEditStyle);
    hashtable_output_->setFixedHeight(kTextEditHeight);
    hashtable_output_->setFixedWidth(kTextEditWidth);

    random_hashtable_output_ = new QTextEdit(this);
    random_hashtable_output_->setReadOnly(true);
    random_hashtable_output_->setStyleSheet(textEditStyle);
    random_hashtable_output_->setFixedHeight(kTextEditHeight);
    random_hashtable_output_->setFixedWidth(kTextEditWidth);

    text_edit_layout->addWidget(hashtable_output_);
    text_edit_layout->addWidget(random_hashtable_output_);
    text_edit_layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    main_layout->addWidget(top_text_label);
    main_layout->addWidget(separator);
    main_layout->addLayout(button_layout);
    main_layout->addLayout(text_edit_layout);

    setLayout(main_layout);
}




void Window::GenerateRandomHashTable() {
    hash_table_.clear();
    int count = QRandomGenerator::global()->bounded(10, 20);
    for (int i = 0; i < count; ++i) {
        int random_key = QRandomGenerator::global()->bounded(-50, 51);
        int random_value = QRandomGenerator::global()->bounded(-100, 101);
        hash_table_.insert(random_key, random_value);
    }
    QMessageBox::information(this, "Success", "Random hash table has been generated.");
}

void Window::DisplayHashTable() {
    QString output;
    for (int i = 0; i < GoodHashTable<int, int>::getTableSize(); ++i) {
        auto* bucket = hash_table_.getBucket(i);
        if (bucket) {
            StackNode<std::pair<int, int>>* current = bucket->getTop();
            while (current) {
                output += QString::number(current->data.first) + ": " + QString::number(current->data.second) + "\n";
                current = current->next;
            }
        }
    }
    hashtable_output_->setText("Hash Table:\n" + output.trimmed());
}

void Window::DisplayPositiveNegativeHashTables() {
    positive_hash_table_.clear();
    negative_hash_table_.clear();

    for (int i = 0; i < GoodHashTable<int, int>::getTableSize(); ++i) {
        auto* bucket = hash_table_.getBucket(i);
        if (bucket) {
            StackNode<std::pair<int, int>>* current = bucket->getTop();
            while (current) {
                int key = current->data.first;
                if (key > 0) {
                    positive_hash_table_.insert(key, current->data.second);
                } else if (key < 0) {
                    negative_hash_table_.insert(key, current->data.second);
                }
                current = current->next;
            }
        }
    }

    QString positive_output;
    for (int i = 0; i < GoodHashTable<int, int>::getTableSize(); ++i) {
        auto* bucket = positive_hash_table_.getBucket(i);
        if (bucket) {
            StackNode<std::pair<int, int>>* current = bucket->getTop();
            while (current) {
                positive_output += QString::number(current->data.first) + ": " + QString::number(current->data.second)
                + "\n";
                current = current->next;
            }
        }
    }

    QString negative_output;
    for (int i = 0; i < GoodHashTable<int, int>::getTableSize(); ++i) {
        auto* bucket = negative_hash_table_.getBucket(i);
        if (bucket) {
            StackNode<std::pair<int, int>>* current = bucket->getTop();
            while (current) {
                negative_output += QString::number(current->data.first) + ": " + QString::number(current->data.second)
                + "\n";
                current = current->next;
            }
        }
    }

    random_hashtable_output_->setText("Positive Hash Table:\n" + positive_output.trimmed() +
                            "\n\nNegative Hash Table:\n" + negative_output.trimmed());
}

void Window::InsertElement() {
    bool ok;
    int key = QInputDialog::getInt(this, "Insert Element", "Enter key:", 0, -1000, 1000, 1, &ok);
    if (ok) {
        int value = QInputDialog::getInt(this, "Insert Element", "Enter value for key " + QString::number(key) + ":",
            0, -1000, 1000, 1, &ok);
        if (ok) {
            hash_table_.insert(key, value);
            QMessageBox::information(this, "Success", "Element inserted: " + QString::number(key) + " -> " +
                QString::number(value));
        }
    }
}

void Window::SearchElement() {
    bool ok;
    int key = QInputDialog::getInt(this, "Search Element", "Enter key to search:", 0, -1000, 1000, 1, &ok);
    if (ok) {
        try {
            int value = hash_table_.search(key); 
            QMessageBox::information(this, "Found", "Element found: " + QString::number(key) + " -> " +
                QString::number(value));
        } catch (const std::runtime_error& e) {  // Обработка исключения, если ключ не найден
            QMessageBox::information(this, "Not Found", "Element with key " + QString::number(key) + " not found.");
        }
    }
}

