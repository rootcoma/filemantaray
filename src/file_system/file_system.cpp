#include "file_system.h"
#include <SDL.h>

std::string FileSystem::GetCurrentPath()
{
    TeenyPath::path cwd = TeenyPath::path(SDL_GetBasePath());
    return cwd.string();
}

std::vector<std::string> FileSystem::GetDrives()
{
    m_roots.clear();
#ifdef _WIN32
    std::vector<std::string> drives;
    char checkStr[] = "A:\\";
    for (int c = 'A'; c <= 'Z'; c++) {
        checkStr[0] = (char)c;
        TeenyPath::path checkDrive = TeenyPath::path(checkStr);
        if (!checkDrive.exists()) {
            continue;
        }
        m_roots.push_back(checkDrive);
        drives.push_back(checkStr);
    }
    return drives;
#else
    std::vector<std::string> ret = {"/"};
    m_roots.push_back("/");
    return ret;
#endif
}

std::vector<std::string> FileSystem::ls(const std::string &path)
{
    const TeenyPath::path currPath = TeenyPath::path(path);
    const std::vector<TeenyPath::path> paths = TeenyPath::ls(currPath);
    std::vector<std::string> pathNames;
    for (auto &p : paths) {
        pathNames.push_back(p.string());
    }
    return pathNames;
}
