#include <Windows.h>
#include <string>
#include <chrono>

class Loader {
public:

    Loader(LPCWSTR LDisk, std::string sDisk);
    void LoadDisk();

    struct DiskInfo {
        LPCWSTR LpcwName = NULL;
        std::string StrName = "";
        double AllMem,
            FreeMem;
    };

    DiskInfo GetDriveInfo(LPCWSTR Dsik);

private:
    int ChooseReportInterval();
    int CountRemaningTime(std::chrono::duration<double> ElapsedSeconds);

    void StartTime();
    void EndTime();
    std::chrono::duration<double> SpendTime();


    std::chrono::system_clock::time_point StartTimePtr;
    std::chrono::system_clock::time_point EndTimePtr;

    DiskInfo CurrentDisk;
    int FileSize;

};