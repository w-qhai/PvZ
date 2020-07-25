/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain() :
	m_iGameState(1),
	timer(0),
	ord_zombie_count(5),
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("PeaShooterAttackRange")),
	t_sunflower(new SunFlower("SunFlower"))
{

}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop(float	fDeltaTime)
{
	switch (GetGameState())
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
	{
		GameInit();
		SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
	}
	break;

	// ��Ϸ�����У����������Ϸ�߼�
	case 2:
	{
		// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
		if (true)
		{
			GameRun(fDeltaTime);
		}
		else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
		{
			SetGameState(0);
			GameEnd();
		}
	}
	break;

	// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
	int pos[5] = { -27, -12, 0, 12, 25 };
	for (int i = 0; i < ord_zombie_count; i++) {
		// ��װ�� creat_zombie()
		OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName("OrdinaryZombie", vec_ord_zombie.size()));
		vec_ord_zombie.push_back(zombie);
		name_to_sprite[zombie->GetName()] = zombie;
		zombie->CloneSprite(t_ord_zombie->GetName());
		zombie->SetSpritePosition(CSystem::GetScreenRight(), pos[i % 5]);
		zombie->move();
	}

	for (int i = 0; i < 5; i++) {
		// ��װ�� creat_pea_shooter()
		Range* rect = new Range(CSystem::MakeSpriteName("PeaShooterAttackRange", vec_range.size()));
		vec_range.push_back(rect);
		name_to_sprite[rect->GetName()] = rect;
		rect->CloneSprite(t_range->GetName());

		Pea* pea = new Pea(CSystem::MakeSpriteName("Pea", vec_pea.size()));
		vec_pea.push_back(pea);
		name_to_sprite[pea->GetName()] = pea;

		PeaShooter* pshtr = new PeaShooter(CSystem::MakeSpriteName("PeaShooter", vec_pea_shooter.size()), pea);
		vec_pea_shooter.push_back(pshtr);
		name_to_sprite[pshtr->GetName()] = pshtr;

		pshtr->CloneSprite(t_pea_shooter->GetName());
		pshtr->SetSpritePosition(-40 + i * 15, pos[i] + 1);
		pshtr->SetSpriteImmovable(false);
		rect->SpriteMountToSprite(pshtr->GetName(), 11, 0);

		// ��װ�� creat_sunflower()
		SunFlower* sf = new SunFlower(CSystem::MakeSpriteName("SunFlower", vec_sunflower.size()));
		std::cout << sf->get_type();
		vec_sunflower.push_back(sf);
		name_to_sprite[sf->GetName()] = sf;
		std::cout << t_sunflower->GetName() << std::endl;

		sf->CloneSprite(t_sunflower->GetName());
		sf->SetSpritePosition(-40 + i * 20, pos[i] + 1);
		sf->SetSpriteImmovable(false);
	}
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun(float fDeltaTime)
{
	timer += fDeltaTime;

	//for (PeaShooter* pshtr : vec_pea_shooter) {
	//	pshtr->attack(fDeltaTime);
	//}
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}

// �þ�������ӳ�侫�����
PvZSprite* CGameMain::get_sprite_by_name(const std::string& sprite_name) {
	if (name_to_sprite.count(sprite_name)) {
		return name_to_sprite.at(sprite_name);
	}
	else {
		return nullptr;
	}
}