#include "../features.hpp"

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/235892-bullet-tracer.html

void visuals::bullet_tracers::cbullet_tracer::log(i_game_event& event, const unsigned int name_hash) {
	//if we receive bullet_impact event
	if (name_hash == fnv::hash("player_hurt"))
	{
		auto index = interfaces::engine->get_player_for_user_id(event.get_int("userid"));

		if (index != interfaces::engine->get_local_player()) return;

		//get local player
		if (!csgo::local_player) return;

		//get the bullet impact's position
		vec3_t position(event.get_float("x"), event.get_float("y"), event.get_float("z"));

		ray_t ray;
		ray.initialize(csgo::local_player->get_eye_pos(), position);

		//skip local player
		trace_filter filter;
		filter.skip = csgo::local_player;

		//trace a ray
		trace_t tr;
		interfaces::trace_ray->trace_ray(ray, MASK_SHOT, &filter, &tr);

		//use different color when we hit a player
		//auto color = (tr.entity && reinterpret_cast<C_BasePlayer*>(tr.entity)->IsPlayer()) ? color(140, 29, 29, 220) : color(255, 255, 0, 220);

		//push info to our vector
		logs.push_back(cbullet_tracer_info(csgo::local_player->get_eye_pos(), position, interfaces::globals->cur_time, color(255, 0, 0, 220)));
	}
}

void visuals::bullet_tracers::cbullet_tracer::render() {
	if (!variables::bullet_tracers_bool) return;
	if (!csgo::local_player) return;

	//loop through our vector
	for (size_t i = 0; i < logs.size(); i++)
	{
		//get the current item
		auto current = logs.at(i);

		//draw a line from local player's head position to the hit point
		interfaces::debug_overlay->addLineOverlay(current.src, current.dst, current.color.r, current.color.g, current.color.b, true, -1.f);
		//draw a box at the hit point
		interfaces::debug_overlay->addBoxOverlay(current.dst, vec3_t(-2, -2, -2), vec3_t(2, 2, 2), vec3_t(0, 0, 0), 255, 0, 0, 127, -1.f);

		//if the item is older than 5 seconds, delete it
		if (fabs(interfaces::globals->cur_time - current.time) > 5.f)
			logs.erase(logs.begin() + i);
	}
}

/*
#define CEL_PROCEED_EVENT_HANDLING 0x2A

typedef void (*TpfnGEL_Eventfunction)(i_game_event* pEvent);

class CGameEventListener : public i_game_event_listener2 {
private:
	std::string m_szEventName;
	TpfnGEL_Eventfunction m_pfnEventFunc;
public:
	CGameEventListener() : m_szEventName("") {}
	CGameEventListener(const std::string& szGameEventName, const TpfnGEL_Eventfunction pfnEventFunc) : m_szEventName(szGameEventName), m_pfnEventFunc(pfnEventFunc)
	{
		//Register game event listener

		if (!this->RegListener())
			exit(1);
	}

	virtual void HandleGameEvent(i_game_event* pEvent)
	{
		//Handle game event specific data here

		if (pEvent) {
			//Call event function
			this->m_pfnEventFunc(pEvent);
		}
	}

	virtual int IndicateEventHandling(void)
	{
		//Indicate whether 'HandleGameEvent()' shall get called or not

		return CEL_PROCEED_EVENT_HANDLING;
	}

	bool RegListener(void)
	{
		//Register game event listener

		if (!interfaces::event_manager)
			return false;

		if (!this->m_pfnEventFunc)
			return false;

		if (!this->m_szEventName.length())
			return false;

		return interfaces::event_manager->add_listener(this, this->m_szEventName.c_str(), false);
	}
};
*/