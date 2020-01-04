#include "trianglequadrenderer.h"
#include <QScreen>
#include "Utilities/helperFuncs.h"
using namespace LXY;

TriangleQuadRenderer::TriangleQuadRenderer(QWidget *parent) :
    BaseGLWidget(parent)
{
}

TriangleQuadRenderer::~TriangleQuadRenderer()
{
}

void TriangleQuadRenderer::initializeGL()
{
    BaseGLWidget::initializeGL();
}

void TriangleQuadRenderer::resizeGL( int width, int height )
{
    BaseGLWidget::resizeGL(width, height);
}

void TriangleQuadRenderer::paintGL()
{
    BaseGLWidget::paintGL();
}


