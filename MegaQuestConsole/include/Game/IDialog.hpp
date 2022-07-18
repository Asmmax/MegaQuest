#pragma once
#include <string>
#include <memory>

namespace Game
{
	class IButtonList;
	class IOutput;

	/// @serializable @shared dialogs @abstract
	class IDialog
	{
		using ButtonListPtr = std::shared_ptr<IButtonList>;
	public:
		using Ptr = std::shared_ptr<IDialog>;

		virtual ~IDialog() = default;
		virtual void Init(IOutput& output) = 0;
		virtual void Update() = 0;
		virtual void Draw(IOutput & output) = 0;
	};
}
