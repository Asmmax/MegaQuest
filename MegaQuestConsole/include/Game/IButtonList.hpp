#pragma once
#include <functional>
#include <vector>

namespace Game
{
	class IOutput;

	/// @serializable @shared buttonLists @abstract
	class IButtonList
	{
	public:
		using Ptr = std::shared_ptr<IButtonList>;
		using Callback = std::function<void()>;

		void Update();
		void Do(int answer = 0);
		virtual void Draw(IOutput& output) = 0;

		void AddPreUpdateCallback(const Callback& callback);
		void AddDoneCallback(const Callback& callback);
		virtual bool IsUpdateAfterDone() const = 0;

	protected:
		virtual void UpdateImpl() = 0;
		virtual void DoImpl(int answer) = 0;

	private:
		std::vector<Callback> _preUpdateCallbacks;
		std::vector<Callback> _doneCallbacks;
	};
}
