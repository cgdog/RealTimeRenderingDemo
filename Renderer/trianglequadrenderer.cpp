#include "trianglequadrenderer.h"
#include <QScreen>

static const char* VERTEX_SHADER_CODE =
        "#version 330 \n"
        "layout(location = 0) in vec3 posVertex;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "  gl_Position = matrix * vec4(posVertex, 1.0f);\n"
        "}\n";

static const char* FRAGMENT_SHADER_CODE =
        "#version 330\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "  fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n";

TriangleQuadRenderer::TriangleQuadRenderer(QWidget *parent) :
    BaseGLWidget(parent), m_frame(0), xRot(0), yRot(0), zRot(0)
{
    //model.loadModel(":/quad.off", true);
    model.loadModel(":/default.off", true);
}

TriangleQuadRenderer::~TriangleQuadRenderer()
{

}

void TriangleQuadRenderer::initializeGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, VERTEX_SHADER_CODE);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, FRAGMENT_SHADER_CODE);
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    // 初始化VAO
    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vao->create();
    m_vao->bind();
    auto & vertices = model.getVertices();
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(&vertices[0], vertices.size()* sizeof(vertices[0]));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_vbo->release();
    m_vao->release();
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
    m_shader->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.scale(0.5f, 0.5f, 0.5f);
    //matrix.translate(0, 0, -2);
    //auto fr = screen()->refreshRate();
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(rotationFactor * xRot, 0, 1, -2);
    matrix.rotate(rotationFactor * yRot, 1, 0, -2);
    int matrixUniformLoc = m_shader->uniformLocation("matrix");
    m_shader->setUniformValue(matrixUniformLoc, matrix);

    f->glDrawArrays(GL_TRIANGLES, 0, model.getVertices().size());
    //f->glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, &(model.getIndices()[0]));
    m_shader->release();
    m_vao->release();
    ++m_frame;
    this->context()->swapBuffers(this->context()->surface());
}

void TriangleQuadRenderer::mousePressEvent(QMouseEvent* event) {
   //lastPos = event->pos();
}

void TriangleQuadRenderer::mouseMoveEvent(QMouseEvent *event) {
//    QPoint curPos = event->pos();
//    QPoint deltPos = lastPos - curPos;
//    xRot += deltPos.x();
//    yRot += deltPos.y();
//    update();
}

void TriangleQuadRenderer::mouseReleaseEvent(QMouseEvent *event) {

}

void TriangleQuadRenderer::mouseDoubleClickEvent(QMouseEvent *event) {

}
