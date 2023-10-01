#include "Cheats.h"
#include "Render.hpp"

void Cheats::Run()
{
	// 更新矩阵数据
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	// 更新实体链表地址
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// 本地实体
	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;

	// 血条Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// 自瞄数据
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
			continue;
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		bool isEnemy = Entity.Controller.TeamID != LocalEntity.Controller.TeamID;
		if (!Entity.IsAlive())
			continue;
		if (!Entity.IsInScreen())
			continue;

		auto teamColor = isEnemy ? ImColor(255, 0, 0, 255) : ImColor(0, 255, 0, 255);

		// 骨骼调试绘制
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/


		// 绘制骨骼
		Render::DrawBone(Entity, teamColor, 1.3);

		// 绘制朝向
		Render::ShowLosLine(Entity, 50, ImColor(255, 0, 0, 255), 1.3);

		// 绘制2D框
		auto Rect = Render::Draw2DBoneRect(Entity, teamColor, 1.3);

		if (isEnemy) {

			//自瞄数据获取
			DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });

			if (DistanceToSight < AimControl::AimRange)
			{
				if (DistanceToSight < MaxAimDistance)
				{
					MaxAimDistance = DistanceToSight;
					HeadPos = Entity.GetBone().BonePosList[BONEINDEX::head].Pos;
					AimPos = Vec3{ HeadPos.x,HeadPos.y,HeadPos.z - 1.f };//aim position height -1 to aim at the center of head, improve hitchance
				}
			}

			// 绘制血条
			if (!HealthBarMap.count(EntityAddress))
				HealthBarMap.insert({ EntityAddress,Render::HealthBar(100) });

			HealthBarMap[EntityAddress].DrawHealthBar(Entity.Controller.Health,
				{ Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 20 }, { 70,8 });

			// 绘制武器名称
			Gui.Text(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, teamColor, 17);
		}
	}

	if (GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}
