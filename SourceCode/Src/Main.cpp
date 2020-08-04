//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include "../VCProject2015/VCProject2015/Timer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>
#undef min
#undef max
///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////

bool			left_pressed; // �������Ƿ���
int				map_id = 0;				 // ��ǰ��ͼ 0:welcome; 1:menu; 2:�ؿ�
Card*			card;		// ֲ�￨
Plant*			seed;		// ֲ������
Shovel*			shovel; // ѡ����С����
long double 	fTimeDelta;
int PASCAL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	//��������̨�����������Ϣ���
	FILE* stream;
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "a+", stdout);

	// ��ʼ����Ϸ����
	if (!CSystem::InitGameEngine(hInstance, lpCmdLine))
		return 0;

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	CSystem::SetWindowTitle("PvZ");
	//CSystem::LoadMap("welcome.t2d");

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});
	timer.detach();

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while (CSystem::EngineMainLoop())
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		// ִ����Ϸ��ѭ��
		g_GameMain.GameMainLoop(fTimeDelta);
	};

	// �ر���Ϸ����
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// �˵������ͼ ����ƶ� event handler
static void menu_map_OnMouseMove(const float fMouseX, const float fMouseY) {
	CAnimateSprite adcenture("AdventureGame"); // ð��ģʽ
	CAnimateSprite mini("MiniGame");		   // ������Ϸ
	CAnimateSprite edu("EduGame");			   // ����ģʽ
	if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
		adcenture.AnimateSpritePlayAnimation("AdventureModeAnimation", false);
	}
	if (mini.IsPointInSprite(fMouseX, fMouseY)) {
		mini.AnimateSpritePlayAnimation("MiniModeAnimation", false);
	}
	if (edu.IsPointInSprite(fMouseX, fMouseY)) {
		edu.AnimateSpritePlayAnimation("EduModeAnimation", false);
	}

}
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	// ��ͬ��ͼ�����¼��ֱ��װ������ȫ�ֵĵ�ͼid���ֲ�ͬ��ͼ���¼�
	switch (map_id)
	{
	case 0:
		break;
	case 1:
		menu_map_OnMouseMove(fMouseX, fMouseY);
	default:
		break;
	}
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	if (left_pressed && shovel) {
		shovel->SetSpritePosition(fMouseX, fMouseY);
	}
	else if (left_pressed && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
// �Բ�ͬ��ͼ����¼����з���, �Ա㱣֤��ͬ��ͼ��ͬ�������¼��Ĳ����ͻ
// ��ӭ�����ͼ ����� event handler
static void welcome_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite startBtn("LoadBar");
	if (iMouseType == MOUSE_LEFT) {
		if (startBtn.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("menu.t2d");
			map_id = 1;
		}
	}
}
// �˵������ͼ ����� event handler
static void menu_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite adcenture("AdventureGame");
	if (iMouseType == MOUSE_LEFT) {
		if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("level.t2d");
			map_id = 2;
		}
	}
}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
	// ��ͬ��ͼ�����¼��ֱ��װ������ȫ�ֵĵ�ͼid���ֲ�ͬ��ͼ���¼�
	switch (map_id)
	{
	case 0:
		welcome_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	case 1:
		menu_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	default:
		break;
	}

	// �����ڴ������Ϸ��Ҫ����Ӧ����
	if (iMouseType == MOUSE_LEFT) {

		left_pressed = true;
		card = nullptr;
		seed = nullptr;
		shovel = nullptr;
		// selected_card = g_GameMain.get_sprite_by_position(fMouseX, fMouseY);
		// ��ֵ���� ���Ч��
		std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);

		for (const auto& sprite : sprites) {
			// ѡ�е�λ����̫��
			if (sprite->get_type() == "Sun") {
				Sun* sun = reinterpret_cast<Sun*>(sprite);
				sun->SpriteMoveTo(-43.275, -33.275, 100, true);
				sun->SetSpriteLifeTime(1);
				g_GameMain.add_sun(sun->get_num());
				sun->set_exist(false);

				left_pressed = false;
				break;
			}

			// ѡ�е�λ����С���������κ�����
			if (sprite->get_type() == "Car") {
				continue;
			}

			// ѡ�в���
			if (sprite->get_type() == "Shovel") {
				shovel = reinterpret_cast<Shovel*>(sprite);
				break;
			}

			// ѡ�п�Ƭ
			std::string type = sprite->get_type();
			// ����λCard��ʾ ֲ�￨
			if (type.substr(type.size() - 4, 4) == "Card") {
				// ��갴�� ѡ��ֲ�￨
				card = reinterpret_cast<Card*>(sprite);
				// ���ѡ�еĿ� ��ȴ���
				if (card->ready(fTimeDelta)) {
				//if(true){
					if (sprite->get_type() == "PeaShooterCard") {
						seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "SunflowerCard") {
						seed = g_GameMain.create_sunflower(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "CherryBombCard") {
						// ���µ�ʱ�� �����ж��Ƿ��Զ���ը
						seed = g_GameMain.create_cherry_bomb(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "PotatoMineCard") {
						// ���µ�ʱ�� �����ж��Ƿ��ͷ
						seed = g_GameMain.create_potato_mine(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "WallNutCard") {
						seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "JalapenoCard") {
						// ���µ�ʱ�� �����ж��Ƿ��Զ���ը
						seed = g_GameMain.create_jalapeno(fMouseX, fMouseY, fTimeDelta);
					}
					seed->SetSpriteColorAlpha(100);
				}
				else {
					card = nullptr;
				}
				break;
			}
		}
	}
}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
	float x_slot[10] = { -39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55 };
	float y_slot[5] = { -17, -5, 9, 20, 32 };

	int x = 0, y = 0;
	for (int i = 1; i < 10; i++) {
		if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
			x = i;
		}
	}
	if (iMouseType == MOUSE_LEFT) {
		// ȷ��λ��
		if (left_pressed && seed && card) {
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			seed->SetSpriteColorAlpha(255);
			bool planting = true;

			for (const auto& sprite : sprites) {
				// ������ֲ�� ������
				if (sprite->get_type() == "Plant") {
					planting = false;
					break;
				}

				// �н�ʬ �����
				if (sprite->get_type() == "Zombie") {
					if (card->get_type() == "CherryBombCard") {
						planting = true;
					}
					else {
						planting = false;
					}
					break;
				}
			}

			if (planting && g_GameMain.planting(seed) && card) {
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				card->plant_time(fTimeDelta);
			}
			else {
				seed->DeleteSprite();
			}
		}
		else if (left_pressed && shovel) {
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
			// λ������ֲ�� ����
			for (const auto& sprite : sprites) {
				std::cout << sprite->GetName() << std::endl;
				if (sprite->get_type() == "Plant") {
					Plant* p = reinterpret_cast<Plant*>(sprite);
					p->die();
					break;
				}
			}
			shovel->SetSpritePosition(12.093, -32.500);
		}
		left_pressed = false;
		seed = nullptr;
		shovel = nullptr;
	}
}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// bAltPress bShiftPress bCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
void CSystem::OnKeyUp(const int iKey)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
void CSystem::OnSpriteColSprite(const char* szSrcName, const char* szTarName)
{
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);


	if (src && tar) {

		// С������
		if (src->get_type() == "Car" && tar->get_type() == "Zombie") {

			std::cout << "src:" << src->get_type() << "  tar:" << tar->get_type() << std::endl;

			Zombie* z = reinterpret_cast<Zombie*>(tar);  // ָ��ǿת
			Car* c = reinterpret_cast<Car*>(src);  // ָ��ǿת

			c->SetSpriteLinearVelocityX(25.0);

			z->die(0);

		}

		// ��ʬ���빥����Χ
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// ת�����丸�����ָ��
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(fTimeDelta);
		}

		// ��ʬ��ֲ��
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			Zombie* z = reinterpret_cast<Zombie*>(src);  // ָ��ǿת
			Plant* p = reinterpret_cast<Plant*>(tar);
			z->eat_plant(p, fTimeDelta);
		}

		// �ӵ���ʬ
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			Arms* a = reinterpret_cast<Arms*>(src);  // ָ��ǿת
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			z->attacked_by(a);
		}
	}
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CSystem::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{

}

