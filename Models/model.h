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

    void loadModel(const string& modelPath,  bool isDefaultModel = false);

    vector<float>& getVertices();
    vector<float>& getVertexNormals();
    vector<float> getVertexAttributes();
    vector<int>& getIndices();

    bool hasNormals();

    Transform& getTransform();

    string getModelPath();

protected:
    void cleanModel();

protected:

    vector<float> vertices;
    vector<float> vNormals;
    vector<int> indices;

    Transform transform;

private:
    string modelPath;
};

}
#endif // MODEL_H
