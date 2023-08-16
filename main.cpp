#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <fstream>

#define FILE_NAME "l1pz.bin"
using namespace std;



void prep_file(int file_size) {
    file_size = 1024 * 1024;
    std::ofstream out(FILE_NAME, std::ios::app);

    if (out.is_open()) {
        for (int i = 0; i < file_size; i++) {
            out << (char)(rand() % (126 + 33 - 0) + 0);
        }
    }
    out.close();

}

void GetHardDriveInfo(LPCWSTR p)
{
    ULARGE_INTEGER FreeBytesToCaller, TotalBytes, FreeBytes;
    GetDiskFreeSpaceEx(p, &FreeBytesToCaller, &TotalBytes, &FreeBytes);

    cout << TotalBytes.QuadPart /(1024*1024*1024) << " GB" << endl;
    cout << FreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0) << " GB" << endl;
}
struct disk {
    LPCWSTR lpcw = L"A:\\";
    string str = "A:\\";
};

void work(disk current) {
    int ctr = 0;
    while (true) {
        string buff = current.str + 'l' + to_string(ctr);
        wstring stemp = wstring(buff.begin(), buff.end());
        LPCWSTR sw = stemp.c_str();
        CopyFile((LPWSTR)FILE_NAME, sw, false);
        cout << "Скопирован: " << buff << endl;
        if (GetLastError() > 0) {
            cout << "Error" << GetLastError() << endl;
        }
        if (GetLastError() == 112 || GetLastError() == 39) {
            cout << "места нет. походу готово" << endl;
            GetHardDriveInfo(current.lpcw);
            break;
        }
        //Sleep(10000);
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

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "rus");
    cout << '1' << argv[1] << endl << '2' << argv[2];
    if (argc < 2) {
        if (strcmp(argv[1], "h")) {
            cout << "Помощь:\n"
                << "1 аргумент - Размер файла подкачки в Мбайт\n"
                << "2 аргумент - Имя диска для зачистки\n";

        }else {
            cout << "Мало аргументов!\n Используйте [loader.exe h] для помощи!" << endl;
        }
        return 0;
    } 
    disk target;
    target.lpcw = (LPCWSTR)argv[2];
    target.str = argv[2];


    prep_file((int)argv[1] - 48);
    auto start = chrono::system_clock::now();
    work(target);
    report(start);
  return 0;
}