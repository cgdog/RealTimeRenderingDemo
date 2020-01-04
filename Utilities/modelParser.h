#ifndef MODELPARSER_H
#define MODELPARSER_H
#include "helperFuncs.h"

namespace LXY {
    void loadOFFModel(ifstream& fileIn, vector<float>& vertices, vector<int>& indices);
    void loadOBJModel(const string& modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals);
    void loadModel(const string& modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals);
    void loadDefaultModel(const string&  modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals);
    void loadDefaultOFFModel(const string&  modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals);
    void loadDefaultOBJModel(const string&  modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals);
}
#endif // MODELPARSER_H
