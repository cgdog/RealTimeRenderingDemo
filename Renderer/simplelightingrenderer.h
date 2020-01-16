#ifndef SIMPLELIGHTINGRENDERER_H
#define SIMPLELIGHTINGRENDERER_H

#include "baseglwidget.h"

using namespace LXY;

class SimpleLightingRenderer : public BaseGLWidget
{
public:
    SimpleLightingRenderer(QWidget *parent=nullptr);
    SimpleLightingRenderer(int _lightNum, Vector4 _clearColor=Vector4(0.0f, 0.0f, 0.0f, 1.0f), QWidget *parent=nullptr);
    ~SimpleLightingRenderer() override;
protected:
    void initializeGL() override;
    void resizeGL( int width, int height ) override;
    void paintGL() override;
};

#endif // SIMPLELIGHTINGRENDERER_H
