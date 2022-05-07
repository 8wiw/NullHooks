#pragma once
#include <deque>
#include "../../source-sdk/sdk.hpp"
#include "../interfaces/i_game_event_manager.hpp"

class CEventListener : public i_game_event_listener2
{
public:
	void Setup(const std::deque<const char*>& arrEvents);
	void Destroy();

	virtual void FireGameEvent(i_game_event* pEvent);
	virtual int GetEventDebugID() {
		return EVENT_DEBUG_ID_INIT;
	}
};