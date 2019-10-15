#include "features.h"
#include "../globals.h"
#include "../render/render.h"
#include "../helpers/entities.h"
#include "../esp.hpp"
#include "../vec3d.h"

#include <mutex>

namespace offscreen_entities
{
	int alpha = 0;
	bool plus_or_minus = false;

	QAngle angles;
	ImVec2 display_size;
	CUtlVector<SndInfo_t> sndList;

	ImU32 sound_color;
	ImU32 origin_color;

	void dot(const Vector& origin, const Vector& pos, const ImU32& color)
	{
		QAngle aim;
		math::vector2angles(pos - origin, aim);

		Vector popvec;
		math::angle2vectors(QAngle(0, 270, 0) - aim + QAngle(0, angles.yaw, 0), popvec);

		const auto screen_pos = Vector(display_size.x / 2, display_size.y / 2, 0) + (popvec * 380.f);


		globals::draw_list->AddCircleFilled(ImVec2(screen_pos.x, screen_pos.y), 12.f, color);

		int w, h;

		interfaces::engine_client->GetScreenSize(w, h);
		//globals::draw_list->AddCircle(ImVec2(w / 2, h / 2), 12.f, color);

	}

	void ringbeam(Color color, const Vector& sound_pos)
	{
		if (g::local_player || !settings::esp::sound)
			return;

		//Color clr = Color(Math::RandomInt(0, 255), Math::RandomInt(0, 255), Math::RandomInt(0, 255));

		//Color clr = settings::visuals::clr_bullet_tracer;

		// !g_Options.vis_bullet_tracer

		BeamInfo_t beamInfo;
		beamInfo.m_nType = TE_BEAMRINGPOINT;
		beamInfo.m_pszModelName = "sprites/physbeam.vmt";
		beamInfo.m_nModelIndex = interfaces::mdl_info->GetModelIndex("sprites/physbeam.vmt");
		beamInfo.m_nHaloIndex = -1;
		beamInfo.m_flHaloScale = 5;
		beamInfo.m_flLife = 1.5f; //2.5f
		beamInfo.m_flWidth = 10.f; //2.5f
		beamInfo.m_flFadeLength = 1.0f;
		beamInfo.m_flAmplitude = 0.f; // 3.0f
		beamInfo.m_flBrightness = color.a();
		beamInfo.m_flSpeed = 0.f;
		beamInfo.m_nStartFrame = 0;
		beamInfo.m_flFrameRate = 60.f;
		beamInfo.m_flRed = color.r();
		beamInfo.m_flGreen = color.g();
		beamInfo.m_flBlue = color.b();
		beamInfo.m_nSegments = 2;
		beamInfo.m_bRenderable = true;
		beamInfo.m_nFlags = FBEAM_SHADEIN;
		beamInfo.m_vecStart = sound_pos; //+Vector(0, 0, 5); //Sound location
		beamInfo.m_flStartRadius = 20.f;
		beamInfo.m_flEndRadius = 640.f;

		auto beam = g::view_render_beams->CreateBeamRingPoint(beamInfo);
		if (beam)
		{
			g::view_render_beams->DrawBeam(beam);
		}

		g::engine_client->ClientCmd("say called");
	}

	void sound()
	{
		sndList.RemoveAll();
		CallVFunction<void(__thiscall*)(void*, CUtlVector<SndInfo_t>&)>(interfaces::engine_sound, 19)(interfaces::engine_sound, sndList);

		auto eye_pos = interfaces::local_player->GetEyePos();
		for (int i = 0; i < sndList.Count(); i++)
		{
			if (!sndList[i].m_pOrigin || !sndList[i].m_nSoundSource || !sndList[i].m_bUpdatePositions || sndList[i].m_nChannel != 4)
				continue;

			if (eye_pos.DistTo(*sndList[i].m_pOrigin) > 800)
				continue;

			auto* player = c_base_player::GetPlayerByIndex(sndList[i].m_nSoundSource);
			if (!player || !player->IsPlayer() || player->is_dormant() || !player->IsAlive() || player == interfaces::local_player)
				continue;

			if (!settings::misc::deathmatch && player->m_iTeamNum() == interfaces::local_player->m_iTeamNum())
				continue;

			//dot(interfaces::local_player->m_vecOrigin(), *sndList[i].m_pOrigin, sound_color);

			Vector vScreen;

			//if (math::world2screen(*sndList[i].m_pOrigin, vScreen))

			if (settings::esp::sound)
			{
				//globals::draw_list->AddCircle(ImVec2(vScreen.x, vScreen.y), 12.f, sound_color);
				ringbeam(Color::Orange, *sndList[i].m_pOrigin);

			}


		}

		/*for (int i = 0; i < sndList.Count(); i++)
		{
			auto* player = c_base_player::GetPlayerByIndex(sndList[i].m_nSoundSource);
			if (!player || !player->IsPlayer() || player->is_dormant() || !player->IsAlive() || player == interfaces::local_player)
				continue;

			if (!settings::misc::deathmatch && player->m_iTeamNum() == interfaces::local_player->m_iTeamNum())
				continue;

				if (settings::esp::sound)
				{
					//globals::draw_list->AddCircle(ImVec2(vScreen.x, vScreen.y), 12.f, sound_color);
					ringbeam(Color::Orange, *sndList[i].m_nSoundSource);

				}
		}*/
	}

	void render(ImDrawList* _draw_list)
	{
		if (!settings::esp::enabled || render::menu::is_visible() || !interfaces::local_player)
			return;

		if (!settings::esp::offscreen && !settings::esp::sound)
			return;

		if (alpha <= 0 || alpha >= 255)
			plus_or_minus = !plus_or_minus;

		auto modifier = 255.f / 0.8f * interfaces::global_vars->frametime;
		alpha += plus_or_minus ? modifier : -modifier;
		alpha = std::clamp<float>(alpha, 0.f, 255.f);

		origin_color = ImGui::GetColorU32(ImVec4(1.f, 0.1f, 0.f, alpha / 255.f));

		display_size = ImGui::GetIO().DisplaySize;
		interfaces::engine_client->GetViewAngles(angles);

		if (interfaces::local_player->IsAlive() && settings::esp::sound)
		{
			sound_color = ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, alpha / 255.f));
			sound();
		}

	}
}