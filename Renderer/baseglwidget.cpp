#include "baseglwidget.h"
#include "Utilities/helperFuncs.h"

using namespace LXY;

BaseGLWidget::BaseGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    m_vbo(nullptr), m_vao(nullptr), m_ebo(nullptr), m_shader(nullptr), clearColor(Qt::black)
{

}

BaseGLWidget::~BaseGLWidget()
{
    if (nullptr != m_vao)
    {
        delete m_vao;
    }

    if (nullptr != m_vbo)
    {
        delete m_vbo;
    }

    if (nullptr != m_ebo)
    {
        delete m_ebo;
    }

    if (nullptr != m_shader)
    {
        delete m_shader;
    }

}

QSize BaseGLWidget::minimumSizeHint() const
{
    return QSize(640, 480);
}

QSize BaseGLWidget::sizeHint() const
{
    return QSize(640, 480);
}

void BaseGLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    update();
}

void BaseGLWidget::mousePressEvent(QMouseEvent* event) {
    log() << "mousePressEvent: x=" << event->x() << " y=" << event->y() << endl;
}

void BaseGLWidget::mouseMoveEvent(QMouseEvent *event) {
    log() << "mouseMoveEvent: x=" << event->x() << " y=" << event->y() << endl;
}

void BaseGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    log() << "mouseReleaseEvent: x=" << event->x() << " y=" << event->y() << endl;
}

void BaseGLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    log() << "mouseDoubleClickEvent: x=" << event->x() << " y=" << event->y() << endl;
}

