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
        monster_a(10, 10);   // 생성자에서 다른 생성자를 호출
        cout << "monster_a 클래스 생성자 and call another constructor" << endl;
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
    forest_monster.show_location();   
    /*
        이 경우 forest_monster 인스턴스에는 매개변수로 받은 생성자가 이름없는 객체로 생성되었다가 소멸 된 것이다.
     */
    return 0;
}