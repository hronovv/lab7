#include "window.h"


Window::Window() {
    QString buttonStyle = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 17px;
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


    auto* top_text_label = new QLabel("This program works with dequeue<int>, which is based on stack array", this);
    top_text_label->setStyleSheet("font-size: 17px; color: #FFFFFF; text-align: center; background-color: #333333; "
    "font-weight: bold;");
    top_text_label->setAlignment(Qt::AlignCenter);


    auto* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setLineWidth(kLineWidth);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    auto* push_back_deque_button = new QPushButton("Push Back (Deque)", this);
    push_back_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    push_back_deque_button->setStyleSheet(buttonStyle);
    connect(push_back_deque_button, &QPushButton::clicked, this, &Window::PushBackDeque);

    auto* push_front_deque_button = new QPushButton("Push Front (Deque)", this);
    push_front_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    push_front_deque_button->setStyleSheet(buttonStyle);
    connect(push_front_deque_button, &QPushButton::clicked, this, &Window::PushFrontDeque);

    auto* pop_back_deque_button = new QPushButton("Pop Back (Deque)", this);
    pop_back_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    pop_back_deque_button->setStyleSheet(buttonStyle);
    connect(pop_back_deque_button, &QPushButton::clicked, this, &Window::PopBackDeque);

    auto* pop_front_deque_button = new QPushButton("Pop Front (Deque)", this);
    pop_front_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    pop_front_deque_button->setStyleSheet(buttonStyle);
    connect(pop_front_deque_button, &QPushButton::clicked, this, &Window::PopFrontDeque);

    auto* clear_deque_button = new QPushButton("Clear (Deque)", this);
    clear_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    clear_deque_button->setStyleSheet(buttonStyle);
    connect(clear_deque_button, &QPushButton::clicked, this, &Window::ClearDeque);

    auto* size_deque_button = new QPushButton("Size (Deque)", this);
    size_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    size_deque_button->setStyleSheet(buttonStyle);
    connect(size_deque_button, &QPushButton::clicked, this, &Window::SizeDeque);

    auto* empty_deque_button = new QPushButton("Empty? (Deque)", this);
    empty_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    empty_deque_button->setStyleSheet(buttonStyle);
    connect(empty_deque_button, &QPushButton::clicked, this, &Window::EmptyDeque);

    auto* random_deque_button = new QPushButton("Random deque", this);
    random_deque_button->setFixedSize(kButtonWidth, kButtonHeight);
    random_deque_button->setStyleSheet(buttonStyle);
    connect(random_deque_button, &QPushButton::clicked, this, &Window::GenerateRandomDeque);



    auto* button_layout = new QGridLayout();
    button_layout->addWidget(push_back_deque_button, 0, 0);
    button_layout->addWidget(push_front_deque_button, 0, 1);
    button_layout->addWidget(pop_back_deque_button, 0, 2);
    button_layout->addWidget(pop_front_deque_button, 0, 3);
    button_layout->addWidget(clear_deque_button, 1, 0);
    button_layout->addWidget(size_deque_button, 1, 1);
    button_layout->addWidget(empty_deque_button, 1, 2);
    button_layout->addWidget(random_deque_button,1,3);

    button_layout->setAlignment(Qt::AlignHCenter);




    auto* main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins,kMargins,kMargins,kMargins);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    deque_output_ = new QTextEdit(this);
    deque_output_->setText("Sandbox");
    deque_output_->setReadOnly(true);
    deque_output_->setStyleSheet(textEditStyle);
    deque_output_->setFixedWidth(kTextEditWidth);
    deque_output_->setFixedHeight(kTextEditHeight);


    main_layout->addWidget(top_text_label);
    main_layout->addWidget(separator);
    main_layout->addLayout(button_layout);
    auto* output_layout = new QHBoxLayout();
    output_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    output_layout->addWidget(deque_output_);
    main_layout->addLayout(output_layout);


    setLayout(main_layout);
}

void Window::PushBackDeque() {
    bool ok = false;
    int number = QInputDialog::getInt(this,"Push Back","Input a number",0,-kIntMax,kIntMax,1,&ok);
    if (ok) {
        my_deque_.push_back(number);
        QMessageBox::information(this,"Success","Element pushed back to deque");
        PrintDeque();
    }
}

void Window::PushFrontDeque() {
    bool ok = false;
    int number = QInputDialog::getInt(this,"Push Front","Input a number",0,-kIntMax,kIntMax,1,&ok);
    if (ok) {
        my_deque_.push_front(number);
        QMessageBox::information(this,"Success","Element pushed front to deque");
        PrintDeque();
    }
}

void Window::PopBackDeque() {
    if (!my_deque_.empty()) {
        my_deque_.pop_back();
        QMessageBox::information(this,"Success","Element popped back from deque");
        PrintDeque();
    } else {
        QMessageBox::warning(this,"Error","Deque is empty");
    }
}

void Window::PopFrontDeque() {
    if (!my_deque_.empty()) {
        my_deque_.pop_front();
        QMessageBox::information(this,"Success","Element popped front from deque");
        PrintDeque();
    } else {
        QMessageBox::warning(this,"Error","Deque is empty");
    }
}

void Window::ClearDeque() {
    my_deque_.clear();
    QMessageBox::information(this,"Success","Deque cleared");
    PrintDeque();
}

void Window::SizeDeque() {
    QMessageBox::information(this,"Size","Deque size is " + QString::number(my_deque_.size()));
}

void Window::EmptyDeque() {
    QString result = my_deque_.empty() ? "Deque is empty" : "Deque is not empty";
    QMessageBox::information(this,"Empty", result);
}

void Window::PrintDeque() {
    QString output;
    GoodDeque<int> copy = my_deque_;
    while (!copy.empty()) {
        output += QString::number(copy.front()) + "\n";
        copy.pop_front();
    }
    deque_output_->setText("Deque sandbox\nElements:\n" + output.trimmed());
}

void Window::GenerateRandomDeque() {
    my_deque_.clear();
    int count = QRandomGenerator::global()->bounded(kLowestAmount, kHighestAmount);
    for (int i = 0; i < count; ++i) {
        int value = QRandomGenerator::global()->bounded(-kRangeInt, kRangeInt+1);
        my_deque_.push_back(value);
    }
    QMessageBox::information(this, "Random Deque", "A random deque has been generated.");
    PrintDeque();
}




