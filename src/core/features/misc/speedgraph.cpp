#include "../features.hpp"

const int speed_graph_width = 420;
static std::vector<int> speeds_vec(speed_graph_width, 0);	// Initialize vec of size graph_width with values as 0. Will store all the speed values

void shift_and_append(int new_val) {
	for (int n = 0; n < speed_graph_width - 1; n++) {		// -1 to skip last item
		speeds_vec.at(n) = speeds_vec.at(n + 1);			// Right to left shitf
	}
	speeds_vec.at(speed_graph_width - 1) = new_val;			// Add new value
}

void misc::speed_graph() {
	if (!variables::misc::draw_speedgraph) return;
	if (!interfaces::engine->is_in_game() || !interfaces::engine->is_connected()) return;
	if (!csgo::local_player) return;
	if (!csgo::local_player->is_alive()) return;
	if (csgo::local_player->is_scoped()) return;		// We don't want to draw speed graph when scoped

	const int cur_speed = (int)std::ceil(csgo::local_player->velocity().length_2d());
	shift_and_append(cur_speed);

	// Render graph
	int screen_w, screen_h;
	interfaces::surface->get_screen_size(screen_w, screen_h);

	for (int n = 0; n < speeds_vec.size(); n++) {
		int n_speed = speeds_vec.at(n);

		int cur_x = screen_w / 2 - speed_graph_width / 2 + n;
		int next_x = (n != speeds_vec.size() - 1) ? cur_x + 1 : cur_x;
		int cur_y = screen_h * 0.9 - n_speed * 0.3;
		int next_y = (n != speeds_vec.size() - 1) ? screen_h * 0.9 - speeds_vec.at(n + 1) * 0.3 : cur_y;

		color line_col = color::white();
		if (variables::misc::use_speedgraph_color) {		// color line setting
			if (n_speed < 10) line_col = color::red();
			else if (n_speed < 80) line_col = color(255, 150, 0, 255);
			else if (n_speed < 135) line_col = color(255, 255, 0, 255);
			else if (n_speed < 260) line_col = color(0, 255, 10, 255);
			else line_col = color(0, 210, 230, 255);
		}

		render::draw_line(cur_x, cur_y, next_x, next_y, line_col);
	}

	// Speed text
	color speed_col = color::white();
	if (cur_speed < 95) speed_col = color(255, 150, 0, 255);
	else if (cur_speed < 135) speed_col = color(255, 255, 0, 255);
	else if (cur_speed < 260) speed_col = color(0, 255, 10, 255);
	else speed_col = color(0, 210, 230, 255);
	render::draw_text_string(screen_w/2, screen_h * 0.9 + 20, render::fonts::watermark_font, std::to_string(cur_speed), true, speed_col);
}