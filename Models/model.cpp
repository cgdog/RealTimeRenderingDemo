#include "model.h"
#include "Utilities/modelParser.h"

namespace LXY
{

Model::Model()
{
}


Model::Model(const string& modelPath)
{
    log() << modelPath << endl;
    loadModel(modelPath);
}

Model::~Model()
{
}

void Model::loadModel(const string& modelPath, bool isDefaultModel)
{
    if (modelPath.empty())
    {
        logErr()<< "error: modelPath is empty." << endl;
        return;
    }

    vertices.clear();
    indices.clear();
    vNormals.clear();
    if (isDefaultModel || isStartsWith(modelPath, ":/"))
    {
        LXY::loadDefaultModel(modelPath, vertices, indices);
    }
    else if (!isDefaultModel)
    {
        LXY::loadModel(modelPath, vertices, indices, vNormals);
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

}
