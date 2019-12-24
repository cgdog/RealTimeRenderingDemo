#include "trianglequadrenderer.h"
#include <QScreen>
#include "Utilities/helperFuncs.h"
using namespace LXY;

TriangleQuadRenderer::TriangleQuadRenderer(QWidget *parent) :
    BaseGLWidget(parent), m_frame(0), xRot(0), yRot(0), zRot(0)
{
}

TriangleQuadRenderer::~TriangleQuadRenderer()
{
}

void TriangleQuadRenderer::initializeGL()
{
    changeModelAndShaders(":/default.off", QString(":/default.vs"), QString(":/default.fs"), false);
}

void TriangleQuadRenderer::resizeGL( int width, int height )
{
//    int side = qMin(width, height);
//    glViewport((width - side)/2, (height - side) / 2, side, side);

    Q_UNUSED(width)
    Q_UNUSED(height)
}

void TriangleQuadRenderer::paintGL()
{    
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
    m_vao->bind();
    m_ebo->bind();
    m_shader->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.scale(0.5f, 0.5f, 0.5f);
    matrix.translate(0, 0, -2); //注意这里，如果设为matrix.translate(0, 0, 0)会看不到某些模型
    //auto fr = screen()->refreshRate();
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(rotationFactor * xRot, 0, 1, 0);
    matrix.rotate(rotationFactor * yRot, 1, 0, 0);
    //int matrixUniformLoc = m_shader->uniformLocation("matrix");
    //int matrixUniformLoc = m_shader->getUniformLocation("matrix");
    //m_shader->setUniformValue(matrixUniformLoc, matrix);
    m_shader->setMat4("matrix", matrix);

    //f->glDrawArrays(GL_TRIANGLES, 0, model.getVertices().size());
    //f->glDrawArrays(GL_TRIANGLES, 0, 3);
    f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model.getIndices().size()), GL_UNSIGNED_INT, 0);
    m_shader->release();
    m_ebo->release();
    m_vao->release();

    ++m_frame;
    this->context()->swapBuffers(this->context()->surface());
}

void TriangleQuadRenderer::mousePressEvent(QMouseEvent* event) {
   lastPos = event->pos();
}

void TriangleQuadRenderer::mouseMoveEvent(QMouseEvent *event) {
    QPoint curPos = event->pos();
    QPoint deltPos = lastPos - curPos;
    xRot += deltPos.x();
    yRot += deltPos.y();
    update();
}

void TriangleQuadRenderer::mouseReleaseEvent(QMouseEvent *event)
{
}

void TriangleQuadRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void TriangleQuadRenderer::changeModel(const string& modelPath, bool isUpdateGL)
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
//    else if (m_vao->isCreated()) {
//        m_vao->destroy();
//    }

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

void TriangleQuadRenderer::changeShaders(const QString& vsPath, const QString& fsPath, bool isUpdateGL)
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

void TriangleQuadRenderer::changeModelAndShaders(const string& modelPath, const QString& vsPath, const QString& fsPath, bool isUpdateGL)
{
    changeModel(modelPath, false);
    changeShaders(vsPath, fsPath, false);
    if (isUpdateGL)
    {
        update();
    }
}
