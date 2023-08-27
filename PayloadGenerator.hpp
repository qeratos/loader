#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Printer.hpp"

#define MEGA_PTR 1048576

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