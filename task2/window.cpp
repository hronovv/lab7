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

    auto* top_text_label = new QLabel("This program works with binary search tree (BST)", this);
    top_text_label->setStyleSheet("font-size: 17px; color: #FFFFFF; text-align: center; background-color: #333333; "
    "font-weight: bold;");
    top_text_label->setAlignment(Qt::AlignCenter);

    auto* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setLineWidth(kLineWidth);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    auto* insert_tree_button = new QPushButton("Insert", this);
    insert_tree_button->setFixedSize(kButtonWidth, kButtonHeight);
    insert_tree_button->setStyleSheet(buttonStyle);
    connect(insert_tree_button, &QPushButton::clicked, this, &Window::InsertTree);

    auto* random_tree_button = new QPushButton("Random Tree", this);
    random_tree_button->setFixedSize(kButtonWidth, kButtonHeight);
    random_tree_button->setStyleSheet(buttonStyle);
    connect(random_tree_button, &QPushButton::clicked, this, &Window::RandomTree);

    auto* delete_tree_button = new QPushButton("Delete", this);
    delete_tree_button->setFixedSize(kButtonWidth, kButtonHeight);
    delete_tree_button->setStyleSheet(buttonStyle);
    connect(delete_tree_button, &QPushButton::clicked, this, &Window::DeleteTree);

    auto* balance_tree_button = new QPushButton("Balance", this);
    balance_tree_button->setFixedSize(kButtonWidth, kButtonHeight);
    balance_tree_button->setStyleSheet(buttonStyle);
    connect(balance_tree_button, &QPushButton::clicked, this, &Window::BalanceTree);

    auto* search_tree_button = new QPushButton("Search", this);
    search_tree_button->setFixedSize(kButtonWidth, kButtonHeight);
    search_tree_button->setStyleSheet(buttonStyle);
    connect(search_tree_button, &QPushButton::clicked, this, &Window::SearchTree);

    auto* preorderButton = new QPushButton("Preorder Traversal", this);
    preorderButton->setFixedSize(kButtonWidth, kButtonHeight);
    preorderButton->setStyleSheet(buttonStyle);
    connect(preorderButton, &QPushButton::clicked, this, &Window::PreorderTraversal);

    auto* postorderButton = new QPushButton("Postorder Traversal", this);
    postorderButton->setFixedSize(kButtonWidth, kButtonHeight);
    postorderButton->setStyleSheet(buttonStyle);
    connect(postorderButton, &QPushButton::clicked, this, &Window::PostorderTraversal);

    auto* inorderButton = new QPushButton("Inorder Traversal", this);
    inorderButton->setFixedSize(kButtonWidth, kButtonHeight);
    inorderButton->setStyleSheet(buttonStyle);
    connect(inorderButton, &QPushButton::clicked, this, &Window::InorderTraversal);

    auto* swap_min_max_button = new QPushButton("Swap Min/Max", this);
    swap_min_max_button->setFixedSize(kButtonWidth, kButtonHeight);
    swap_min_max_button->setStyleSheet(buttonStyle);
    connect(swap_min_max_button, &QPushButton::clicked, this, &Window::SwapMinMax);

    auto* swap_button = new QPushButton("Swap elements", this);
    swap_button->setFixedSize(kButtonWidth, kButtonHeight);
    swap_button->setStyleSheet(buttonStyle);
    connect(swap_button, &QPushButton::clicked, this, &Window::Swap);


    auto* button_layout = new QGridLayout();
    button_layout->addWidget(insert_tree_button, 0, 0);
    button_layout->addWidget(random_tree_button, 0, 1);
    button_layout->addWidget(delete_tree_button, 0, 2);
    button_layout->addWidget(balance_tree_button, 0, 3);
    button_layout->addWidget(search_tree_button, 0, 4);
    button_layout->addWidget(preorderButton, 1, 0);
    button_layout->addWidget(postorderButton, 1, 1);
    button_layout->addWidget(inorderButton, 1, 2);
    button_layout->addWidget(swap_min_max_button, 1, 3);
    button_layout->addWidget(swap_button, 1, 4);

    button_layout->setVerticalSpacing(kSpacing);
    button_layout->setAlignment(Qt::AlignHCenter);


    auto* main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(kSpacing);
    main_layout->setContentsMargins(kMargins, kMargins, kMargins, kMargins);
    main_layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    auto* bst_label = new QLabel("BST:", this);
    bst_label->setStyleSheet("font-size: 20px; color: #FFFFFF; text-align: center; font-weight: bold;");
    bst_label->setAlignment(Qt::AlignCenter);

    treeWidget_ = new BinaryTreeWidget(this);
    treeWidget_->setFixedSize(kBSTWidgetWidth, kBSTWidgetHeight);
    treeWidget_->setTree(&tree_);

    main_layout->addWidget(top_text_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(separator);
    main_layout->addLayout(button_layout);
    main_layout->addWidget(bst_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(treeWidget_, 0, Qt::AlignHCenter);

    setLayout(main_layout);
}

void Window::InsertTree() {
    bool ok = false;
    int key = QInputDialog::getInt(this, "Insert", "Input a key (integer):", 0, -kIntMax, kIntMax, 1, &ok);
    if (!ok) {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
        return;
    }

    QString value = QInputDialog::getText(this, "Insert", "Input a value (string):", QLineEdit::Normal, "", &ok);
    if (!ok) {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
        return;
    }

    tree_.insert(key, value.toStdString());
    treeWidget_->update();
    QMessageBox::information(this, "Success", "Element has been inserted into the tree!");
}


void Window::RandomTree() {
    bool ok = false;
    int number = QInputDialog::getInt(this, "Random BST", "Input a number (amount of elements):", 0,
        1, kIntMax, 1, &ok);
    if (ok) {
        QMessageBox::information(this, "Success", "BST has been generated");
        tree_.clear();
        std::srand(std::time(nullptr));
        for (int i = 0; i < number; ++i) {
            int randomKey = std::rand() % (kNumberRange+1) - (kNumberRange/2);
            std::stringstream ss;
            ss << "Value" << (std::rand() % kValueRange);
            std::string randomValue = ss.str();
            tree_.insert(randomKey, randomValue);
        }
        treeWidget_->update();
    } else {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
    }
}

void Window::DeleteTree() {
    bool ok = false;
    int number = QInputDialog::getInt(this, "Delete", "Input a number to delete", 0, -kIntMax, kIntMax, 1, &ok);
    if (ok) {
        TreeNode<int,std::string>* node = tree_.search(number);
        if (node) {
            tree_.deleteNode(number);
            QMessageBox::information(this, "Success", "Element has been deleted from the tree!");
            treeWidget_->update();
        } else {
            QMessageBox::warning(this, "Not Found", "Element not found in the tree!");
        }
    } else {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
    }
}

void Window::BalanceTree() {
    if (tree_.getRoot() == nullptr) {
        QMessageBox::information(this, "Balance", "Tree is empty, nothing to balance!");
        return;
    }
    tree_.balance();
    treeWidget_->update();
    QMessageBox::information(this, "Success", "Tree has been balanced!");
}

void Window::SearchTree() {
    bool ok = false;
    int key = QInputDialog::getInt(this, "Search", "Input the key to find its value", 0, -kIntMax, kIntMax, 1, &ok);
    if (ok) {
        try {
            std::string value = tree_.getValueByKey(key);
            QMessageBox::information(this, "Found", "The value for key "
                + QString::number(key) + " is: " + QString::fromStdString(value));
        } catch (const std::invalid_argument& e) {
            QMessageBox::warning(this, "Not Found", "Key not found in the tree!");
        }
    } else {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
    }
}

void Window::PreorderTraversal() {
    std::string result = tree_.preorder();
    if (result.empty()) {
        QMessageBox::information(this, "Preorder Traversal", "The tree is empty.");
    } else {
        QMessageBox::information(this, "Preorder Traversal", QString::fromStdString(result));
    }
}

void Window::PostorderTraversal() {
    std::string result = tree_.postorder();
    if (result.empty()) {
        QMessageBox::information(this, "Postorder Traversal", "The tree is empty.");
    } else {
        QMessageBox::information(this, "Postorder Traversal", QString::fromStdString(result));
    }
}

void Window::InorderTraversal() {
    std::string result = tree_.inorder();
    if (result.empty()) {
        QMessageBox::information(this, "Inorder Traversal", "The tree is empty.");
    } else {
        QMessageBox::information(this, "Inorder Traversal", QString::fromStdString(result));
    }
}


void Window::SwapMinMax() {
    if (tree_.getRoot() == nullptr) {
        QMessageBox::information(this, "Swap Min/Max", "Tree is empty, no elements to swap.");
        return;
    }

    TreeNode<int, std::string>* minNode = tree_.getMinNode();
    TreeNode<int, std::string>* maxNode = tree_.getMaxNode();

    if (minNode && maxNode && (tree_.getRoot()->left || tree_.getRoot()->right)) {
        tree_.swapValues(minNode,maxNode);
        treeWidget_->update();
        QMessageBox::information(this, "Swap Min/Max", "Successfully swapped the info "
                                                       "from minimum and maximum elements.");
    } else {
        QMessageBox::warning(this, "Swap Min/Max", "Unable to swap elements."
                                                   "Check if the tree can be operated on with this method");
    }
}

void Window::Swap() {
    bool ok = false;
    int key1 = QInputDialog::getInt(this, "Swap", "Input the first key:", 0, -kIntMax, kIntMax, 1, &ok);
    if (!ok) {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
        return;
    }

    int key2 = QInputDialog::getInt(this, "Swap", "Input the second key:", 0, -kIntMax, kIntMax, 1, &ok);
    if (!ok) {
        QMessageBox::information(this, "Cancel", "Operation is cancelled");
        return;
    }

    TreeNode<int, std::string>* node1 = tree_.search(key1);
    TreeNode<int, std::string>* node2 = tree_.search(key2);

    if (node1 && node2) {
        std::string tempValue = node1->value;
        node1->value = node2->value;
        node2->value = tempValue;
        treeWidget_->update();
        QMessageBox::information(this, "Swap", "Successfully swapped the values of the elements.");
    } else {
        QMessageBox::warning(this, "Not Found", "One or both keys were not found in the tree.");
    }
}




