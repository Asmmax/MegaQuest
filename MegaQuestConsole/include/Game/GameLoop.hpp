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
        using InputHandlerPtr = std::shared_ptr<IO::InputHandler>;

    public:
        GameLoop(const InputHandlerPtr& inputHandler);
        void Update();
        void Init();
        int Run();
        void Quit();

    private:
        InputHandlerPtr _inputHandler;
        bool _isStoped = true;
    };
}
