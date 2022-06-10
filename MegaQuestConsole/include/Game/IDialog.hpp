#pragma once
#include <string>
#include <memory>

namespace Game
{
	class IButtonList;

	class IDialog
	{
		using ButtonListPtr = std::shared_ptr<IButtonList>;
	public:
		using Ptr = std::shared_ptr<IDialog>;

		virtual ~IDialog() = default;
		virtual ButtonListPtr GetButtonList(const std::string& key = std::string()) = 0;
		virtual void Init() = 0;
		virtual void Update() = 0;
	};
}