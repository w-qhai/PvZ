#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
#include "Assist.h"

// ֲ�����
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, double health, int attack_interval, int cost);
    virtual int attack(float delta_time) = 0;
    virtual bool attacked_by(Zombie* zombie);
    
    const char* get_type() override;
    void set_exist(bool exist);
    int get_cost() { return cost; }
    void change_zombie_animation();
    void die();
protected:
    double health;                      // Ѫ��
    long double next_attack;            // �����´ι���ʱ��
    const float attack_interval;        // �������
    static const char* type;            // ����
    int cost;                           // ��������
    std::set<Zombie*> set_attack_zombie;    // ����ʵʩ������Zombie����
};

// �㶹���� �̳���ֲ�����
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    int attack(float delta_time) override;
private:
    Pea* pea;
};


// ���տ� �̳���ֲ�����
class Sunflower : public Plant {

public:
    Sunflower(const char* plant_name, Sun* sun);
    int attack(float delta_time) override;
private:
    Sun* sun;
};

// ӣ��ը�� �̳���ֲ�����
class CherryBomb : public Plant {

public:
    CherryBomb(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
    void set_exist(bool exist) override;
private:
    Boom* boom;
    long double plant_time;
};


// �������� �̳���ֲ�����
class PotatoMine : public Plant {

public:
    PotatoMine(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
private:
    Boom* boom;
    long double plant_time;
    const float preparation_time;
};

// ��� �̳���ֲ�����
class WallNut : public Plant {

public:
    WallNut(const char* plant_name);
    virtual bool attacked_by(Zombie* zombie) override;
    int attack(float delta_time) override; // ���麯�� ����޹�����Ϊ�������Ǹ��պ���
};

// ������ �̳���ֲ�����
class Jalapeno : public Plant {

public:
    Jalapeno(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
    void set_exist(bool exist) override;
private:
    Boom* boom;
    long double plant_time;
};


