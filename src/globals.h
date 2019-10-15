#pragma once

#include <map>
#include <vector>
#include <string>
#include "options.hpp"

namespace globals 
{
	extern bool chat_translation;
	extern bool post_processing;
	extern bool configs_initialized;
	extern bool no_animations;
	extern bool russian_language;

	extern int yaw_offset;
	extern float last_yaw_offset;

	extern QAngle angles;
	extern ImDrawList* draw_list;

	extern std::string settings;
	extern std::string playername;

	extern std::map<int, int> team_damage;

	void save();
	void load();

	namespace view_matrix
	{
		extern bool has_offset;
		extern DWORD offset;
	}

	namespace clantag
	{
		extern float delay;
		extern std::string value;
		extern bool animation;
	}

	namespace binds
	{
		namespace thirdperson
		{
			extern bool enabled;
			extern int key;
		}
		
		extern int fake_duck;
		extern int desync;
		extern int back_shot;
		extern int esp;
		extern int trigger;
		extern int fake_lag;
		extern int zeus_bot;
		extern int lightning_shot;
		extern int slow_walk;

		extern bool notify_when_loaded;
		extern std::map<std::string, int> configs;

		void handle(const int& key);
	}
}