#pragma once
#include "Game/IButtonList.hpp"
#include <memory>

namespace Game
{
	class ReplayManager;

	/// @serializable
	class ReplayButtonList : public IButtonList
	{
		using ReplayManagerPtr = std::shared_ptr<ReplayManager>;
	public:
		using Ptr = std::shared_ptr<ReplayButtonList>;

		ReplayButtonList(const IButtonList::Ptr& buttonList, const ReplayManagerPtr& manager);
		virtual void Draw(IOutput& output) override;
		virtual bool IsUpdateAfterDone() const override { return false; }

	protected:
		virtual void UpdateImpl() override;
		virtual void DoImpl(int answer) override;

	private:
		IButtonList::Ptr _buttonList;
		ReplayManagerPtr _manager;
	};
}
