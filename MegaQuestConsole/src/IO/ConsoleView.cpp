#include "IO/ConsoleView.hpp"
#include <iostream>
#include <locale>

using namespace IO;
using namespace QuestCore;

ConsoleView::ConsoleView(const TextString& intro)
{
    std::setlocale(LC_ALL, "");

#ifdef _WIN32
    std::wcout << intro.ToUtf16();
#else
    std::cout << intro.ToUtf8();
#endif // _WIN32
}

void ConsoleView::Write(const TextString& text)
{
#ifdef _WIN32
    std::wcout << std::endl;
    std::wcout << text.ToUtf16();
#else
    std::cout << std::endl;
    std::cout << text.ToUtf8();
#endif // _WIN32
}
