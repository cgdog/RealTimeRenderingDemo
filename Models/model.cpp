#include "model.h"
#include "Utilities/modelParser.h"

namespace LXY
{

Model::Model()
{
}


Model::Model(const string& _modelPath)
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

}
