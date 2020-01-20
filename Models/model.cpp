#include "model.h"
#include "Utilities/modelParser.h"

namespace LXY
{

Model::Model() : isAltKeyDown(false), isLeftMouseButtonDown(false), mouseSensitivity(0.3f)
{
}


Model::Model(const string& _modelPath) : isAltKeyDown(false), isLeftMouseButtonDown(false), mouseSensitivity(0.1f)
{
    log() << _modelPath << endl;
    loadModel(_modelPath);
}

Model::~Model()
{
}

void Model::loadModel(const string& _modelPath, bool isDefaultModel)
{
    if (_modelPath.empty())
    {
        logErr()<< "error: modelPath is empty." << endl;
        return;
    }

    this->modelPath = _modelPath;

    vertices.clear();
    indices.clear();
    vNormals.clear();
    if (isDefaultModel || isStartsWith(_modelPath, ":/"))
    {
        LXY::loadDefaultModel(_modelPath, vertices, indices, vNormals);
    }
    else if (!isDefaultModel)
    {
        LXY::loadModel(_modelPath, vertices, indices, vNormals);
    }
}

void Model::cleanModel()
{
}

vector<float>& Model::getVertices()
{
    return vertices;
}

bool Model::hasNormals()
{
    return !vNormals.empty();
}

vector<float> Model::getVertexAttributes()
{
    if (vNormals.empty()) return vertices;

    vector<float> vertexAttributes(vertices.size()+vNormals.size());
    size_t count = 0;
    for (size_t i = 0; i < vertexAttributes.size(); i += 6)
    {
        vertexAttributes[i] = vertices[count];
        vertexAttributes[i+1] = vertices[count + 1];
        vertexAttributes[i+2] = vertices[count + 2];

        vertexAttributes[i+3] = vNormals[count];
        vertexAttributes[i+4] = vNormals[count+1];
        vertexAttributes[i+5] = vNormals[count+2];
        count += 3;
    }
    return vertexAttributes;
}

vector<int>& Model::getIndices()
{
    return indices;
}

vector<float>& Model::getVertexNormals()
{
    return vNormals;
}


Transform& Model::getTransform()
{
    return transform;
}

string Model::getModelPath()
{
    return this->modelPath;
}

void Model::processALTKey(bool altFlag)
{
    isAltKeyDown = altFlag;
}

void Model::processMouseMove(float x, float y)
{
    if (isLeftMouseButtonDown && isAltKeyDown)
    {
        float xOffset = x - lastX;
        float yOffset = y - lastY;
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;
        transform.rotateZ(yOffset);
        transform.rotateY(xOffset);
        lastX = x;
        lastY = y;
    }
}

void Model::updateMouseLeftButtonDown(bool isDown, float x, float y)
{
    isLeftMouseButtonDown = isDown;
    if (isDown)
    {
        lastX = x;
        lastY = y;
    }
}

}
