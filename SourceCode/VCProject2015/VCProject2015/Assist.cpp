#include "Assist.h"
const char* Assist::type = "Assist";
Assist::Assist(const char* sprite_name) :
    PvZSprite(sprite_name)
{
    this->exist = true;
}

void Assist::set_exist(bool exist) {
    this->exist = exist;
}

const char* Assist::get_type() {
    return type;
}

/*-----------------������Χ-------------------*/
const char* Range::type = "Range";
Range::Range(const char* assist_name) :
    Assist(assist_name)
{

}

const char* Range::get_type() {
    return type;
}


/*-----------------С��-------------------*/
const char* Car::type = "Car";
Car::Car(const char* assist_name) :
	Assist(assist_name)
{

}

const char* Car::get_type() {
	return type;
}

/*-----------------����-------------------*/
const char* Shovel::type = "Shovel";
Shovel::Shovel(const char* assist_name) :
	Assist(assist_name)
{

}

const char* Shovel::get_type() {
	return type;
}

/*-----------------����-------------------*/
const char* Sun::type = "Sun";
Sun::Sun(const char* assist_name, int num) :
    Assist(assist_name),
    num(num)
{

}

const char* Sun::get_type() {
    return type;
}

/*-----------------ֲ�￨-------------------*/
const char* Card::type = "Card";
Card::Card(const char* assist_name, double cooldown) :
    Assist(assist_name),
    cooldown(cooldown),
    pre_select(0),
    gray_mask(nullptr)
{

}

const char* Card::get_type() {
    return type;
}

bool Card::ready(long double now) {
    // ������ε�ʱ����
    if (now - pre_select >= cooldown) {
        if (gray_mask && gray_mask->IsSpriteVisible() != false) {
            /*gray_mask->SetSpriteHeight(0); // ����
            gray_mask->SetSpriteVisible(false);*/

            // �Ƴ���Ļ�� ��ȥ����ȥ����
            gray_mask->SetSpritePosition(-100, -100);
        }
        return true;
    }
    else {
        if (gray_mask) {
            // ����ʱ��ٷֱ� �����ɰ�߶�
            float percentage = (cooldown - (now - pre_select)) / cooldown;
            gray_mask->SetSpriteHeight(percentage * this->GetSpriteHeight());
        }
        return false;
    }
}

void Card::plant_time(long double now) {
    this->pre_select = now;
    if (gray_mask) {
        gray_mask->SetSpritePosition(this->GetSpritePositionX(), this->GetSpritePositionY());
        gray_mask->SetSpriteHeight(this->GetSpriteHeight());
    }
}

void Card::set_mask(CSprite* mask) {
    gray_mask = mask;
}

/*------------------һЩֲ�￨-start------------------*/

/*�㶹����*/
const char* PeaShooterCard::type = "PeaShooterCard";
PeaShooterCard::PeaShooterCard(const char* card_name) :
    Card(card_name, 2)
{

}

const char* PeaShooterCard::get_type() {
    return type;
}

/*���տ�*/
const char* SunflowerCard::type = "SunflowerCard";
SunflowerCard::SunflowerCard(const char* card_name) :
    Card(card_name, 2)
{

}

const char* SunflowerCard::get_type() {
    return type;
}

/*ӣ��ը��*/
const char* CherryBombCard::type = "CherryBombCard";
CherryBombCard::CherryBombCard(const char* card_name) :
    Card(card_name, 2)
{

}

const char* CherryBombCard::get_type() {
    return type;
}

/*��������*/
const char* PotatoMineCard::type = "PotatoMineCard";
PotatoMineCard::PotatoMineCard(const char* card_name) :
    Card(card_name, 2)
{

}

const char* PotatoMineCard::get_type() {
    return type;
}

/*������*/
const char* JalapenoCard::type = "JalapenoCard";
JalapenoCard::JalapenoCard(const char* card_name) :
    Card(card_name, 2)
{

}

const char* JalapenoCard::get_type() {
    return type;
}

/*���*/
const char* WallNutCard::type = "WallNutCard";
WallNutCard::WallNutCard(const char* assist_name) :
    Card(assist_name, 2)
{

}

const char* WallNutCard::get_type() {
    return type;
}
/*------------------һЩֲ�￨-end----------------*/
