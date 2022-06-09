#pragma once
#include <string>
#include <memory>

namespace Game
{
	class ButtonList;

	class IDialog
	{
		using ButtonListPtr = std::shared_ptr<ButtonList>;
	public:
		using Ptr = std::shared_ptr<IDialog>;

		virtual ~IDialog() = default;
		virtual ButtonListPtr GetButtonList(const std::string& key = std::string()) = 0;
		virtual void Update() = 0;
	};
}
