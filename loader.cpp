#define _CRT_SECURE_NO_WARNINGS

#include "Loader.hpp"
#include "PayloadGenerator.hpp"
#include "ArgParser.hpp"


int Loader::ChooseReportInterval()
{
    if (this->FileSize < 50) {
        return 50;
    }
    else if (this->FileSize >= 50 && this->FileSize < 500) {
        return 20;
    }
    else if (this->FileSize >= 500 && this->FileSize <= 1000) {
        return 10;
    }
    else {
        return 1;
    }
}

Loader::DiskInfo Loader::GetDriveInfo(LPCWSTR Disk) {
    ULARGE_INTEGER FreeBytesToCaller, TotalBytes, FreeBytes;
    GetDiskFreeSpaceEx(Disk, &FreeBytesToCaller, &TotalBytes, &FreeBytes);
    CurrentDisk.AllMem = TotalBytes.QuadPart / (1024 * 1024 * 1024);
    CurrentDisk.FreeMem = FreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
    return CurrentDisk;
}

void Loader::StartTime(){
    this->StartTimePtr = std::chrono::system_clock::now();
}

void Loader::EndTime(){
    this->EndTimePtr = std::chrono::system_clock::now();
}

std::chrono::duration<double> Loader::SpendTime(){    
    return this->EndTimePtr - this->StartTimePtr;
}

void Loader::LoadDisk(){
    this->StartTime();

    while(true){




        if (GetLastError() == 112 || GetLastError() == 39) {
            GetDriveInfo(CurrentDisk.LpcwName);
            break;
        }
    }

    this->EndTime();
    this->SpendTime();
}






//void work(disk current, int file_size) {
//    cout << "готово примерно: 0  %\n" << "примерно осталось:      мин\n" << "свободно на диске:      гб\n" << "скопирован: ";
//    auto timer = chrono::system_clock::now();
//    while (true) {
//        if (ctr - tim_ctr >= time_i) {
//            auto t = chrono::system_clock::now();
//            std::chrono::duration<double> elapsed_seconds = t - timer;
//            cout << elapsed_seconds.count() << "сек";
//            setconsolecursorposition(getstdhandle(std_output_handle), time_crd);
//            cout << "    ";
//            setconsolecursorposition(getstdhandle(std_output_handle), time_crd);
//            cout << (int)(getharddriveinfo(current.lpcw, false).free_mem * 1024 / (time_i * file_size)) * (int)elapsed_seconds.count() / 60;
//                setconsolecursorposition(getstdhandle(std_output_handle), free_crd);
//            cout << "     ";
//            setconsolecursorposition(getstdhandle(std_output_handle), free_crd);
//            cout << (int)getharddriveinfo(current.lpcw, false).free_mem;
//            tim_ctr = ctr;
//            timer = chrono::system_clock::now();
//        }
//        string buff = current.str + 'l' + to_string(ctr) + ".bin";
//        wstring stemp = wstring(buff.begin(), buff.end());
//        lpcwstr sw = stemp.c_str();
//        copyfile(l"l1pz.bin", sw, false);
//        proc = (100 * file_size * ctr) / (getharddriveinfo(current.lpcw, false).free_mem * 1024);
//        if (proc != prev) {
//            setconsolecursorposition(getstdhandle(std_output_handle), proc_crd);
//            cout << "   ";
//            setconsolecursorposition(getstdhandle(std_output_handle), proc_crd);
//            cout << proc;
//        }
//
//        if (getlasterror() > 0) {
//            setconsolecursorposition(getstdhandle(std_output_handle), exit_crd);
//            cout << "error" << getlasterror() << endl;
//        }
//        else {
//            setconsolecursorposition(getstdhandle(std_output_handle), name_crd);
//            cout << buff;
//        }
//        if (getlasterror() == 112 || getlasterror() == 39) {
//            setconsolecursorposition(getstdhandle(std_output_handle), exit_crd);
//            cout << "места нет. готово" << endl;
//            getharddriveinfo(current.lpcw, true);
//            break;
//        }
//        prev = proc;
//        ctr++;
//    }
//}

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

    target.str = argv[2];
    wstring sw = wstring(target.str.begin(), target.str.end());

    target.lpcw = sw.c_str();;


    prep_file(atoi(argv[1]));
    auto start = std::chrono::system_clock::now();
    work(target, atoi(argv[1]));
    report(start);
    return 0;
}





