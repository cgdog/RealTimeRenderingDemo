#ifndef TRIANGLEQUADRENDERER_H
#define TRIANGLEQUADRENDERER_H

#include "baseglwidget.h"

class TriangleQuadRenderer : public BaseGLWidget
{
public:
    TriangleQuadRenderer(QWidget *parent=0);
    ~TriangleQuadRenderer() override;
protected:
    void initializeGL() override;
    void resizeGL( int width, int height ) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    int m_frame;
    float rotationFactor = 0.01f;
    int xRot;
    int yRot;
    int zRot;
};

#endif // TRIANGLEQUADRENDERER_H
