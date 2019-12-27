#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "Math/transform.h"

using namespace LXY;
using namespace std;

namespace LXY {

class Model
{
public:
    Model();
    Model(const string& modelPath);
    ~Model();

    void loadModel(string modelPath,  bool isDefaultModel = false);

    vector<float>& getVertices();
    vector<int>& getIndices();

    Transform& getTransform();

protected:
    void cleanModel();

protected:

    vector<float> vertices;
    vector<int> indices;

    Transform transform;
};

}
#endif // MODEL_H
