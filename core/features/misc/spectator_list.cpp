#include "../features.hpp"
#include "../../menu/menu.hpp"

void draw_spec_frame(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, std::int32_t wname_h, std::int32_t wname_margin, color bg, color header_text, color header_line, const std::string& name) {
	// Background
	render::draw_filled_rect(x, y, w, h, bg);
	// Header title
	render::draw_filled_rect(x, y, w, wname_h, header_text);
	render::draw_filled_rect(x, y + wname_h, w, 2, header_line);
	render::draw_text_string(x + 10, y + wname_margin, render::fonts::watermark_font, name, false, color::white(255));
};

void misc::spectator_list() {
	if (!variables::spectators::spectator_list_bool) return;

	if (interfaces::engine->is_connected() || variables::menu::opened) {
		if (!csgo::local_player) return;
		int spec_count = 0;			// Will count actual spectators
		std::string spec_arr[64 + 1];

		// Clear usernames array
		for (int i = 0; i <= interfaces::globals->max_clients; i++) {
			spec_arr[i] = "";
		}

		// Get usernames from spectators
		for (int i = 0; i <= interfaces::globals->max_clients; i++) {
			player_t* e = (player_t*)interfaces::entity_list->get_client_entity(i);
			player_info_t pinfo;

			if (!e) continue;
			if (e && e != csgo::local_player && !e->dormant()) {
				interfaces::engine->get_player_info(i, &pinfo);

				auto obs = e->observer_target();
				if (!obs) continue;
				
				player_t* spec = (player_t*)interfaces::entity_list->get_client_entity_handle(obs);
				if (spec == nullptr) continue;
				
				player_info_t spec_info;
				interfaces::engine->get_player_info(i, &spec_info);
				char buf[255];
				sprintf(buf, "%s", pinfo.name);

				if (strstr(buf, "GOTV")) continue;

				if (spec->index() == csgo::local_player->index()) {
					spec_arr[spec_count] = buf;
					spec_count++;
				}
			}
		}

		// Only render if there are spectators or the menu is open
		if (spec_arr[0] != "" || variables::menu::opened) {
			/*
			// Bakground
			interfaces::surface->set_drawing_color(34, 34, 37, 200);
			interfaces::surface->draw_filled_rectangle(pos_x, pos_y - 1, win_w, win_h);
			// Rectangle
			interfaces::surface->set_drawing_color(150, 22, 22);
			interfaces::surface->draw_outlined_rect(pos_x, pos_y - 1, win_w, win_h);
			// Title
			render::draw_text_string(pos_x, pos_y - 15, render::fonts::watermark_font, "Spectators", false, color(230, 0, 0));
			*/

			int cur_name_w = variables::spectators::w;
			int cur_name_h;

			const int wname_h = 25;
			variables::spectators::w = 100;
			variables::spectators::h = 5 + (15 * spec_count) + 5 + wname_h;
			
			draw_spec_frame(variables::spectators::x, variables::spectators::y, cur_name_w, variables::spectators::h, wname_h, 5,
				color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "Spectators");

			// Print each username
			std::string username = "";
			for (int i = 0; i < spec_count; i++) {
				username = spec_arr[i];
				if (username != "") {
					const std::wstring converted_str = std::wstring(username.begin(), username.end());
					interfaces::surface->get_text_size(render::fonts::watermark_font, converted_str.c_str(), cur_name_w, cur_name_h);
					if (cur_name_w > variables::spectators::w - 20)
						variables::spectators::w = 10 + cur_name_w + 10;
					render::draw_text_string(variables::spectators::x + 10, (variables::spectators::y + wname_h + 5 + (15 * i)),
						render::fonts::watermark_font, username, false, color(255, 255, 255));
				}
			}
		}
	}
}