#include "Printer.hpp"


Printer::Printer(std::string Language, int TextColor) {
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->Language = GetSystemDefaultUILanguage(); // Recieve Language
    setlocale(LC_ALL, "rus");
}

template<typename Type>
void Printer::PrintLine(Type MsgFirst, Type MsgSecond, Type MsgThird, Type MsgFirth){
    this->LineCtr += 1;


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