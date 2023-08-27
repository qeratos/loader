#include "PayloadGenerator.hpp"


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