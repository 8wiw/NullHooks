#include "eventlistener.hpp"
#include "../interfaces/interfaces.hpp"
#include "../../core/features/features.hpp"

void CEventListener::Setup(const std::deque<const char*>& arrEvents) {
	if (arrEvents.empty())
		return;

	for (auto szEvent : arrEvents) {
		interfaces::event_manager->add_listener(this, szEvent, false);

		if (!interfaces::event_manager->find_listener(this, szEvent))
			throw std::runtime_error("failed add listener");
	}
}

void CEventListener::Destroy() {
	interfaces::event_manager->remove_listener(this);
}

void CEventListener::FireGameEvent(i_game_event* pEvent) {
	if (pEvent == nullptr)
		return;

	const unsigned int uNameHash = fnv::hash(pEvent->get_name());

	// *pEvent ??
	visuals::bullet_tracers::bullet_tracer.log(*pEvent, uNameHash);
}