#include "IO/ConsoleInput.hpp"

#include <iostream>

using namespace IO;


QuestCore::TextString ConsoleInput::GetString() const
{
#ifdef _WIN32
    std::wstring answer;
    std::getline(std::wcin, answer);
    return QuestCore::TextString::FromUtf16(answer);
#else
    std::string answer;
    std::getline(std::cin, answer);
    return QuestCore::TextString::FromUtf8(answer);
#endif // _WIN32
}
