#include "../render.h"
#include "../../globals.h"
#include "../../settings.h"
#include "../../helpers/imdraw.h"
#include "../../helpers/console.h"

extern void bind_button(const char* eng, const char* rus, int& key);
extern bool hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0.f, 0.f));

namespace render
{
	namespace menu
	{
		void visuals_tab()
		{			
			child("ESP", []()
			{
				columns(2);
				{
					checkbox("Enabled", u8"��������", &settings::esp::enabled);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					hotkey("##binds.esp", &globals::binds::esp);
					ImGui::PopItemWidth();
				}
				columns(1);

				checkbox("Visible Only", u8"�������� ���������", &settings::esp::visible_only);

				checkbox("Name", u8"���", &settings::esp::names);
				checkbox("Weapon", u8"������", &settings::esp::weapons);

				columns(2);
				{
					checkbox("Boxes", u8"�����", &settings::esp::boxes);

					ImGui::NextColumn();

					const char* box_types[] = {
						___("Normal", u8"�������"), ___("Corner", u8"�������")
					};

					ImGui::PushItemWidth(-1);
					{
						ImGui::Combo("##esp.box_type", &settings::esp::box_type, box_types, IM_ARRAYSIZE(box_types));
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
	
				const char* positions[] =
				{
					___("Left", u8"�����"),
					___("Right", u8"������"),
					___("Bottom", u8"�����"),
				};

				columns(2);
				{
					checkbox("Health", u8"��������", &settings::esp::health);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("##health.position", &settings::esp::health_position, positions, IM_ARRAYSIZE(positions));
					ImGui::PopItemWidth();
				}
				columns(1);

				columns(2);
				{
					checkbox("Armor", u8"�����", &settings::esp::armour);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("##armor.position", &settings::esp::armour_position, positions, IM_ARRAYSIZE(positions));
					ImGui::PopItemWidth();
				}
				columns(1);

				//checkbox("Dormant", &Settings::ESP::dormant);
				checkbox("Is Scoped", &settings::esp::is_scoped);
				checkbox("Snap Lines", &settings::esp::snaplines);
				checkbox("Beams", u8"���� �����", &settings::esp::beams);

				checkbox("Sound Direction (?)", &settings::esp::sound);
				tooltip("Sound ESP", u8"���������� ��������� ����������� �����, ������ ������ ������.");

				checkbox("Point of Direction (?)", u8"����� ����������� (?)", &settings::esp::offscreen);
				tooltip("Off Screen ESP", u8"���������� ��������� ��������� ������. ��������, ����� ����� ��������� �� ������.");

				ImGui::Separator();

				ColorEdit4(___("Visible", u8"�������"), &settings::esp::visible_color);
				ColorEdit4(___("Occluded", u8"�� ���������"), &settings::esp::occluded_color);
			});

			ImGui::NextColumn();

			child(___("Chams", u8"������� ������"), []()
			{
				checkbox("Enabled", u8"��������", &settings::chams::enabled);
				checkbox("Visible Only", u8"�������� ���������", &settings::chams::visible_only);
				checkbox("Wireframe", u8"�����", &settings::chams::wireframe);
				checkbox("Flat", &settings::chams::flat);

				separator("Arms", u8"����");

				checkbox("Enabled##arms", u8"��������##arms", &settings::chams::arms::enabled);
				checkbox("Wireframe##arms", u8"�����##arms", &settings::chams::arms::wireframe);

				ImGui::Separator();

				ColorEdit4(___("Visible", u8"�������"), &settings::chams::visible_color);
				ColorEdit4(___("Occluded", u8"�� ���������"), &settings::chams::occluded_color);

				ColorEdit4(___("Arms", u8"����"), &settings::chams::arms::color);
			});

			ImGui::NextColumn();

			child(___("Extra", u8"������"), []()
			{
				checkbox("Planted C4", &settings::visuals::planted_c4);
				checkbox("Defuse Kits", u8"������", &settings::visuals::defuse_kit);
				checkbox("World Weapons", u8"��������� ������", &settings::visuals::dropped_weapons);
				checkbox("World Grenades", u8"��������� ������", &settings::visuals::world_grenades);
				checkbox("Sniper Crosshair", u8"����������� ������", &settings::visuals::sniper_crosshair);
				checkbox("Grenade Prediction", u8"������� ������ ������", &settings::visuals::grenade_prediction);
	
				ImGui::Separator();
				
				const auto old_night_state = settings::visuals::night_mode;
				checkbox("Night Mode", u8"������ �����", &settings::visuals::night_mode);
				if (old_night_state != settings::visuals::night_mode)
					imdraw::apply_style(settings::visuals::night_mode);

				ColorEdit4(___("Sky", u8"����"), &settings::visuals::sky);
				tooltip("Will not work on Dust 2, Inferno and Nuke", u8"�� ����� �������� �� Dust 2, Inferno � Nuke.");
			});
		}
	}
}