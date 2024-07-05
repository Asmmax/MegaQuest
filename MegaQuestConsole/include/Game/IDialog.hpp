#pragma once
#include <string>
#include <memory>

namespace Game
{
	class IButtonList;
	class IOutput;

	class IDialog
	{
	public:
		virtual ~IDialog() = default;
		virtual void Init(IOutput& output) = 0;
		virtual void Update() = 0;
		virtual void Draw(IOutput & output) = 0;
	};
}
