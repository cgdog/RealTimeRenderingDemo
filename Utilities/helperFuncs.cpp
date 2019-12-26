#include "helperFuncs.h"
#include <ctype.h>

namespace LXY{

    QStringList OpenFileChooser(const QString &caption, const QString &directory, const QString &filter, bool canMultiFile)
    {
        QFileDialog *fileDialog = new QFileDialog(nullptr, caption, directory, filter);

        if (canMultiFile)
        {
            fileDialog->setFileMode(QFileDialog::ExistingFiles);
        }
        else
        {
            fileDialog->setFileMode(QFileDialog::ExistingFile);
        }
        fileDialog->setViewMode(QFileDialog::Detail);

        QStringList fileNames;
        if(fileDialog->exec())
        {
            fileNames = fileDialog->selectedFiles();
        }
        return fileNames;
    }


   string readFileToString2(const QString& path)
   {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return nullptr;
        }
        QByteArray data = file.readAll();
        string source = data.toStdString();
        return source;
    }

   string loadDefaultVertexShader()
   {
       return readFileToString2(":/default.vs");
   }

   string loadDefaultFragmentShader()
   {
       return readFileToString2(":/default.fs");
   }

   string readFileToString(const QString& path)
   {
        std::string filePath = path.toStdString();
        std::ifstream fileIn(filePath);
        if (fileIn.bad())
        {
           std::cerr << "open file " << filePath << "failed" << std::endl;
        }

        std::stringstream ss;
        ss << fileIn.rdbuf();
        string source = ss.str();

        fileIn.close();
        return source;
    }

    std::ostream& logErr()
    {
        return std::cerr;
    }

    std::ostream& log()
    {
        return std::cout;
    }

    bool isEndsWith(const string & source, const string & pattern)
    {
        if (source.length() >= pattern.length())
        {
            return (0 == source.compare (source.length() - pattern.length(), pattern.length(), pattern));
        }
        else
        {
            return false;
        }
    }

    bool isStartsWith(const string & source, const string & pattern)
    {
        if (source.length() >= pattern.length())
        {
            return (0 == source.compare (0, pattern.length(), pattern));
        }
        else
        {
            return false;
        }
    }

    // http://www.cplusplus.com/reference/iterator/istreambuf_iterator/
    // https://stackoverflow.com/questions/4064601/copy-data-from-fstream-to-stringstream-with-no-buffer
    void ifstream2ostringstream(ifstream& fin, ostringstream& sout)
    {
        copy(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(sout));
        //string ms = sout.str();
        //cout << ms << endl;
    }

}
