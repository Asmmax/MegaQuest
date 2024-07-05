#pragma once
#include <memory>

namespace IO
{
    class InputHandler;
}

namespace Game
{
    class GameLoop
    {
    public:
        GameLoop(IO::InputHandler* inputHandler);
        void Update();
        void Init();
        int Run();
        void Quit();

    private:
        IO::InputHandler* _inputHandler;
        bool _isStoped = true;
    };
}
