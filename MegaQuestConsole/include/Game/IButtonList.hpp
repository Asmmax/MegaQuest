#pragma once
#include <functional>

namespace Game
{
	class IButtonList
	{
	public:
		using Ptr = std::shared_ptr<IButtonList>;
		using Callback = std::function<void()>;

		virtual void Do(int answer = 0) = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}
