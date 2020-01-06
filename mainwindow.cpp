#include "mainwindow.h"
#include "Utilities/helperFuncs.h"
#include "Math/matrix4d.h"
#include <sstream>

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
        fileMenu->addAction("Load View Matrix", this, SLOT(onLoadViewMatrix()));
        fileMenu->addAction("Save View Matrix", this, SLOT(onSaveViewMatrix()));

        // for test.
        auto testMenu = mb->addMenu(tr("&Test"));
        testMenu->addAction("Test Matrix", this, SLOT(onClickTestMatrix()));
    }
}

void MainWindow::onClickLoadModelAndShaders()
{
    QStringList files = LXY::OpenFileChooser(tr("选择模型和shader文件"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.off *.obj *.vs *.fs)"));
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
        else if (filePath.endsWith(".off") || filePath.endsWith(".obj"))
        {
            modelPath = filePath.toStdString();
            setTitle(filePath);
        }
    }

    this->glWidget->changeModelAndShaders(modelPath, vsPath, fsPath);
}

void MainWindow::onClickLoadModel()
{
    QStringList modelFiles = LXY::OpenFileChooser(tr("选择模型文件"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.off *.obj)"), false);
    for (auto filePath : modelFiles) {
        setTitle(filePath);
        string modelPath = filePath.toStdString();
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

void MainWindow::onClickTestMatrix()
{
    Matrix4D mat4;
    //ifstream fin("./testInMat4.mat4");
    //fin >> mat4;
    std::istringstream strin("1 2 3 4\n"
                             "0 5 6 7\n"
                             "8 9 10 11\n"
                             "12 13 14 15\n");
    strin >> mat4;
    ofstream fout("./testOutMat4.mat4");
    fout << mat4;
    cout << mat4;
    //fin.close();
    fout.close();
}


void MainWindow::onLoadViewMatrix()
{
    QStringList modelFiles = LXY::OpenFileChooser(tr("选择view matrix文件"), tr("../RealTimeRenderingDemo/DefaultModels"), tr("(*.viewMatrix)"), false);
    for (auto filePath : modelFiles) {
        this->glWidget->loadViewMatrix(filePath.toStdString());
    }
}

void MainWindow::onSaveViewMatrix()
{
    this->glWidget->saveViewMatrix();
}

void MainWindow::setTitle(QString title)
{
    title = "RealtmeRenderintDemo: " + title.split("/").last();
    setWindowTitle(title);
}
