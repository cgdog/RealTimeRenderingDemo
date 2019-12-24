#include "mainwindow.h"
#include "Utilities/helperFuncs.h"
using namespace LXY;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mb(nullptr)
{
    glWidget = new TriangleQuadRenderer;
    setCentralWidget(glWidget);
    processMenu();
}

MainWindow::~MainWindow()
{
    if (nullptr !=glWidget)
    {
        delete glWidget;
        glWidget = nullptr;
    }
}

void MainWindow::processMenu()
{
    mb = menuBar();
    if (nullptr != mb)
    {
        auto fileMenu = mb->addMenu(tr("&File"));
        fileMenu->addAction("Load &Model and Shaders", this, SLOT(onClickLoadModelAndShaders()));
        fileMenu->addAction("&Load Model", this, SLOT(onClickLoadModel()));
        fileMenu->addAction("Load &Shaders", this, SLOT(onClickLoadShaders()));
    }
}

void MainWindow::onClickLoadModelAndShaders()
{
    QStringList files = LXY::OpenFileChooser(tr("选择模型和shader文件"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.off *.vs *.fs)"));
    string modelPath;
    QString vsPath;
    QString fsPath;
    for(auto filePath : files) {

        if (filePath.endsWith(".vs"))
        {
            vsPath = filePath;
        }
        else if (filePath.endsWith(".fs"))
        {
            fsPath = filePath;
        }
        else if (filePath.endsWith(".off"))
        {
            modelPath = filePath.toStdString();
        }
    }

    this->glWidget->changeModelAndShaders(modelPath, vsPath, fsPath);
}

void MainWindow::onClickLoadModel()
{
    QStringList modelFiles = LXY::OpenFileChooser(tr("选择模型文件"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.off)"), false);
     for (auto filePath : modelFiles) {
         this->glWidget->changeModel(filePath.toStdString());
     }
}

void MainWindow::onClickLoadShaders()
{
    QStringList shaderFiles = LXY::OpenFileChooser(tr("选择shader"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.vs *.fs)"));
    QString vsPath;
    QString fsPath;
    for(auto filePath : shaderFiles) {
        if (filePath.endsWith(".vs")) {
            vsPath = filePath;
        } else if (filePath.endsWith(".fs")) {
            fsPath = filePath;
        }
    }

    this->glWidget->changeShaders(vsPath, fsPath);
}

