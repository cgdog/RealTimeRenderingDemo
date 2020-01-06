#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "Renderer/trianglequadrenderer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void processMenu();

private slots:
    void onClickLoadModelAndShaders();
    void onClickLoadModel();
    void onClickLoadShaders();

    void onLoadViewMatrix();
    void onSaveViewMatrix();

    // for test.
    void onClickTestMatrix();

private:
    BaseGLWidget* glWidget;
    QMenuBar* mb;
};
#endif // MAINWINDOW_H
