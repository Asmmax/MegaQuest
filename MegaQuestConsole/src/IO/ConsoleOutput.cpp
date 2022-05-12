#include "IO/ConsoleOutput.hpp"
#include "TextString.hpp"
#include <iostream>
#include <locale>

using namespace IO;
using namespace QuestCore;

ConsoleOutput::ConsoleOutput()
{
    std::setlocale(LC_ALL, "");
}

void ConsoleOutput::Write(const TextString& text)
{
#ifdef _WIN32
    std::wcout << text.ToUtf16();
#else
    std::cout << text.ToUtf8();
#endif // _WIN32
}

void ConsoleOutput::WriteLn(const TextString& text)
{
#ifdef _WIN32
    std::wcout << text.ToUtf16();
    std::wcout << std::endl;
#else
    std::cout << text.ToUtf8();
    std::cout << std::endl;
#endif // _WIN32
}

void ConsoleOutput::WriteLn()
{
#ifdef _WIN32
    std::wcout << std::endl;
#else
    std::cout << std::endl;
#endif // _WIN32
}
