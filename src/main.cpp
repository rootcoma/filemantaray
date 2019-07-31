#include "base/log.h"
#include "gui.h"
#include "file_system/file_system.h"

void Init()
{
    GUIInit();
}

int main(int argc, char** argv)
{
    Success("Hello World!");
    Init();
    FileSystem fs;
    std::string path = fs.GetCurrentPath();
    Success("currentpath: %s-----", path.c_str());
    std::vector<std::string> dirContents;
    dirContents = fs.GetDrives();
    Info("Contents");
    for (auto &n : dirContents) {
        Info("->%s", n.c_str());
    }
    GUILoop(fs);
    Success("Bye!");
    GUICleanup(); // closes win and exits
}