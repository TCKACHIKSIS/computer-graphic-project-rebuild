#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>
#include <vector>
#include "canalofsignal/canalofsignal.h"
#include "filehandler/dataStructure.h"
#include <QString>
class FileHandler
{
private:
    std::ifstream file;
    std::ofstream file_to_save;
public:
    dataStructure* getData();
    std::string name_of_current_file;
    void openFile(const QString &path);
    bool isFileOpen();
    void readDataField(int &field);
    void readDataField(double &field);
    void readDataField(std::string &field);
    void readDataField(std::vector<std::string> &field);
    void readDataField(std::vector<CanalOfSignal> &field, const std::vector<std::string> &names);
    void saveFile(dataStructure data_for_save, QString path);
};

#endif // FILEHANDLER_H
