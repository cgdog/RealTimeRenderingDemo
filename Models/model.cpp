#include "model.h"
#include "Utilities/modelParser.h"
using namespace LXY;

Model::Model(){
    //loadModel(":/default.off", true);
}


Model::Model(const string& modelPath) {
    log() << modelPath << endl;
    loadModel(modelPath);
}

Model::~Model() {
}

void Model::loadModel(string modelPath, bool isDefaultModel) {
    if (modelPath.empty()) {
        logErr()<< "error: modelPath is empty." << endl;
        return;
    }

    vertices.clear();
    indices.clear();
    if (!isDefaultModel) {
        LXY::loadModel(modelPath, vertices, indices);
    } else {
        LXY::loadDefaultModel(modelPath, vertices, indices);
    }
}

void Model::cleanModel() {
}

vector<float>& Model::getVertices() {
    return vertices;
}
vector<int>& Model::getIndices() {
    return indices;
}


