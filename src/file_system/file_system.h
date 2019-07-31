#ifndef FILEMANTARAY_FILE_SYSTEM_H_
#define FILEMANTARAY_FILE_SYSTEM_H_
#include <string>
#include <vector>
#include <teenypath.h>

class FileSystem
{
public:
    std::vector<std::string> ls(const std::string &path);

    std::vector<std::string> GetDrives();

    std::string GetCurrentPath();

    std::vector<TeenyPath::path> m_roots; // drives for windows or / for linux
};

#endif
