#include "TreeWidget.h"

TreeWidget::TreeWidget(QWidget* parent) : QWidget(parent), tree(nullptr) {}

void TreeWidget::setTree(RedBlackTree* tree) {
    this->tree = tree;
    update();  // Trigger a redraw whenever the tree changes
}

void TreeWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Smooth drawing

    if (tree != nullptr && tree->getRoot() != tree->getTNULL()) {
        // Start drawing from the root of the tree
        drawTree(tree->getRoot(), &painter, width() / 2, 30, 1);
    }
}

void TreeWidget::drawTree(Node* node, QPainter* painter, int x, int y, int level) {
    if (node == tree->getTNULL()) return;  // Base case for null nodes

    // Draw the node (circle with text for word and frequency)
    painter->setPen(Qt::black);
    painter->setBrush(node->color == RED ? Qt::red : Qt::black);  // Red or Black nodes
    painter->drawEllipse(x - 20, y - 20, 40, 40);  // Draw node as a circle

    painter->setPen(Qt::white);
    QString nodeText = QString::fromStdString(node->word) + ":" + QString::number(node->frequency);
    painter->drawText(x - 15, y, nodeText);

    // Draw edges and recursively draw children
    int childXOffset = 50;  // Horizontal distance between nodes
    int childYOffset = 50;  // Vertical distance between levels

    if (node->left != tree->getTNULL()) {
        painter->setPen(Qt::black);
        painter->drawLine(x, y + 20, x - childXOffset, y + childYOffset);  // Line to left child
        drawTree(node->left, painter, x - childXOffset, y + childYOffset, level + 1);
    }

    if (node->right != tree->getTNULL()) {
        painter->setPen(Qt::black);
        painter->drawLine(x, y + 20, x + childXOffset, y + childYOffset);  // Line to right child
        drawTree(node->right, painter, x + childXOffset, y + childYOffset, level + 1);
    }
}
