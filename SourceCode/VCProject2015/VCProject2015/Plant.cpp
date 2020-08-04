#include "Plant.h"

const char* Plant::type = "Plant";

/* --------------------------------------------------- */
// ֲ�����ʵ��
Plant::Plant(const char* sprite_name, double health, int attack_interval, int cost) :
	PvZSprite(sprite_name),
	health(health),
	next_attack(0),
	attack_interval(attack_interval),
	cost(cost) {

}
void Plant::die() {
	this->change_zombie_animation();

	this->DeleteSprite();
}

/// <summary>
/// ֲ�ﱻ��ʬ��
/// </summary>
/// <param name="zombie">��ֻ��ʬ</param>
/// <returns>true:��ҧ���� false����û��ҧ��</returns>
bool Plant::attacked_by(Zombie* zombie) {
	this->health -= zombie->get_power();
	std::cout << this->health << std::endl;

	if (this->health <= 0) {

		// ��ֲ����������������ҧֲ���ɥʬ���ָ�����
		this->die();
		return true;
	}
	else {
		// ����ҧֲ����ý�ʬ״̬
		zombie->set_eating_plant(this);
		set_attack_zombie.insert(zombie);
		zombie->set_status();

		return false;
	}
}

const char* Plant::get_type() {
	return type;
}

void Plant::set_exist(bool exist) {
	this->exist = exist;
	this->SetSpriteCollisionSend(exist);
	this->SetSpriteCollisionReceive(exist);
	this->SetSpriteCollisionPhysicsReceive(exist);
	this->SetSpriteCollisionPhysicsSend(exist);
}

void Plant::change_zombie_animation() {

	for (std::set<Zombie*>::iterator it = this->set_attack_zombie.begin();
		it != this->set_attack_zombie.end();
		++it)
	{
		if ((*it)->is_exist()) {

			(*it)->set_eating_plant(nullptr);
			(*it)->set_status();
		}
	}

	this->set_attack_zombie.clear();

}

/* --------------------------------------------------- */
// �㶹����
PeaShooter::PeaShooter(const char* plant_name, Pea* pea) :
	Plant(plant_name, 300, 2, 100),
	pea(pea)
{

}

/// <summary>
/// ʱ�������۵���һ���̶Ⱥ� ��ʼ����
/// </summary>
/// <param name="delta_time">ÿ��ʱ����</param>
int PeaShooter::attack(float delta_time) {
	if (pea->is_exist() == false && this->is_exist()) {
		if (delta_time - next_attack > attack_interval) {
			pea->set_exist(true);
			pea->CloneSprite("Pea");
			// ΢��λ��һ�� ���첿����
			pea->SetSpritePosition(this->GetSpritePositionX() + 1, this->GetSpritePositionY() - 2);
			pea->SetSpriteLinearVelocityX(40);
			next_attack = delta_time;
		}
	}
	return 0;
}
/* --------------------------------------------------- */
// ���տ�

Sunflower::Sunflower(const char* sprite_name, Sun* sun) :
	Plant(sprite_name, 300, 10, 50),
	sun(sun) {
	
}

int Sunflower::attack(float delta_time) {
	if (this->is_exist() && sun->is_exist() == false) {
		if (delta_time - next_attack > attack_interval) {
			sun->set_exist(true);
			sun->CloneSprite("Sun");
			sun->SetSpritePosition(this->GetSpritePositionX() + 5, this->GetSpritePositionY() + 5);
			next_attack = delta_time;
			return sun->get_num();
		}
	}
	return 0;
}

/* --------------------------------------------------- */
// 	ӣ��ը�� CherryBomb
CherryBomb::CherryBomb(const char* plant_name, Boom* boom, long double plant_time) :
	Plant(plant_name, 300, 2, 150),
	boom(boom),
	plant_time(plant_time)
{

}

int CherryBomb::attack(float delta_time) {
	if (this->is_exist()) {
		boom->set_exist(true);
		boom->CloneSprite("CherryBoom");
		boom->SpriteMountToSprite(this->GetName(), 0, 0);
		this->SetSpriteLifeTime(0.5);
		this->set_exist(false);
		next_attack = delta_time;
	}
	return 1;
}

bool CherryBomb::preparation(float delta_time) {
	if (delta_time - plant_time >= 2) {
		this->attack(delta_time);
		return true;
	}
	return false;
}

void CherryBomb::set_exist(bool exist) {
	this->exist = exist;
	this->SetSpriteCollisionSend(exist);
	this->SetSpriteCollisionReceive(false);
	this->SetSpriteCollisionPhysicsReceive(false);
	this->SetSpriteCollisionPhysicsSend(false);
}

/* --------------------------------------------------- */
// 	�������� PotatoMine
PotatoMine::PotatoMine(const char* plant_name, Boom* boom, long double plant_time) :
	Plant(plant_name, 300, 2, 25),
	boom(boom),
	plant_time(plant_time),
	preparation_time(2)
{

}

int PotatoMine::attack(float delta_time) {
	if (this->preparation(delta_time)) {
		if (this->is_exist()) {
			if (delta_time - next_attack > attack_interval) {
				std::cout << "Boom" << std::endl;
				boom->set_exist(true);
				boom->CloneSprite("PotatoMineBoom");
				boom->SpriteMountToSprite(this->GetName(), 0, 0);
				this->SetSpriteLifeTime(0.5);
				this->set_exist(false);
				next_attack = delta_time;
			}
		}
	}
	return 1;
}

bool PotatoMine::preparation(float delta_time) {
	// ʱ�䵽�� ��ͷ
	if (delta_time - plant_time >= preparation_time) {
		if (std::string(this->GetAnimateSpriteAnimationName()) != "PotatoMine2Animation") {
			this->AnimateSpritePlayAnimation("PotatoMine2Animation", false);
			this->SetSpriteWidth(9.250);
			this->SetSpriteHeight(6.875);
		}
		return true;
	}
	return false;
}

/* --------------------------------------------------- */
// 	��� WallNut
WallNut::WallNut(const char* plant_name) :
	Plant(plant_name, 100000, 2, 50)
{

}

int WallNut::attack(float delta_time) {
	return 0;
}

/// <summary>
/// ֲ�ﱻ��ʬ��
/// </summary>
/// <param name="zombie">��ֻ��ʬ</param>
/// <returns>true:��ҧ���� false����û��ҧ��</returns>
bool WallNut::attacked_by(Zombie* zombie) {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	// ���ø����ٽ�ֵ��ͬ�Ķ���
	if (this->health <= 1333) {
		if (currentAnimation != "Wallnut3Animation") {
			this->AnimateSpritePlayAnimation("Wallnut3Animation", false);
		}
	}
	else if (this->health <= 2666) {
		if (currentAnimation != "Wallnut2Animation") {
			this->AnimateSpritePlayAnimation("Wallnut2Animation", false);
		}
	}
	else if (this->health <= 4000) {
		if (currentAnimation != "Wallnut1Animation") {
			this->AnimateSpritePlayAnimation("Wallnut1Animation", false);
		}
	}
	// �����궯�� �������ദ��
	return Plant::attacked_by(zombie);
}

/* --------------------------------------------------- */
// 	ӣ��ը�� CherryBomb
Jalapeno::Jalapeno(const char* plant_name, Boom* boom, long double plant_time) :
	Plant(plant_name, 300, 2, 150),
	boom(boom),
	plant_time(plant_time)
{

}

int Jalapeno::attack(float delta_time) {
	if (this->is_exist()) {
		this->SetSpriteVisible(false);
		boom->set_exist(true);
		boom->CloneSprite("JalapenoAttack");
		boom->SetSpritePosition(0, this->GetSpritePositionY());
		boom->SetSpriteLifeTime(0.5);
		// ���ɾ�����³�bug
		this->SetSpriteLifeTime(0.6);
		this->set_exist(false);
		next_attack = delta_time;
	}
	return 1;
}

bool Jalapeno::preparation(float delta_time) {
	if (delta_time - plant_time >= 2) {
		this->attack(delta_time);
		return true;
	}
	return false;
}

void Jalapeno::set_exist(bool exist) {
	this->exist = exist;
	this->SetSpriteCollisionSend(exist);
	this->SetSpriteCollisionReceive(false);
	this->SetSpriteCollisionPhysicsReceive(false);
	this->SetSpriteCollisionPhysicsSend(false);
}