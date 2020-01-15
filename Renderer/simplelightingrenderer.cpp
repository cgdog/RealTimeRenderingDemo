#include "simplelightingrenderer.h"


SimpleLightingRenderer::SimpleLightingRenderer(QWidget *parent) :
    BaseGLWidget(parent)
{
}

SimpleLightingRenderer::~SimpleLightingRenderer()
{
}

void SimpleLightingRenderer::initializeGL()
{
    changeModelAndShaders(":/default.off", QString(":/default.vs"), QString(":/default.fs"), false);
}

void SimpleLightingRenderer::resizeGL( int width, int height )
{
    BaseGLWidget::resizeGL(width, height);
}

void SimpleLightingRenderer::paintGL()
{
    BaseGLWidget::paintGL();
}
