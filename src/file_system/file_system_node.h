#ifndef FILEMANTARAY_FILE_SYSTEM_FILE_SYSTEM_NODE_H
#define FILEMANTARAY_FILE_SYSTEM_FILE_SYSTEM_NODE_H

class FileSystemNode
{
public:

protected:
    FileSystemNode *parent = nullptr;
    uint64_t m_size = 0;
    std::string *m_name = "";
}

#endif FILEMANTARAY_FILE_SYSTEM_FILE_SYSTEM_NODE_H
