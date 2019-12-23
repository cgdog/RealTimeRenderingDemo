#ifndef MODELPARSER_H
#define MODELPARSER_H
#include "helperFuncs.h"

namespace LXY {
    void loadOFFModel(ifstream& fileIn, vector<float>& vertices, vector<int>& indices);
    void loadModel(string modelPath, vector<float>& vertices, vector<int>& indices);
    void loadDefaultModel(string modelPath, vector<float>& vertices, vector<int>& indices);
}
#endif // MODELPARSER_H
