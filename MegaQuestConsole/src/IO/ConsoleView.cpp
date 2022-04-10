#include "IO/ConsoleView.hpp"
#include <iostream>
#include <locale>

using namespace IO;

ConsoleView::ConsoleView(const std::string& intro)
{
    setlocale(LC_ALL, "Russian");
	std::cout << intro;
}
void ConsoleView::Write(const std::string& text)
{
    std::cout << std::endl;
    std::cout << text;
}
