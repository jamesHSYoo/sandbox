#include<iostream>

using namespace std;

class character{
public:
    character(){
        cout << "character 클래스 생성자" << endl;
    };
};

class monster{
public:
    monster(){
        cout << "monster 클래스 생성자" << endl;
    };
};

class monster_a : public monster, character{
public:
    monster_a(){
        cout << "monster_a 클래스 생성자" << endl;
    };

    monster_a(int x, int y) : location{x, y}{
        cout << "monster_a 클래스 생성자(매개변수 추가)" << endl;
    };

    void show_location(){
        cout << "위치(" << location[0] << " , " << location[1] << ")" << endl;
    }


private:
    int location[2];
};

int main(){

    monster_a forest_monster;
    forest_monster.show_location();   // 값을 매핑하는 생성자를 쓰지 않았기에 쓰래기 값이 나옴
    monster_a wood_monster(10, 25);
    wood_monster.show_location();
    return 0;
}