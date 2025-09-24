#include<iostream>

using namespace std;

// 캐릭터 클래스
class character{
public:
    character() : hp(100), power(100){};
protected:
    int hp;
    int power;
};

// 플레이어 클래스
class player : public character{
public:
    player(){};
};

// 기본 몬스터 클래스
class monster{
public:
    monster(){};
    void get_damage(int _damage){};
    void attack(player target_player){};
    void attack_special(player target_player);
};

void monster::attack_special(player target_player){
    cout <<  "기본 공격 : 데이지 - 10 hp" << endl;
};

// 기본 몬스터 클래스 상속
class monster_a : public monster, character{
public:
    void attack_special(player target_player){
        cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
    }
};

// 기본 몬스터 클래스 상속
class monster_b : public monster, character{
public:
    void attack_special(player target_player){
        cout << "가상 공격 : 데미지 - 0 hp" << endl;
    }
};

// 기본 몬스터 클래스 상속
class monster_c : public monster, character{
public:
    void attack_special(player target_player);
};

void monster_c::attack_special(player target_player){
    cout << "강력 뇌전 공격 : 데미지 - 100 hp" << endl;
};

int main(){
    player player_1;

    monster_a forest_monster;
    monster_b tutorial_monster;
    monster_c boss_monster;

    cout << "오버라이딩 공격" << endl;
    forest_monster.attack_special(player_1);
    tutorial_monster.attack_special(player_1);
    boss_monster.attack_special(player_1);

    cout << "기본(monster 클래스) 공격" << endl;
    forest_monster.monster::attack_special(player_1);
    tutorial_monster.monster::attack_special(player_1);
    boss_monster.monster::attack_special(player_1);
}