#pragma once
#include <memory>

class InputHandler;

namespace Game
{
    class GameLoop
    {
        using InputHandlerPtr = std::shared_ptr<InputHandler>;

    public:
        GameLoop(const InputHandlerPtr& inputHandler);
        void Update();
        int Run();
        void Quit();

    private:
        InputHandlerPtr _inputHandler;
        bool _isStoped = true;
    };
}
