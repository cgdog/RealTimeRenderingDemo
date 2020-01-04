#ifndef TRIANGLEQUADRENDERER_H
#define TRIANGLEQUADRENDERER_H

#include "baseglwidget.h"
#include <QKeyEvent>

class TriangleQuadRenderer : public BaseGLWidget
{
public:
    TriangleQuadRenderer(QWidget *parent=nullptr);
    ~TriangleQuadRenderer() override;
protected:
    void initializeGL() override;
    void resizeGL( int width, int height ) override;
    void paintGL() override;
};

#endif // TRIANGLEQUADRENDERER_H
