#include "modelParser.h"

namespace LXY {

    void loadOFFModel(ifstream& fileIn, vector<float>& vertices, vector<int>& indices)
    {
        string line;
        int numV = -1;
        int numF = -1;
        int numE = -1;

        while (getline(fileIn, line))
        {
            if (line[0] == '#' || isspace(line[0]))
            {
                continue;
            }
            else if (line.compare("OFF")==0)
            {
                int curVNum = 0;
                int curFNum = 0;
                while (getline(fileIn, line))
                {
                    fileIn.clear();
                    if (line[0] == '#' || isspace(line[0]))
                    {
                        continue;
                    }
                    else if (-1 == numV)
                    {
                        std::stringstream ss(line);
                        ss >> numV >> numF >> numE;
                    }
                    else if (numV > curVNum)
                    {
                        curVNum += 1;
                        std::stringstream ss(line);
                        float x, y, z;
                        ss >> x >> y >> z;
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);
                    }
                    else if (numF > curFNum)
                    {
                        curFNum += 1;
                        int nf, v1, v2, v3; // 目前只支持三角形面片
                        std::stringstream ss(line);
                        ss >> nf >> v1 >> v2 >> v3;
                        indices.push_back(v1);
                        indices.push_back(v2);
                        indices.push_back(v3);
                    }
                    else
                    { // 暂时忽略边edges
                        fileIn.close();
                        return;
                    }
                }
            }
        }
        return;
    }

    void loadModel(const string& modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals)
    {
        if (isEndsWith(modelPath, ".off"))
        {
            ifstream fileIn(modelPath);
            if (fileIn.good())
            {
                loadOFFModel(fileIn, vertices, indices);
                fileIn.close();
            }
            else
            {
                logErr() << "The file " << modelPath << " is not good." << endl;
            }
        }
        else if (isEndsWith(modelPath, ".obj"))
        {
            loadOBJModel(modelPath, vertices, indices, vNormals);
        }
        else
        {
            logErr() << "Not support this file format now." << endl;
        }
    }

    void loadOBJModel(const string& modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals)
    {
        ifstream fileIn(modelPath);
        if (fileIn.good())
        {
            string line;

            while (getline(fileIn, line))
            {
                fileIn.clear();
                if (line[0] == '#' || isspace(line[0]))
                {
                    continue;
                }
                else if ('v' == line[0] && isspace(line[1]))
                {
                    std::stringstream ss(line);
                    string flag;
                    float x, y , z;
                    ss >> flag >> x >> y >> z;
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                }
                else if ('v' == line[0] && 'n' == line[1])
                {
                    std::stringstream ss(line);
                    string flag;
                    float x, y , z;
                    ss >> flag >> x >> y >> z;
                    vNormals.push_back(x);
                    vNormals.push_back(y);
                    vNormals.push_back(z);
                }
                else if ('f' == line[0])
                {
                    std::stringstream ss(line);
                    string flag;
                    string numStr[3];

                    ss >> flag >> numStr[0] >> numStr[1] >> numStr[2];
                    for (int i = 0; i < 3; ++i)
                    {
                        size_t pos = numStr[i].find('/');
                        if (pos != string::npos)
                        {
                            int face = atoi(numStr[i].substr(0, pos).c_str());
                            face -= 1;//obj indices stat with 1.
                            indices.push_back(face);
                        }
                        else
                        {
                            logErr() << "The obj file format is wrong when parsing face data.\n";
                        }
                    }
                }
            }
        }
        else
        {
            logErr() << "The file " << modelPath << " is not good." << endl;
        }
        log() << "load obj model, triangle size = " << vertices.size() / 3 << endl;
        log() << "load obj model, vertex normal size = " << vNormals.size() / 3 << endl;
        log() << "load obj model, faces size = " << indices.size() / 3 << endl;
    }

    void loadDefaultModel(const string&  modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals)
    {
        if (isEndsWith(modelPath, ".off"))
        {
            loadDefaultOFFModel(modelPath, vertices, indices, vNormals);
        }
        else if (isEndsWith(modelPath, ".obj"))
        {
            loadDefaultOBJModel(modelPath, vertices, indices, vNormals);
        }
    }

    void loadDefaultOBJModel(const string&  modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals)
    {
        QFile file(QString(modelPath.c_str()));

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            logErr() << "error: load default model: " << modelPath << endl;
            return;
        }

        while (!file.atEnd())
        {
            QByteArray bytes = file.readLine();
            const char * line= bytes.constData();

            if (line[0] == '#' || isspace(line[0]))
            {
                continue;
            }
            else if ('v' == line[0] && isspace(line[1]))
            {
                std::stringstream ss(line);
                string flag;
                float x, y , z;
                ss >> flag >> x >> y >> z;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
            else if ('v' == line[0] && 'n' == line[1])
            {
                std::stringstream ss(line);
                string flag;
                float x, y , z;
                ss >> flag >> x >> y >> z;
                vNormals.push_back(x);
                vNormals.push_back(y);
                vNormals.push_back(z);
            }
            else if ('f' == line[0])
            {
                std::stringstream ss(line);
                string flag;
                string numStr[3];

                ss >> flag >> numStr[0] >> numStr[1] >> numStr[2];
                for (int i = 0; i < 3; ++i)
                {
                    size_t pos = numStr[i].find('/');
                    if (pos != string::npos)
                    {
                        int face = atoi(numStr[i].substr(0, pos).c_str());
                        face -= 1;//obj indices stat with 1.
                        indices.push_back(face);
                    }
                    else
                    {
                        logErr() << "The obj file format is wrong when parsing face data.\n";
                    }
                }
            }
        }
    }

    void loadDefaultOFFModel(const string& modelPath, vector<float>& vertices, vector<int>& indices, vector<float>& vNormals)
    {
        Q_UNUSED(vNormals)
        QFile file(QString(modelPath.c_str()));

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            logErr() << "error: load default model: " << modelPath << endl;
            return;
        }

        int numV = -1;
        int numF = -1;
        int numE = -1;

        while (!file.atEnd())
        {
            QByteArray bytes = file.readLine();
            const char * line= bytes.constData();

            if (line[0] == '#' || isspace(line[0]))
            {
                continue;
            }
            else if (strcmp(line, "OFF\n")==0)
            {
                int curVNum = 0;
                int curFNum = 0;
                while (!file.atEnd())
                {
                    bytes = file.readLine();
                    const char * buffer = bytes.constData();
                    if (buffer[0] == '#' || isspace(buffer[0]))
                    {
                        continue;
                    }
                    else if (-1 == numV)
                    {
                        std::stringstream ss(buffer);
                        ss >> numV >> numF >> numE;
                    }
                    else if (numV > curVNum)
                    {
                        curVNum += 1;
                        std::stringstream ss(buffer);
                        float x, y, z;
                        ss >> x >> y >> z;
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);
                    }
                    else if (numF > curFNum)
                    {
                        curFNum += 1;
                        int nf, v1, v2, v3; // 目前只支持三角形面片
                        std::stringstream ss(buffer);
                        ss >> nf >> v1 >> v2 >> v3;
                        indices.push_back(v1);
                        indices.push_back(v2);
                        indices.push_back(v3);
                    }
                    else
                    { // 暂时忽略边edges

                    }
                }
            }

        }
        file.close();
        return;
    }
}
