#include "Plant.h"

const char* Plant::type = "Plant";

Plant::Plant(const char* sprite_name, double health, int attack_interval) :
    PvZSprite(sprite_name),
    health(health), 
    next_attack(0),
    attack_interval(attack_interval) {

}

const char* Plant::get_type() {
    return type;
}

/* --------------------------------------------------- */
PeaShooter::PeaShooter(const char* plant_name, Pea* pea) :
    Plant(plant_name, 300, 2),
    pea(pea)
{
    
}

/// <summary>
/// ʱ�������۵���һ���̶Ⱥ� ��ʼ����
/// </summary>
/// <param name="delta_time">ÿ��ʱ����</param>
void PeaShooter::attack(float delta_time) {

    if ((next_attack -= delta_time) <= 0) {
        // �������֣� �����㶹(������Ч)
        SuperSound::closeAndPlay("open-shoot", "play-shoot", "close-shoot");
        pea->CloneSprite("Pea");
        // ΢��λ��һ�� ���첿����
        pea->SetSpritePosition(this->GetSpritePositionX() + 1, this->GetSpritePositionY() - 2);
        pea->SetSpriteLinearVelocityX(40);
        next_attack = attack_interval;
    }
}

/// <summary>
/// ֲ�ﱻ��ʬ��
/// </summary>
/// <param name="zombie">��ֻ��ʬ</param>
/// <returns>true:��ҧ���� false����û��ҧ��</returns>
bool PeaShooter::attacked_by(Zombie* zombie) {

    this->health -= zombie->get_power();
    //std::cout << this->health << std::endl;
    if (this->health <= 0) {
        this->DeleteSprite();
        return true;
    }
    else {
        return false;
    }
}