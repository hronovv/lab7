#include "window.h"


Window::Window() {
    QString buttonStyle = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 17px;
            font-family: 'Orbitron';
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
        font-family: 'Orbitron';
        color: #FFFFFF;
    )";

    QString textEditStyle = R"(
        font-size: 17px;
        font-family: 'Orbitron';
        background-color: #f9f9f9;
        color: #000000;
        border: 2px solid #000000;
        border-radius: 5px;
    )";



    auto* top_text_label = new QLabel("This program works with queue<int>, which is based on doubly linked list", this);
    top_text_label->setStyleSheet("font-size: 17px; color: #FFFFFF; text-align: center;font-family: 'Orbitron';"
                                  " background-color: #333333; "
    "font-weight: bold;");
    top_text_label->setAlignment(Qt::AlignCenter);


    auto* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setLineWidth(kLineWidth);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    auto* push_queue_button = new QPushButton("Push", this);
    push_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    push_queue_button->setStyleSheet(buttonStyle);
    connect(push_queue_button, &QPushButton::clicked, this,&Window::PushQueue);

    auto* pop_queue_button = new QPushButton("Pop", this);
    pop_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    pop_queue_button->setStyleSheet(buttonStyle);
    connect(pop_queue_button, &QPushButton::clicked, this,&Window::PopQueue);

    auto* front_queue_button = new QPushButton("Front", this);
    front_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    front_queue_button->setStyleSheet(buttonStyle);
    connect(front_queue_button, &QPushButton::clicked, this,&Window::FrontQueue);

    auto* back_queue_button = new QPushButton("Back", this);
    back_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    back_queue_button->setStyleSheet(buttonStyle);
    connect(back_queue_button, &QPushButton::clicked, this, &Window::BackQueue);

    auto* size_queue_button = new QPushButton("Size", this);
    size_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    size_queue_button->setStyleSheet(buttonStyle);
    connect(size_queue_button, &QPushButton::clicked, this, &Window::SizeQueue);

    auto* empty_queue_button = new QPushButton("Empty?", this);
    empty_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    empty_queue_button->setStyleSheet(buttonStyle);
    connect(empty_queue_button, &QPushButton::clicked, this, &Window::EmptyQueue);

    auto* random_queue_button = new QPushButton("Random queue", this);
    random_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    random_queue_button->setStyleSheet(buttonStyle);
    connect(random_queue_button, &QPushButton::clicked, this, &Window::GenerateRandomQueue);

    auto* min_to_front_queue_button = new QPushButton("Min to front", this);
    min_to_front_queue_button->setFixedSize(kButtonWidth, kButtonHeight);
    min_to_front_queue_button->setStyleSheet(buttonStyle);
    connect(min_to_front_queue_button, &QPushButton::clicked, this, &Window::MinToFrontQueue);


    auto* button_layout = new QGridLayout();
    button_layout->addWidget(push_queue_button, 0, 0);
    button_layout->addWidget(pop_queue_button, 1, 0);
    button_layout->addWidget(front_queue_button, 0, 1);
    button_layout->addWidget(back_queue_button, 1, 1);
    button_layout->addWidget(size_queue_button, 0, 2);
    button_layout->addWidget(empty_queue_button, 1, 2);
    button_layout->addWidget(random_queue_button, 0, 3);
    button_layout->addWidget(min_to_front_queue_button, 1, 3);
    button_layout->setAlignment(Qt::AlignHCenter);




    auto* main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins,kMargins,kMargins,kMargins);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    queue_output_ = new QTextEdit(this);
    queue_output_->setText("Sandbox");
    queue_output_->setReadOnly(true);
    queue_output_->setStyleSheet(textEditStyle);
    queue_output_->setFixedWidth(kTextEditWidth);
    queue_output_->setFixedHeight(kTextEditHeight);

    queue_random_output_ = new QTextEdit(this);
    queue_random_output_->setText("For individual task");
    queue_random_output_->setReadOnly(true);
    queue_random_output_->setStyleSheet(textEditStyle);
    queue_random_output_->setFixedWidth(kTextEditWidth);
    queue_random_output_->setFixedHeight(kTextEditHeight);

    main_layout->addWidget(top_text_label);
    main_layout->addWidget(separator);
    main_layout->addLayout(button_layout);
    auto* output_layout = new QHBoxLayout();
    output_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    output_layout->addWidget(queue_output_);
    output_layout->addWidget(queue_random_output_);
    main_layout->addLayout(output_layout);


    setLayout(main_layout);
}

void Window::PushQueue() {
    bool ok = false;
    int number = QInputDialog::getInt(this,"Push","Input a number",0,-kIntMax,kIntMax,1,&ok);
    if (ok) {
        QMessageBox::information(this,"Success","Element has been pushed to the queue!");
        my_queue_.push(number);
        PrintQueue();
    } else {
        QMessageBox::information(this,"Cancel","Operation is cancelled");
    }
}

void Window::PopQueue() {
    if (!my_queue_.empty()) {
        my_queue_.pop();
        QMessageBox::information(this,"Success","Element has been popped from the queue!");
        PrintQueue();
    } else {
        QMessageBox::warning(this,"Error","You can't pop from the empty queue");
    }
}

void Window::FrontQueue() {
    if (!my_queue_.empty()) {
        QMessageBox::information(this,"Front","The element in the head of the queue is "
            + QString::number(my_queue_.front()));
    } else {
        QMessageBox::warning(this,"Error","Queue is empty");
    }
}

void Window::BackQueue() {
    if (!my_queue_.empty()) {
        QMessageBox::information(this, "Back", "The element at the tail of the queue is "
            + QString::number(my_queue_.back()));
    } else {
        QMessageBox::warning(this, "Error", "Queue is empty");
    }
}

void Window::SizeQueue() {
    QMessageBox::information(this, "Size", "The size of the queue is "
        + QString::number(my_queue_.size()));
}

void Window::EmptyQueue() {
    QString result = my_queue_.empty() ? "Queue is empty" : "Queue is not empty";
    QMessageBox::information(this, "Empty", result);
}

void Window::PrintQueue() {
    QString output;
    GoodQueue<int> copy = my_queue_;
    while (!copy.empty()) {
        output += QString::number(copy.front()) + "\n";
        copy.pop();
    }
    queue_output_->setText("Sandbox\nQueue elements:\n" + output.trimmed());
}

void Window::PrintRandomQueue() {
    QString output;
    GoodQueue<int> copy = my_random_queue_;
    while (!copy.empty()) {
        output += QString::number(copy.front()) + "\n";
        copy.pop();
    }
    queue_random_output_->setText("For individual task\nQueue elements:\n" + output.trimmed());
}

void Window::GenerateRandomQueue() {
    my_random_queue_.clear();
    int count = QRandomGenerator::global()->bounded(kLowestAmount, kHighestAmount);
    for (int i = 0; i < count; ++i) {
        int value = QRandomGenerator::global()->bounded(-kRangeInt, kRangeInt+1);
        my_random_queue_.push(value);
    }
    QMessageBox::information(this, "Random Queue", "A random queue has been generated.");
    PrintRandomQueue();
}

void Window::MinToFrontQueue() {
    if (my_random_queue_.empty()) {
        QMessageBox::warning(this, "Error", "Queue is empty");
        return;
    }

    GoodQueue<int> temp_queue;
    int min_val = my_random_queue_.front();
    QVector<int> values;

    while (!my_random_queue_.empty()) {
        int val = my_random_queue_.front();
        if (val < min_val) min_val = val;
        values.push_back(val);
        my_random_queue_.pop();
    }

    temp_queue.push(min_val);
    bool min_pushed = false;

    for (int val : values) {
        if (val == min_val && !min_pushed) {
            min_pushed = true;
            continue;
        }
        temp_queue.push(val);
    }

    my_random_queue_ = temp_queue;

    QMessageBox::information(this, "Success", "Minimal element moved to the front of the queue.");
    PrintRandomQueue();
}



