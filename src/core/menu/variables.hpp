#pragma once
#include "global_input.hpp"

namespace variables {
	namespace aim {
		inline bool triggerbot = false;
		inline hotkey_t triggerbot_key(VK_PRIOR);

		inline bool aimbot = false;
		inline float aimbot_fov = 0.3f;
		inline bool draw_fov = false;
		inline bool ignore_walls = false;
		inline float aimbot_smoothing = 0.5f;
		inline bool aimbot_isvisiblecheck = true;
		inline bool target_friends = false;
		inline bool non_rifle_aimpunch = true;
		inline bool aimbot_noscope = true;
	}

	namespace player_visuals {
		inline bool showteamesp = false;
		inline bool playerglow = false;
		inline bool boxesp = false;
		inline bool lineesp = false;
		inline bool skeletonesp = false;
		inline bool nameesp = false;
		inline bool playerinfo = false;
		inline bool healthesp = false;
	}

	namespace entity_visuals {
		inline bool entityglow = false;
		inline bool entitytext = false;
		inline bool bombtimer = true;
		inline bool nade_esp = false;
	}

	namespace chams {
		inline std::vector<std::string> materials = {
			"Transparent",
			"Textured",
			"Flat",
			"Ghost",
			"Gold 1",
			"Gold 2",
			"Amethyst",
			"Silver",
			"Steel",
			"Dark steel",
			"Plastic",
			"Red glow",
			"Effect 1",
			"Effect 2",
			"Effect 3",
			"Animated blink",
			"Animated stripes"
		};

		// Enabled options
		inline bool only_visible_chams = false;
		inline bool draw_chams_on_top = false;
		inline bool wireframe_chams = false;
		inline bool player_chams = false;
		inline bool vm_weapon_chams = false;
		inline bool vm_arm_chams = false;
		inline bool vm_sleeve_chams = false;

		// Selected material for each setting
		inline int player_chams_mat_id = 1;
		inline int sleeve_chams_mat_id = 6;
		inline int arm_chams_mat_id = 7;
		inline int weapon_chams_mat_id = 5;

		// Used for togling popups
		inline bool player_chams_popup_tog = false;
		inline bool sleeve_chams_popup_tog = false;
		inline bool arm_chams_popup_tog = false;
		inline bool weapon_chams_popup_tog = false;
	}

	namespace misc_visuals {
		inline bool nade_predict = true;
		inline float noflash_alpha = 0.f;
		inline bool noscope  = true;
		inline bool crosshair = false;
		inline bool recoil_crosshair = false;

		inline bool chickenpride = false;

		inline float custom_fov_slider = 90.f;
		inline float custom_vmfov_slider = 1.f;
	}

	namespace misc {
		inline bool infinite_duck = false;
		inline bool bhop = true;
		inline bool edgejump = false;
		inline hotkey_t ej_key('C');	// Mind the ' ' and the capital letter
		inline bool edgebug = false;
		inline hotkey_t eb_key(VK_XBUTTON1);
		inline bool jumpbug = false;
		inline hotkey_t jb_key(VK_MENU);	// Alt key
		inline bool draw_watermark = true;
		inline bool draw_speedgraph = false;
		inline bool use_speedgraph_color = false;
		inline float speedgraph_h = 50.f;
		inline float speedgraph_pos = 92.5;
		inline bool draw_stats = true;
		inline bool clean_screenshots = true;
	}
	
	namespace ui {
		namespace spectators {
			inline bool spectator_list = true;
			inline int x = 10, y = 560;
			inline int w = 100, h = 10;
		}

		namespace menu {
			inline bool opened = false;
			inline int x = 300, y = 200;
			inline int w = 500, h = 450;
		}

		namespace watermark {
			inline int y = 10;
			inline int x = 15;
		}
	}

	namespace crosshair {
		const inline bool only_engine_crosshair = true;		// Edit here
		inline bool using_cs_crosshair = true;

		inline float crosshair_len = 3;		// 2-20
		inline float crosshair_w = 2;		// 2-15
		inline float crosshair_gap = 0;		// 0-10

		inline bool rainbow_crosshair = false;
	}

	namespace colors {
		// Esp and glow
		inline color friendly_color = color(0, 90, 255, 255);
		inline bool friendly_color_tog = false;
		inline color friendly_color_soft = color(0, 150, 255, 255);
		inline color friendly_color_softer = color(90, 180, 255, 255);
		inline color enemy_color = color::red(255);
		inline bool enemy_color_tog = false;
		inline color enemy_color_soft = color(190, 25, 25, 255);
		inline bool enemy_color_soft_tog = false;
		inline color enemy_color_softer = color(255, 75, 75, 255);

		// Chams
		inline color chams_vis_enemy_c = color(230, 20, 70);
		inline bool chams_vis_enemy_tog = false;
		inline color chams_inv_enemy_c = color(150, 15, 15, 255);
		inline color chams_vis_friend_c = color(0, 150, 255);
		inline bool chams_vis_friend_tog = false;
		inline color chams_inv_friend_c = color(0, 75, 255);

		inline color chams_sleeve_c = color(200, 0, 200, 255);
		inline bool chams_sleeve_c_tog = false;
		inline color chams_arms_c = color(255, 0, 255, 255);
		inline bool chams_arms_c_tog = false;
		inline color chams_weapon_c = color(255, 150, 255, 255);
		inline bool chams_weapon_c_tog = false;

		// Misc
		inline color crosshair_c = color::white();
		inline bool crosshair_c_tog = false;
		inline color recoil_crosshair_c = color(0, 255, 0, 255);
		inline bool recoil_crosshair_c_tog = false;
	};

	inline struct MotionBlur {
		bool enabled{ false };
		bool forwardEnabled{ false };
		float fallingMin{ 10.0f };
		float fallingMax{ 20.0f };
		float fallingIntensity{ 1.0f };
		float rotationIntensity{ 1.0f };
		float strength{ 2.0f };
	} motion_blur;
}
