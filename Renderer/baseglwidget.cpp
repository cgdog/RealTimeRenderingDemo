#include "baseglwidget.h"
#include "Utilities/helperFuncs.h"

using namespace LXY;

BaseGLWidget::BaseGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    m_vbo(nullptr), m_vao(nullptr), m_ebo(nullptr), m_shader(nullptr), clearColor(Qt::black)
{
    setFocusPolicy(Qt::StrongFocus);
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

void BaseGLWidget::changeModel(const string& modelPath, bool isUpdateGL)
{
    if (modelPath.empty())
    {
        return;
    }
    model.loadModel(modelPath);
    auto &vertices = model.getVertices();
    auto &indices = model.getIndices();
    if (nullptr == m_vao)
    {
        m_vao = new QOpenGLVertexArrayObject();
    }

    if (nullptr == m_vbo)
    {
        m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    } else if (m_vbo->isCreated()) {
        m_vbo->destroy();
    }

    if (nullptr == m_ebo)
    {
        m_ebo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    } else if (m_ebo->isCreated()) {
        m_ebo->destroy();
    }

    if (!m_vao->isCreated())
    {
        m_vao->create();
    }

    m_vao->bind();
    if (!m_vbo->isCreated())
    {
        m_vbo->create();
    }
    m_vbo->bind();
    m_vbo->allocate(&vertices[0], static_cast<int>(vertices.size() * sizeof(GLfloat)));

    if (!m_ebo->isCreated())
    {
        m_ebo->create();
    }
    m_ebo->bind();
    m_ebo->allocate(&indices[0], static_cast<int>(indices.size() * sizeof(GLint)));

    QOpenGLFunctions *f = this->context()->functions();

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_vbo->release();
    m_ebo->release();
    m_vao->release();
    if (isUpdateGL)
    {
        update();
    }
}

void BaseGLWidget::changeShaders(const QString& vsPath, const QString& fsPath, bool isUpdateGL)
{
    if (nullptr == m_shader)
    {
        m_shader = new Shader();
    }
    m_shader->loadShaderByPath(vsPath, fsPath);
    if (isUpdateGL)
    {
        update();
    }
}

void BaseGLWidget::changeModelAndShaders(const string& modelPath, const QString& vsPath, const QString& fsPath, bool isUpdateGL)
{
    changeModel(modelPath, false);
    changeShaders(vsPath, fsPath, false);
    if (isUpdateGL)
    {
        update();
    }
}
