#include "../features.hpp"

void visuals::grenade_projectile_esp() {
	if (!(variables::nade_esp_bool
		|| variables::drawc4_bool)) return;
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;
	if (!csgo::local_player) return;

	for (int i = 1; i <= interfaces::entity_list->get_highest_index(); i++) {
		entity_t* entity = reinterpret_cast<entity_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity) continue;

		vec3_t origin = entity->origin(), w2s;

		// TODO: Add fire, smoke, etc. effect timer
		if (math::world_to_screen(origin, w2s)) {
			auto class_id = entity->client_class()->class_id;
			switch (class_id) {
				/* ------------ NADE PROJECTILES ------------ */
				case cbasecsgrenadeprojectile: {
					const model_t* model = entity->model();
					if (!model) return;

					studio_hdr_t* hdr = interfaces::model_info->get_studio_model(model);
					if (!hdr) return;

					std::string name = hdr->name_char_array;
					if (name.find("incendiarygrenade") != std::string::npos || name.find("fraggrenade") != std::string::npos) {
						render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "frag", true, color(255, 0, 0));
						break;
					}
					render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "flash", true, color(255, 255, 0));
					break;
				}
				case cmolotovprojectile:
				case cinferno:
					render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "fire", true, color(255, 0, 0));
					break;
				case csmokegrenadeprojectile:
					render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "smoke", true, color(0, 160, 255));
					break;
				case cdecoyprojectile:
					render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "decoy", true, color::white(255));
					break;
				/* ------------ BOMB ------------ */
				case cplantedc4:
					entity_info::bomb(entity);
					break;
				case cc4:
					entity_info::dropped_bomb(entity);
					break;
				/* ------------------------------ */
				default:
					break;
			}
		}
	}
}