#ifndef HELPFUNC_H
#define HELPFUNC_H
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QByteArray>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace LXY{

   #define PI 3.14159265f
   float Epsilon();

   bool isEqualZeroF(float f);

   QStringList OpenFileChooser(const QString &caption = QString(), const QString &directory = QString(), const QString &filter = QString(), bool canMultiFile = true);

   string readFileToString2(const QString& path);

    string readFileToString(const QString& path);

    string loadDefaultVertexShader();

    string loadDefaultFragmentShader();

    std::ostream& logErr();

    std::ostream& log();

    bool isEndsWith(const string & source, const string & pattern);
    bool isStartsWith(const string & source, const string & pattern);

    void ifstream2ostringstream(ifstream& fin, ostringstream& sout);

    float degreeToRadian(float degree);
    float radianToDegree(float radian);

}
#endif // HELPFUNC_H
