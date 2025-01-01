#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), tree(new RedBlackTree()), treeWidget(new TreeWidget(this)) {
    setupUI();
}

void MainWindow::setupUI() {
    // Set the main window title
    setWindowTitle("Red-Black Tree Word Frequency Visualizer");

    // Create widgets
    wordInput = new QLineEdit(this);
    wordInput->setPlaceholderText("Enter a word...");

    addButton = new QPushButton("Add Word", this);
    resetButton = new QPushButton("Reset Tree", this);

    treeWidget->setTree(tree);

    // Layout setup
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();

    inputLayout->addWidget(wordInput);
    inputLayout->addWidget(addButton);
    inputLayout->addWidget(resetButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(treeWidget);

    // Create a central widget and set layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addWord);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetTree);
}

void MainWindow::addWord() {
    QString word = wordInput->text();
    if (!word.isEmpty()) {
        std::string wordStd = word.toStdString();
        tree->insert(wordStd);  // Insert the word into the tree
        wordInput->clear();
        treeWidget->update();  // Redraw the tree visualization
    }
}

void MainWindow::resetTree() {
    delete tree;
    tree = new RedBlackTree();
    treeWidget->setTree(tree);
    treeWidget->update();  // Redraw the tree visualization
}
