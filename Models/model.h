#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
using namespace std;

class Model
{
public:
    Model();
    Model(const string& modelPath);
    ~Model();

    void loadModel(string modelPath,  bool isDefaultModel = false);

    vector<float>& getVertices();
    vector<int>& getIndices();

protected:
    void cleanModel();

protected:

    vector<float> vertices;
    vector<int> indices;
};

#endif // MODEL_H
