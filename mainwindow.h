#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "TreeWidget.h"
#include "RedBlackTree.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void addWord();      // Slot to handle adding a word
    void resetTree();    // Slot to reset the tree

private:
    RedBlackTree* tree;  // Red-Black Tree instance
    TreeWidget* treeWidget; // Visualization widget

    QLineEdit* wordInput;   // Input for entering a word
    QPushButton* addButton; // Button to add a word
    QPushButton* resetButton; // Button to reset the tree

    void setupUI();  // Method to set up the user interface
};

#endif // MAINWINDOW_H
