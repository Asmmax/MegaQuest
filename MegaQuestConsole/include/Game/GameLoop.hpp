#pragma once
#include <memory>

namespace Game
{
    class IInputHandler;

    class GameLoop
    {
    public:
        void SetInputHandler(const std::shared_ptr<IInputHandler>& inputHandler);
        void Update();
        int Run();
        void Quit();

    private:
        std::shared_ptr<IInputHandler> _inputHandler;
        bool _isStoped = true;
    };
}
