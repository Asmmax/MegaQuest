#pragma once
#include <memory>

namespace QuestCore
{
	class TextString;
}

class IModel
{
public:
	using Ptr = std::shared_ptr<IModel>;

	virtual ~IModel() = default;
	virtual void OpenInventory() = 0;
	virtual bool Handle(int answer) = 0;
	virtual void Init() = 0;
};
