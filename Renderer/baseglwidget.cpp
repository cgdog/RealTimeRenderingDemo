#include "baseglwidget.h"
#include "Utilities/helperFuncs.h"

using namespace LXY;

BaseGLWidget::BaseGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    vbo(nullptr), vao(nullptr), ebo(nullptr), m_shader(nullptr),
    clearColor(0.0f, 0.0f, 0.0f, 1.0f), xRot(0), yRot(0), zRot(0), lightNum(1)
{
    setFocusPolicy(Qt::StrongFocus);
    lights = new Light[static_cast<size_t>(lightNum)];
}

BaseGLWidget::BaseGLWidget(int _lightNum, Vector4 _clearColor, QWidget *parent) : QOpenGLWidget(parent),
    vbo(nullptr), vao(nullptr), ebo(nullptr), m_shader(nullptr),
    clearColor(_clearColor), xRot(0), yRot(0), zRot(0), lightNum(_lightNum)
{
    setFocusPolicy(Qt::StrongFocus);
    lights = new Light[static_cast<size_t>(lightNum)];
}

BaseGLWidget::~BaseGLWidget()
{
    if (nullptr != vao)
    {
        delete vao;
    }

    if (nullptr != vbo)
    {
        delete vbo;
    }

    if (nullptr != ebo)
    {
        delete ebo;
    }

    if (nullptr != m_shader)
    {
        delete m_shader;
    }

    if (nullptr != lights)
    {
        delete [] lights;
    }

}

int BaseGLWidget::getLightNum()
{
    return lightNum;
}

void BaseGLWidget::initializeGL()
{
    changeModelAndShaders(":/default.off", QString(":/default.vs"), QString(":/default.fs"), false);
    //changeModelAndShaders(":/quad.off", QString(":/quad.vs"), QString(":/quad.fs"), false);
    //changeModelAndShaders(":/triangle.off", QString(":/triangle.vs"), QString(":/triangle.fs"), false);
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

    QOpenGLFunctions *glFuncs = this->context()->functions();
    glFuncs->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFuncs->glClearColor(clearColor.X(), clearColor.Y(), clearColor.Z(), clearColor.W());

    glFuncs->glEnable(GL_DEPTH_TEST);
    //glFuncs->glEnable(GL_CULL_FACE);
    //glFuncs->glCullFace(GL_BACK);
    //glFuncs->glCullFace(GL_FRONT);
    // https://learnopengl.com/Advanced-OpenGL/Face-culling
    // 注意face culling是相对于你的视点(相机的)。现在camera默认位置是(0, 0, -3), 看向(0, 0, 0)处。
    // 所以，项目中的DefaultModels目录下的几个默认模型(.off文件)相对于此时的相机是顺时针缠绕(clock-wise winding)，即OpenGL中的back face。

    vao->bind();
    ebo->bind();
    m_shader->bind();

    Matrix4D viewMatrix = camera.lookAt();
    //Matrix4D projection = camera.getPerspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    Matrix4D projection = camera.getPerspective(4.0f/3.0f, 0.1f, 100.0f);
    //Matrix4D rotationX = camera.getTransform().rotate(rotationFactor * xRot, 0, 1, 0);
    //Matrix4D rotationY = camera.getTransform().rotate(rotationFactor * yRot, 1, 0, 0);
    Matrix4D translation = model.getTransform().translate(0, 0, -2);
    //Matrix4D tmpMatrix = projection * translation * rotationY * rotationX;
    //Matrix4D tmpMatrix = projection * viewMatrix * translation * rotationY * rotationX;
    //Matrix4D tmpMatrix = projection * translation;
    Matrix4D tmpMatrix = projection * viewMatrix * translation;
    int matrixUniformLoc = m_shader->getUniformLocation("matrix");
    // The matrices in OpenGL are column-major. Note: the LXY::Matrix4D implemented here is row-major matrix.
    // So I set the third parameter to GL_TRUE.
    glFuncs->glUniformMatrix4fv(matrixUniformLoc, 1, GL_TRUE, tmpMatrix.getData());

    GLsizei numFaceIndices = static_cast<GLsizei>(model.getIndices().size());
    glFuncs->glDrawElements(GL_TRIANGLES, numFaceIndices, GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    ebo->release();
    vao->release();

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

void BaseGLWidget::setClearColor(const Vector4 &color)
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
    if (nullptr == vao)
    {
        vao = new QOpenGLVertexArrayObject();
    }

    if (nullptr == vbo)
    {
        vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    } else if (vbo->isCreated()) {
        //m_vbo->destroy();
    }

    if (nullptr == ebo)
    {
        ebo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    } else if (ebo->isCreated()) {
        //m_ebo->destroy();
    }

    if (!vao->isCreated())
    {
        vao->create();
    }

    vao->bind();
    if (!vbo->isCreated())
    {
        vbo->create();
    }
    vbo->bind();
    vbo->allocate(&vertices[0], static_cast<int>(vertices.size() * sizeof(GLfloat)));

    if (!ebo->isCreated())
    {
        ebo->create();
    }
    ebo->bind();
    ebo->allocate(&indices[0], static_cast<int>(indices.size() * sizeof(GLint)));

    QOpenGLFunctions *f = this->context()->functions();

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    vbo->release();
    ebo->release();
    vao->release();

    loadViewMatrixByModelPath(modelPath);
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

void BaseGLWidget::loadViewMatrixByModelPath(const string& modelPath)
{
    size_t pos = modelPath.find(".off");
    if (string::npos == pos)
    {
        pos = modelPath.find(".obj");
    }
    string viewMatrixPath = modelPath.substr(0, pos);
    viewMatrixPath += ".viewMatrix";
    if (isStartsWith(viewMatrixPath, ":/"))
    {
        //viewMatrixPath[0] = '.';
        return;
    }
    loadViewMatrix(viewMatrixPath);
}

void BaseGLWidget::loadViewMatrix(const string& path)
{
    ifstream fin(path);
    if (!fin.good())
    {
        //logErr() << "Error: " << path << " is not a good view matrix file path." << endl;
        return;
    }
    string line;
    int flag = 0;
    while (getline(fin, line))
    {
        if ('#' == line[0])
        {
            continue;
        }
        stringstream ss(line);
        Vector3 v3;
        float eulerAngle(0.0f);
        if (flag >= 0 && flag < 3)
        {
            ss >> v3.X() >> v3.Y() >> v3.Z();
        }
        else
        {
            ss >> eulerAngle;
        }
        switch (flag)
        {
        case 0:
            camera.setPos(v3);
            break;
        case 1:
            camera.setWorldUp(v3);
            break;
        case 2:
            camera.setCameraDirection(v3);
            break;
        case 3:
            camera.setYaw(eulerAngle);
            break;
        case 4:
            camera.setPitch(eulerAngle);
            break;
        }

        ++flag;
    }
    fin.close();
    update();
}

void BaseGLWidget::saveViewMatrix()
{

    string modelPath = model.getModelPath();
    size_t pos = modelPath.find(".off");
    if (string::npos == pos)
    {
        pos = modelPath.find(".obj");
    }
    string viewMatrixPath = modelPath.substr(0, pos);
    viewMatrixPath += ".viewMatrix";
    if (isStartsWith(viewMatrixPath, ":/"))
    {
        viewMatrixPath[0] = '.';
    }

    ofstream fout(viewMatrixPath);
    fout << "# camera view matrix parameters: "
            "cameraPos, cameraWorldUp, cameraDirection, yaw, pitch." << endl;
    auto cameraPos = camera.getPos();
    fout << cameraPos.X() << " " << cameraPos.Y() << " " << cameraPos.Z() << endl;
    auto cameraWorldUp = camera.getWorldUp();
    fout << cameraWorldUp.X() << " " << cameraWorldUp.Y() << " " << cameraWorldUp.Z() << endl;
    auto cameraDirection = camera.getCameraDirection();
    fout << cameraDirection.X() << " " << cameraDirection.Y() << " " << cameraDirection.Z() << endl;
    float yaw = camera.getYaw();
    float pitch = camera.getPitch();
    fout << yaw << endl;
    fout << pitch << endl;
    fout.close();
}
