#ifndef TREEWIDGET_H
#define TREEWIDGET_H

// Include guards to prevent multiple inclusions of this header file

#include <QWidget>        // Include for the QWidget base class
#include <QPainter>       // Include for QPainter, used for custom rendering
#include "RedBlackTree.h" // Include the header file for the Red-Black Tree class

// TreeWidget is a custom widget that visualizes a Red-Black Tree
class TreeWidget : public QWidget {
    Q_OBJECT  // Qt macro enabling signals and slots functionality in this class

public:
    explicit TreeWidget(QWidget* parent = nullptr);
    // Constructor for TreeWidget, with an optional parent QWidget parameter

    void setTree(RedBlackTree* tree);
    // Method to set the Red-Black Tree to be visualized

protected:
    void paintEvent(QPaintEvent* event) override;
    // Overrides the paintEvent from QWidget to handle custom rendering

private:
    RedBlackTree* tree;  // Pointer to the Red-Black Tree to be visualized

    void drawTree(Node* node, QPainter* painter, int x, int y, int level);
    // Helper function to recursively draw the Red-Black Tree starting from the given node
    // 'painter' is used for rendering, 'x' and 'y' determine the position, and 'level' tracks tree depth
};

#endif // TREEWIDGET_H
// End of the include guard
