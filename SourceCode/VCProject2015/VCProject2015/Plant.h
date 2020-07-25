#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
// ֲ�����
class Plant : public PvZSprite
{
public:
	Plant(const char* sprite_name, double health, int attack_interval);
	Plant(const char* sprite_name, double health);

	virtual void attack(float delta_time) = 0;
	virtual bool attacked_by(Zombie* zombie);

	const char* get_type() override;

protected:
	int line;                           // ������
	double health;                      // Ѫ��
	float next_attack;                  // �����´ι���ʱ��
	float attack_interval;        // �������
	static const char* type;            // ����
};

/* --------------------------------------------------- */
// �㶹���� �̳���ֲ�����
class PeaShooter : public Plant {

public:
	PeaShooter(const char* plant_name, Pea* pea);
	void attack(float delta_time) override;

private:
	Pea* pea;
};


/* --------------------------------------------------- */
// ���տ� �̳���ֲ�����
class SunFlower : public Plant {
public:
	SunFlower(const char* plant_name);
	void attack(float delta_time) override;

protected:
	double light_num;                   // ��������
	double light_v;						// ����һ�ι��ʱ��
};
/* --------------------------------------------------- */