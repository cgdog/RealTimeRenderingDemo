#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "Renderer/trianglequadrenderer.h"
#include "Renderer/simplelightingrenderer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void processMenu();
    void setTitle(QString title);

private slots:
    void onClickLoadModelAndShaders();
    void onClickLoadModel();
    void onClickLoadShaders();

    void onLoadViewMatrix();
    void onSaveViewMatrix();

    // demos
    void onChange2LightDemo();
    void onChange2DefaultDemo();

    // tools

    void onClickObj2Off();

    // for test.
    void onClickTestMatrix();

private:
    BaseGLWidget* glWidget;
    QMenuBar* mb;
    QAction* defaultDemoAction;
    QAction* lightDemoAction;
};
#endif // MAINWINDOW_H
