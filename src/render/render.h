#pragma once

#include "../valve_sdk/csgostructs.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/directx9/imgui_impl_dx9.h"

namespace render
{
	namespace fonts
	{
		extern ImFont* main;
		extern ImFont* visuals;
		extern ImFont* low_size;
		extern ImFont* notifies;
		extern ImFont* spectators;
		extern ImFont* configs_list;

		extern ImFont* header_title;
		extern ImFont* header_buttons;
	}

	void initialize();
	void destroy();

	void device_lost();
	void device_reset();

	bool is_ready();

	/*gui helpers*/
	const char* ___(const char* english, const char* russian);

	void tooltip(const char* text);
	void tooltip(const char* english, const char* russian);

	bool selectable(const char* label, bool selected);
	void combo(const char* label, const std::function<void(std::string&)>& body);
	ImVec2 get_listbox_size(float x = 0, float y_offset = 0.f);

	bool ColorEdit4(const char* label, ImVec4* v);
	bool ColorEdit4(const char* label, Color* v);
	bool ColorEdit3(const char* label, Color* v);

	void columns(int count);
	void separator(const char* label);
	void separator(const char* en, const char* ru);

	void child(const char* label, const std::function<void()>& body);

	void checkbox(const char* label, bool* value);
	void checkbox(const char* english, const char* russian, bool* value);

	void switch_hwnd();

	namespace menu
	{
		struct weapon_type_t
		{
			const char* name;
			int type;
		};

		bool is_visible();
		void toggle();
		void background();
		void show();

		void visuals_tab();
		void aimbot_tab();
		void misc_tab();
		void skins_tab();
		void players_tab();
		void configs_tab();
		void glow_tab();
	}

	namespace timers
	{
		void show();
	}

	namespace spectators
	{
		void show();
	}
}