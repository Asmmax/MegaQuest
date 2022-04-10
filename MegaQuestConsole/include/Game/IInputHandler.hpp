#pragma once

namespace Game 
{
	class IInputHandler
	{
	public:
		virtual ~IInputHandler() = default;
		virtual void Handle() = 0;
	};
}
