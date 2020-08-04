#pragma once
#include "PvZSprite.h"
class Assist :
    public PvZSprite
{
public:
    Assist(const char* sprite_name);
    const char* get_type() override;
    void set_exist(bool exist) override;
protected:
    static const char* type;
};

// С�� 
class Car : public Assist {
public:
	Car(const char* assist_name);
	const char* get_type() override;
protected:
	static const char* type;
};

// ����
class Shovel : public Assist {
public:
	Shovel(const char* assist_name);
	const char* get_type() override;
protected:
	static const char* type;
};

// ������Χ
class Range : public Assist {
public:
    Range(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};

// ̫��
class Sun : public Assist {
public:
    Sun(const char* assist_name, int num);
    const char* get_type() override;
    int get_num() { return num; }
protected:
    int num;
    static const char* type;
};

// ֲ�￨
class Card : public Assist {
public:
    Card(const char* assist_name, double cooldownk);
    const char* get_type() override;
    bool ready(long double now);
    void plant_time(long double now);
    void set_mask(CSprite* mask);
protected:
    const double cooldown;          // ��ȴʱ��
    double pre_select;              // �ϴ�ѡ���ʱ�� ���ڼ���ʱ���
    CSprite* gray_mask;
    static const char* type;
};

class PeaShooterCard : public Card {
public:
    PeaShooterCard(const char* card_name);
    const char* get_type() override;

protected:
    static const char* type;
};

class SunflowerCard : public Card {
public:
    SunflowerCard(const char* card_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class CherryBombCard : public Card {
public:
    CherryBombCard(const char* card_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class PotatoMineCard : public Card {
public:
    PotatoMineCard(const char* card_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class JalapenoCard : public Card {
public:
    JalapenoCard(const char* card_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class WallNutCard : public Card {
public:
    WallNutCard(const char* card_name);
    const char* get_type() override;
protected:
    static const char* type;
};
