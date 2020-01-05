#include "baseglwidget.h"
#include "Utilities/helperFuncs.h"

using namespace LXY;

BaseGLWidget::BaseGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    m_vbo(nullptr), m_vao(nullptr), m_ebo(nullptr), m_shader(nullptr),
    clearColor(Qt::black), xRot(0), yRot(0), zRot(0)
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

void BaseGLWidget::initializeGL()
{
    //changeModelAndShaders(":/default.off", QString(":/default.vs"), QString(":/default.fs"), false);
    //changeModelAndShaders(":/quad.off", QString(":/quad.vs"), QString(":/quad.fs"), false);
    changeModelAndShaders(":/triangle.off", QString(":/triangle.vs"), QString(":/triangle.fs"), false);
    //changeModelAndShaders(":/horse-gallop-01.obj", QString(":/horse-gallop-01.vs"), QString(":/horse-gallop-01.fs"), false);
    timeManaer.initialize();
    lastTime = 0;
}

void BaseGLWidget::paintGL()
{
    int curTime = timeManaer.getTime();
    deltaTime = curTime - lastTime;
    //log() << "--deltaTime=" << deltaTime << endl;
    lastTime = curTime;

    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    f->glEnable(GL_DEPTH_TEST);
    //f->glEnable(GL_CULL_FACE);

    m_vao->bind();
    m_ebo->bind();
    m_shader->bind();


    Matrix4D viewMatrix = camera.lookAt();
    //Matrix4D projection = camera.getPerspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    Matrix4D projection = camera.getPerspective(4.0f/3.0f, 0.1f, 100.0f);
    //Matrix4D rotationX = camera.getTransform().rotate(rotationFactor * xRot, 0, 1, 0);
    //Matrix4D rotationY = camera.getTransform().rotate(rotationFactor * yRot, 1, 0, 0);
    Matrix4D translation = camera.getTransform().translate(0, 0, -2);
    //Matrix4D tmpMatrix = projection * translation * rotationY * rotationX;
    //Matrix4D tmpMatrix = projection * viewMatrix * translation * rotationY * rotationX;
    //Matrix4D tmpMatrix = projection * translation;
    Matrix4D tmpMatrix = projection * viewMatrix * translation;
    int matrixUniformLoc = m_shader->getUniformLocation("matrix");
    // The matrices in OpenGL are column-major. Note: the LXY::Matrix4D implemented here is row-major matrix.
    // So I set the third parameter to GL_TRUE.
    f->glUniformMatrix4fv(matrixUniformLoc, 1, GL_TRUE, tmpMatrix.getData());

    GLsizei numFaceIndices = static_cast<GLsizei>(model.getIndices().size());
    f->glDrawElements(GL_TRIANGLES, numFaceIndices, GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    m_ebo->release();
    m_vao->release();

    this->context()->swapBuffers(this->context()->surface());
}

void BaseGLWidget::resizeGL( int width, int height )
{
//    int side = qMin(width, height);
//    glViewport((width - side)/2, (height - side) / 2, side, side);

    Q_UNUSED(width)
    Q_UNUSED(height)
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

void BaseGLWidget::mousePressEvent(QMouseEvent* event)
{
   camera.updateMouseLeftButtonDown(true, event->x(), event->y());
}

void BaseGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    camera.processMouseMove(event->x(), event->y());
    update();
}

void BaseGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    camera.updateMouseLeftButtonDown(false, event->x(), event->y());
}

void BaseGLWidget::wheelEvent(QWheelEvent* event)
{
    auto delta = event->angleDelta();
    if (delta.isNull())
    {
        delta = event->pixelDelta();
    }
    camera.processMouseScroll(delta.y());
    update();
}

void BaseGLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void BaseGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
    {
        camera.processKeyboard(Direction::UP, deltaTime);
    }
    else if (event->key() == Qt::Key_S)
    {
        camera.processKeyboard(Direction::DOWN, deltaTime);
    }
    else if (event->key() == Qt::Key_A)
    {
        camera.processKeyboard(Direction::LEFT, deltaTime);
    }
    else if (event->key() == Qt::Key_D)
    {
        camera.processKeyboard(Direction::RIGHT, deltaTime);
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
    update();
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
        //m_vbo->destroy();
    }

    if (nullptr == m_ebo)
    {
        m_ebo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    } else if (m_ebo->isCreated()) {
        //m_ebo->destroy();
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
