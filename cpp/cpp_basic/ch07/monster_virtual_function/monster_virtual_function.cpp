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
    virtual void attack_special(player target_player); // 가상함수 선언
};

void monster::attack_special(player target_player){
    cout <<  "기본 공격 : 데이지 - 10 hp" << endl;
};

// 기본 몬스터 클래스 상속
class monster_a : public monster, character{
public:
    virtual void attack_special(player target_player) override; // 가상함수 오버라이드 선언
};

void monster_a::attack_special(player target_player){
    cout <<  "인텡글 공격 : 데이지 - 15 hp" << endl;
}

// 기본 몬스터 클래스 상속
class monster_b : public monster, character{
public:
    virtual void attack_special(player target_player) override; // 가상함수 오버라이드 선언
};

void monster_b::attack_special(player target_player){
    cout <<  "가상 공격 : 데이지 - 0 hp" << endl;
}

// 기본 몬스터 클래스 상속
class monster_c : public monster, character{
public:
    virtual void attack_special(player target_player) override; // 가상함수 오버라이드 선언
};

void monster_c::attack_special(player target_player){
    cout << "강력 뇌전 공격 : 데미지 - 100 hp" << endl;
};

int main(){

    player player_1;
    monster_a forest_monster;

    monster &mon = forest_monster;       // 부모 클래스의 래퍼런스에 대입
    monster_a &mon_a = forest_monster;   // 자식 클래스의 레퍼런스에 대입

    cout << endl << "부모 클래스 레퍼런스로 공격" << endl;
    mon.attack_special(player_1);

    cout << endl << "자식 클래스 레퍼런스로 공격" << endl;
    mon_a.attack_special(player_1);
    
    /* 부모클래스(monster)에서 가상함수로 선언한 후, 자식클래스에서(monster_a, b, c)에서 해당함수를 오버라이딩을 해야 
       다형성을 사용하더라도 자식클래스에 있는 함수 내용이 실행이됨 -> 자바에서보면 매우 당연한 얘기
       c++에서는 가상함수로 오버라이딩 하지 않으면 다형성을 이용하기 위해서 
       monter &mon = forest_monster; (-> monster_a 클래스임)
       mon.attack_special()을 실행하게 되면 monster 클래스에서 선언된 함수로 실행이됨  -> monster_reference_call.cpp를 확인해보면 됨
    */ 

    return 0;
}