#pragma once
#include "Game.h"
#include "Bone.h"

namespace MenuConfig
{
	inline bool ShowBoneESP = true;
	inline bool ShowBoxESP = true;
	inline bool ShowHealthBar = true;
	inline bool ShowWeaponESP = true;
	inline bool ShowEyeRay = true;
	inline bool ShowPlayerName = true;

	inline bool AimBot = true;
	inline int AimBotHotKey = 0;
	// 0: head 1: neck 3: spine
	inline int  AimPosition = 0;
	inline DWORD  AimPositionIndex = BONEINDEX::head;

	// 0: normal 1: dynamic
	inline int  BoxType = 0;
	// 0: Vertical 1: Horizontal
	inline int  HealthBarType = 0;

	inline ImColor BoneColor = ImColor(255, 255, 255, 255);
	inline ImColor BoxColor = ImColor(255, 255, 255, 255);
	inline ImColor EyeRayColor = ImColor(255, 0, 0, 255);

	inline bool ShowMenu = true;

	inline bool ShowRadar = true;
	inline float RadarRange = 150;
	inline bool ShowCrossLine = true;
	inline ImColor CrossLineColor = ImColor(34, 34, 34, 180);
	// 0: circle 1: arrow 2: circle with arrow
	inline int RadarType = 2;
	inline float Proportion = 2300;

	inline bool TriggerBot = true;
	inline int TriggerHotKey = 0;

	inline bool TeamCheck = true;
	inline bool VisibleCheck = false;
	inline bool ShowHeadShootLine = true;
	inline ImColor HeadShootLineColor = ImColor(255, 255, 255, 255);

	inline bool ShowFovLine = true;
	inline ImColor FovLineColor = ImColor(55, 55, 55, 220);
	inline float FovLineSize = 60.f;

	inline bool ShowLineToEnemy = false;
	inline ImColor LineToEnemyColor = ImColor(255, 255, 255, 220);
}