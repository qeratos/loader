#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

class Printer {
public:
    Printer(std::string Language, int TextColor);
    void SetCoords(int x, int y);
    template<typename Type>
    void PrintLine(Type MsgFirst, Type MsgSecond, Type MsgThird, Type MsgFirth);
    COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

protected:
    COORD Coords = { 0, 0 };
    HANDLE hConsole = NULL;
    int LineCtr = 0;
    LANGID Language;

};