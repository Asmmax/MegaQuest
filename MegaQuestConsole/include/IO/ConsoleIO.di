bind "IO/ConsoleInput.hpp";
bind "IO/ConsoleOutput.hpp";

shared IO::ConsoleInput : Game::IInput 
{
};

shared IO::ConsoleOutput : Game::IOutput
{
};
