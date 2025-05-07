#ifndef BINARYTREEWIDGET_H
#define BINARYTREEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include "bst.h"

constexpr int kVerticalStep = 60;
constexpr int kPenWidth = 3;
constexpr int kCircleDiameter = 40;

class BinaryTreeWidget : public QWidget {
    Q_OBJECT

public:
    explicit BinaryTreeWidget(QWidget* parent = nullptr) : QWidget(parent), tree(nullptr) {}

    void setTree(GoodBST<int, std::string>* newTree) {
        tree = newTree;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (tree) {
            drawTree(&painter, tree->getRoot(), width() / 2, 50, width()/4.2);
        }
    }

private:
    GoodBST<int, std::string>* tree;

    void drawTree(QPainter* painter, TreeNode<int, std::string>* node, int x, int y, double dx) {
        if (!node) {
            return;
        }

        if (node->left) {
            painter->setPen(QPen(Qt::blue, kPenWidth));
            painter->drawLine(x, y, x - dx, y + kVerticalStep);
            drawTree(painter, node->left, x - dx, y + kVerticalStep, dx / 2);
        }

        if (node->right) {
            painter->setPen(QPen(Qt::red, kPenWidth));
            painter->drawLine(x, y, x + dx, y + kVerticalStep);
            drawTree(painter, node->right, x + dx, y + kVerticalStep, dx / 2);
        }

        painter->setBrush(QBrush(Qt::green));
        painter->setPen(QPen(Qt::black,2));
        painter->drawEllipse(x - kCircleDiameter / 2, y - kCircleDiameter / 2, kCircleDiameter, kCircleDiameter);

        QFont font = painter->font();
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(x - 10, y + 5, QString::number(node->key));
    }
};

#endif // BINARYTREEWIDGET_H
