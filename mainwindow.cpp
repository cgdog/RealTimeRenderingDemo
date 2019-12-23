#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new TriangleQuadRenderer;
    setCentralWidget(glWidget);
}

MainWindow::~MainWindow()
{
    if (nullptr !=glWidget)
    {
        delete glWidget;
        glWidget = nullptr;
    }
}

