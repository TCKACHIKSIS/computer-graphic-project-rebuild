#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>
#include <vector>
#include "canalofsignal/canalofsignal.h"
#include "filehandler/dataStructure.h"
class FileHandler
{
private:
    std::ifstream file;
public:
    dataStructure getData();
    void openFile(const std::string& path);
    bool isFileOpen();
    void readDataField(int &field);
    void readDataField(double &field);
    void readDataField(std::string &field);
    void readDataField(std::vector<std::string> &field);
    void readDataField(std::vector<CanalOfSignal> &field, const std::vector<std::string> &names);
};

#endif // FILEHANDLER_H
