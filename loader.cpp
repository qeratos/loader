#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <fstream>
#define MEGA_PTR 1048576

class Printer {
public:
    Printer(std::string Language, int TextColor);
    void SetCoords(int x, int y);
    COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

protected:
    COORD Coords = { 0, 0 };
    HANDLE hConsole = NULL;

};

Printer::Printer(std::string Language, int TextColor) {
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

}

COORD Printer::GetConsoleCursorPosition(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }else{
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void Printer::SetCoords(int x, int y){
    this->Coords.X = x;
    this->Coords.Y = y;
}


class PayloadGenerator : public Printer {
public:
    PayloadGenerator(std::string Language, int TextColor, std::string FileExt, int FileSize);
    
    std::string GetFileName();
    int MakeFile();


private:
    std::string FileName;
    std::ofstream ExitFile;
    int FileSize = 0;


};

PayloadGenerator::PayloadGenerator(std::string Language, int TextColor, std::string FileExt, int FileSize) : Printer(Language, TextColor){
    this->ExitFile.open("l1pz.bin", std::ios::out);
}

std::string PayloadGenerator::GetFileName() {
    
}

int PayloadGenerator::MakeFile() {
    this->FileSize *= MEGA_PTR;
    int proc = 0, prev = 0;
    if (ExitFile.is_open()) {
        for (long long i = 0; i < this->FileSize; i++) {
            ExitFile << (char)(rand() % (126 + 33 - 0) + 0);
            proc = (100 * i) / this->FileSize;
            if (proc != prev) {
                //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
                std::cout << proc;
            }
            prev = proc;
        }
    }
}

PayloadGenerator::~PayloadGenerator() {
    this->ExitFile.close();
}


class Loader {
public:

    Loader(LPCWSTR LDisk, std::string sDisk);


    struct DiskInfo {
        LPCWSTR LpcwName = NULL;
        std::string StrName = "";
        double AllMem,
            FreeMem;
    };

    DiskInfo GetDriveInfo(LPCWSTR Dsik);

private:
    std::chrono::system_clock::time_point StartTime();
    std::chrono::system_clock::time_point EndTime();
    std::chrono::system_clock::time_point SpendTime();
    DiskInfo CurrentDisk;
    
};

Loader::DiskInfo Loader::GetDriveInfo(LPCWSTR Disk) {
    ULARGE_INTEGER FreeBytesToCaller, TotalBytes, FreeBytes;
    GetDiskFreeSpaceEx(Disk, &FreeBytesToCaller, &TotalBytes, &FreeBytes);
    CurrentDisk.AllMem = TotalBytes.QuadPart / (1024 * 1024 * 1024);
    CurrentDisk.FreeMem = FreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
    return CurrentDisk;
}




//void prep_file(int file_size) {
//    COORD current_crd = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
//
//    cout << "Создание файла подкачки:    %" << endl;
//    
//    COORD coords = { 25, current_crd.Y };
//    
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
//    cout << 100 << endl;
//    out.close();
//
//}


void work(disk current, int file_size) {
    int ctr = 0, proc = 0, prev = 0, tim_ctr = 0, time_i = 100;

    if (file_size < 50) {
        time_i = 50;
    }
    else if (file_size >= 50 && file_size < 500) {
        time_i = 20;
    }
    else if (file_size >= 500 && file_size <= 1000) {
        time_i = 10;
    }
    else {
        time_i = 1;
    }

    disk_param current_disk;
    COORD current_crd = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    COORD name_crd = { 12, current_crd.Y + 3 }, proc_crd = { 17, current_crd.Y }, time_crd = { 19, current_crd.Y + 1 }, free_crd = { 19, current_crd.Y + 2 }, exit_crd = { 0, current_crd.Y + 4 };

    current_disk = GetHardDriveInfo(current.lpcw, false);
    Sleep(1000);
    cout << "Готово примерно: 0  %\n" << "Примерно осталось:      мин\n" << "Свободно на диске:      Гб\n" << "Скопирован: ";
    auto timer = chrono::system_clock::now();
    while (true) {
        if (ctr - tim_ctr >= time_i) {
            auto t = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = t - timer;
            //cout << elapsed_seconds.count() << "сек";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), time_crd);
            cout << "    ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), time_crd);
            cout << (int)(GetHardDriveInfo(current.lpcw, false).free_mem * 1024 / (time_i * file_size)) * (int)elapsed_seconds.count() / 60;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), free_crd);
            cout << "     ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), free_crd);
            cout << (int)GetHardDriveInfo(current.lpcw, false).free_mem;
            tim_ctr = ctr;
            timer = chrono::system_clock::now();
        }
        string buff = current.str + 'l' + to_string(ctr) + ".bin";
        wstring stemp = wstring(buff.begin(), buff.end());
        LPCWSTR sw = stemp.c_str();
        CopyFile(L"l1pz.bin", sw, false);
        proc = (100 * file_size * ctr) / (GetHardDriveInfo(current.lpcw, false).free_mem * 1024);
        if (proc != prev) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), proc_crd);
            cout << "   ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), proc_crd);
            cout << proc;
        }

        if (GetLastError() > 0) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), exit_crd);
            cout << "Error" << GetLastError() << endl;
        }
        else {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), name_crd);
            cout << buff;
        }
        if (GetLastError() == 112 || GetLastError() == 39) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), exit_crd);
            cout << "места нет. готово" << endl;
            GetHardDriveInfo(current.lpcw, true);
            break;
        }
        prev = proc;
        ctr++;
    }
}

void report(chrono::system_clock::time_point start) {
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    time_t start_time = chrono::system_clock::to_time_t(start);

    cout << "Начало: " << ctime(&start_time)
        << "Конец: " << ctime(&end_time)
        << "Затрачено: " << elapsed_seconds.count() / 60 << "мин или " << elapsed_seconds.count() / 3600 << "час"
        << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    if (argc < 3) {
        if (*argv[1] == 'h') {
            cout << "Помощь:\n"
                << "1 аргумент - Размер файла подкачки в Мбайт\n"
                << "2 аргумент - Имя диска для зачистки в формате [A:\\]\n";

        }
        else {
            cout << "Мало аргументов!\n Используйте [loader.exe h] для помощи!" << endl;
        }
        return 0;
    }
    cout << "Диск: " << argv[2] << '\n'
        << "Размер файла подкачки в Мбайт: " << argv[1] << endl;



    disk target;
    target.str = argv[2];
    wstring sw = wstring(target.str.begin(), target.str.end());

    target.lpcw = sw.c_str();;


    prep_file(atoi(argv[1]));
    auto start = std::chrono::system_clock::now();
    work(target, atoi(argv[1]));
    report(start);
    return 0;
}





