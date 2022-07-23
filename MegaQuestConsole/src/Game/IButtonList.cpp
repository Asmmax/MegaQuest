#include "Game/IButtonList.hpp"

using namespace Game;

void IButtonList::Update()
{
	for (auto& callback : _preUpdateCallbacks) {
		callback();
	}
	UpdateImpl();
}

void IButtonList::Do(int answer)
{
	DoImpl(answer);
	for (auto& callback : _doneCallbacks) {
		callback();
	}
}

void IButtonList::AddPreUpdateCallback(const Callback& callback)
{
	_preUpdateCallbacks.push_back(callback);
}

void IButtonList::AddDoneCallback(const Callback& callback)
{
	_doneCallbacks.push_back(callback);
}
