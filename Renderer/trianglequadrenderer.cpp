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
    _time.start();
    lastTime = 0;
}

void TriangleQuadRenderer::resizeGL( int width, int height )
{
//    int side = qMin(width, height);
//    glViewport((width - side)/2, (height - side) / 2, side, side);

    Q_UNUSED(width)
    Q_UNUSED(height)
}

/*
void TriangleQuadRenderer::paintGL()
{    
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model.getIndices().size()), GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    m_ebo->release();
    m_vao->release();

    ++m_frame;
    this->context()->swapBuffers(this->context()->surface());
}
*/


///*
void TriangleQuadRenderer::paintGL()
{
    int curTime = _time.elapsed();
    int deltaTime = curTime - lastTime;
    lastTime = curTime;

    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    //matrix.rotate(rotationFactor * yRot, 1, 0, 0);
    //int matrixUniformLoc = m_shader->uniformLocation("matrix");
    //int matrixUniformLoc = m_shader->getUniformLocation("matrix");
    //m_shader->setUniformValue(matrixUniformLoc, matrix);

    //m_shader->setMat4("matrix", matrix);
    const float radius = 2;
    float camX = radius * static_cast<float>(cos(deltaTime));
    float camZ = radius * static_cast<float>(sin(deltaTime));
    Matrix4D viewMatrix = camera.lookAt(Vector3(camX, 0, camZ));

    //Matrix4D viewMatrix = camera.lookAt();
    Matrix4D projection = camera.getPerspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    Matrix4D rotationX = camera.getTransform().rotate(rotationFactor * xRot, 0, 1, 0);
    Matrix4D rotationY = camera.getTransform().rotate(rotationFactor * yRot, 1, 0, 0);
    Matrix4D translation = camera.getTransform().translate(0, 0, -2);
    //Matrix4D tmpMatrix = projection * translation * rotationY * rotationX;
    //Matrix4D tmpMatrix = projection * translation;
    Matrix4D tmpMatrix = projection * viewMatrix * translation;
    int matrixUniformLoc = m_shader->getUniformLocation("matrix");
    // 关于行优先存储、列优先存储。OpenGL函数需要列优先存储的数据
    // https://blog.csdn.net/baiyu9821179/article/details/74852984
    f->glUniformMatrix4fv(matrixUniformLoc, 1, GL_TRUE, tmpMatrix.getData());

    //f->glDrawArrays(GL_TRIANGLES, 0, model.getVertices().size());
    //f->glDrawArrays(GL_TRIANGLES, 0, 3);
    f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model.getIndices().size()), GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    m_ebo->release();
    m_vao->release();

    ++m_frame;
    this->context()->swapBuffers(this->context()->surface());
}
//*/

void TriangleQuadRenderer::mousePressEvent(QMouseEvent* event) {
   lastPos = event->pos();
}

void TriangleQuadRenderer::mouseMoveEvent(QMouseEvent *event) {
    QPoint curPos = event->pos();
    QPoint deltPos = lastPos - curPos;
    xRot -= deltPos.x();
    yRot -= deltPos.y();
    update();
}

void TriangleQuadRenderer::mouseReleaseEvent(QMouseEvent *event)
{
}

void TriangleQuadRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
}

